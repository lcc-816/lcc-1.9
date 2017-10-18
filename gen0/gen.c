/* C compiler: symbolic code generator */

#include "c.h"

static int maxoffset;		/* maximum value of offset */
static int offset;		/* current frame offset */
static Node *tail;

dclproto(extern char *asmname,(Symbol));
dclproto(extern unsigned regloc,(Symbol));
dclproto(extern int regoffset,(int, int));

dclproto(static int gen1,(Node, int, int));
dclproto(static void symname,(Symbol));

/* address - initialize q for addressing expression p+n */
void address(q, p, n) Symbol q, p; int n; {
	q->x.name = stringf("%s%s%d", p->x.name, n > 0 ? "+" : "", n);
}

/* asmcode - emit assembly language specified by asm */
void asmcode(str, argv) char *str; Symbol argv[]; {
	for ( ; *str; str++)
		if (*str == '%' && str[1] >= 0 && str[1] <= 9)
			print("%s", asmname(argv[*++str]));
		else
			*bp++ = *str;
	outs("\n");
}

/* asmname - print assembler code for symbol p */
char *asmname(p) Symbol p; {
	return p->x.name;
}

/* blockbeg - begin a compound statement */
void blockbeg(e) Env *e; {
	*e = offset;
}

/* blockend - end a compound statement */
void blockend(e) Env *e; {
	if (offset > maxoffset)
		maxoffset = offset;
	offset = *e;
}

/* defconst - define a constant */
void defconst(ty, v) Value v; {
	print("defconst ");
	switch (ty) {
	case C: print("char %d\n",       v.uc); break;
	case S: print("short %d\n",      v.ss); break;
	case I: print("int %d\n",        v.i ); break;
	case U: print("unsigned 0x%x\n", v.u ); break;
	case P: print("void* 0x%x\n",    v.p ); break;
	case F: {
		char buf[MAXLINE];
		sprintf(buf, "float %.8e\n", v.f);  /* fix */
		outs(buf);
		break;
		}
	case D: {
		char buf[MAXLINE];
		sprintf(buf, "double %.18e\n", v.d);  /* fix */
		outs(buf);
		break;
		}
	default: assert(0);
	}
}

/* defstring - emit a string constant */
void defstring(len, s) char *s; {
	int n;

	print("defstring \"");
	for (n = 0; len-- > 0; s++) {
		if (n >= 72) {
			print("\n");
			n = 0;
		}
		if (*s == '"' || *s == '\\') {
			print("\\%c", *s);
			n += 2;
		} else if (*s >= ' ' && *s < 0177) {
			*bp++ = *s;
			n += 1;
		} else {
			print("\\%d%d%d", (*s>>6)&3, (*s>>3)&7, *s&7);
			n += 4;
		}
	}
	print("\"\n");
}

/* defsymbol - define a symbol: initialize p->x */
void defsymbol(p) Symbol p; {
	p->x.name = p->name;
	if (glevel > 2 && p->scope >= LOCAL && p->type && isfunc(p->type))
		sym("extern", p, "\n");
}

/* emit - emit the dags on list p */
void emit(p) Node p; {
	for (; p; p = p->x.next)
		if (p->op == LABEL+V) {
			assert(p->syms[0]);
			print("%s:\n", p->syms[0]->x.name);
		} else {
			int i;
			assert(p->link == 0 || p->x.lev == 0);
			print("node%c%d %s count=%d", p->x.lev == 0 ? '\'' : '#', p->x.id,
				opname(p->op), p->count);
			for (i = 0; i < MAXKIDS && p->kids[i]; i++)
				print(" #%d", p->kids[i]->x.id);
			for (i = 0; i < MAXSYMS && p->syms[i]; i++) {
				if (p->syms[i]->x.name)
					print(" %s", p->syms[i]->x.name);
				if (p->syms[i]->name != p->syms[i]->x.name)
					print(" (%s)", p->syms[i]->name);
			}
			print("\n");
		}
}

/* function - generate code for a function */
void function(f, caller, callee, ncalls) Symbol f, caller[], callee[]; {
	int i;

	sym("function", f, ncalls ? 0 : "\n");
	if (ncalls)
		print(" ncalls=%d\n", ncalls);
	offset = 0;
	for (i = 0; caller[i] && callee[i]; i++) {
		offset = roundup(offset, caller[i]->type->align);
		caller[i]->x.name = caller[i]->name;
		callee[i]->x.name = callee[i]->name;
		caller[i]->x.offset = callee[i]->x.offset = offset;
		sym("caller's parameter", caller[i], "\n");
		sym("callee's parameter", callee[i], "\n");
		offset += caller[i]->type->size;
	}
	maxoffset = offset = 0;
	gencode(caller, callee);
	print("maxoffset=%d\n", maxoffset);
	emitcode();
	print("end %s\n", f->x.name);
}

/* gen - generate code for the dags on list p */
Node gen(p) Node p; {
	int n;
	Node nodelist;

	tail = &nodelist;
	for (n = 0; p; p = p->link) {
		switch (generic(p->op)) {	/* check for valid nodelist */
		case CALL:
			break;
		case ARG:
		case ASGN: case JUMP: case LABEL: case RET:
		case EQ: case GE: case GT: case LE: case LT: case NE:
			assert(p->count == 0);
			break;
		case INDIR:
			assert(p->count > 0);
			break;
		default:
			assert(0);
		}
		n = gen1(p, 0, n);
	}
	*tail = 0;
	return nodelist;
}

/* gen1 - generate code for *p */
static int gen1(p, lev, n) Node p; {
	if (p && p->x.id == 0) {
		p->x.lev = lev;
		p->x.id = ++n;
		n = gen1(p->kids[0], lev + 1, n);
		n = gen1(p->kids[1], lev + 1, n);
		*tail = p;
		tail = &p->x.next;
	}
	return n;
}

/* local - local variable */
void local(p) Symbol p; {
	offset = roundup(offset, p->type->align);
	p->x.name = p->name;
	p->x.offset = offset;
	sym("local", p, "\n");
	offset += p->type->size;
}

/* progbeg - beginning of program */
void progbeg(argc, argv) char *argv[]; {
	print("progbeg argv=");
	while (argc--)
		print("%s ", *argv++);
	print("\n");
}

/* regloc - return "id" for p's register */
unsigned regloc(p) Symbol p; {
	assert(p && p->sclass == REGISTER);
	return 0;
}
	
/* regoffset - return stack offset of cell that saves reg */
int regoffset(regset, regnum) {
	return -1;
}

/* sym - print symbol table entry for p, followed by str */
void sym(kind, p, str) char *kind, *str; Symbol p; {
	assert(kind);
	if (glevel > 2) {
		print("%s ", kind);
		symname(p);
	} else
		print("%s %s", kind, p->name);
	if (p->name != p->x.name)
		print(" (%s)", p->x.name);
	print(" type=%t class=%k scope=", p->type, p->sclass);
	switch (p->scope) {
	case CONSTANTS: print("CONSTANTS"); break;
	case LABELS:    print("LABELS");    break;
	case GLOBAL:    print("GLOBAL");    break;
	case PARAM:     print("PARAM");     break;
	case LOCAL:     print("LOCAL");     break;
	default:
		if (p->scope > LOCAL)
			print("LOCAL+%d", p->scope - LOCAL);
		else
			print("%d", p->scope);
	}
	if (p->scope >= PARAM && p->sclass != STATIC)
		print(" offset=%d ref=%d", p->x.offset, p->ref);
	if (glevel > 2) {
		print(" up=");
		symname(p->up);
	}
	if (str)
		print(str);
}

/* symname - print prefix, p's name, declaration source coordinate, suffix */
static void symname(p) Symbol p; {
	if (p)
		print("%s@%w.%d", p->name, &p->src, p->src.x);
	else
		print("0");
}

/* stabend - finalize stab output */
void stabend(cp, p, cpp, sp, stab) Coordinate *cp, **cpp; Symbol p, *sp, *stab; {
	int i;

	symname(p);
	print("\n");
	for (i = 0; cpp[i] && sp[i]; i++) {
		print("%w.%d: ", cpp[i], cpp[i]->x);
		symname(sp[i]);
		print("\n");
	}
}

/* stabline - emit line number information for source coordinate *cp */
void stabline(cp) Coordinate *cp; {
	if (cp->file)
		print("%s:", cp->file);
	print("%d.%d:\n", cp->y, cp->x);
}
