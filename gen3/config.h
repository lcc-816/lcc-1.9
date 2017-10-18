/* C compiler: configuration parameters for VAX subset code generator */

/* include config */
#define VAX

/* type metrics: size,alignment,constants */
#define CHAR_METRICS     1,1,0
#define SHORT_METRICS    2,2,0
#define INT_METRICS      4,4,0
#define FLOAT_METRICS    4,4,1
#define DOUBLE_METRICS   8,4,1
#define POINTER_METRICS  4,4,0
#define STRUCT_ALIGN     1

#define LEFT_TO_RIGHT	 /* evaluate args left-to-right */
#define LITTLE_ENDIAN	 /* right-to-left bit fields */
#define JUMP_ON_RETURN	0
/* end config */

/* include Env */
typedef struct {
	unsigned rmask;
	int offset;
} Env;
/* end Env */
/* include Xnode */
typedef struct {
	int id;             /* node id number (omit) */
	unsigned visited:1; /* 1 if dag has been linearized */
	int reg;            /* register number */
	unsigned rmask;     /* unshifted register mask */
	unsigned busy;      /* busy regs */
	int argoffset;      /* ARG: argument offset */
	Node next;          /* next node on emit list */
} Xnode;
/* end Xnode */
/* include Xsymbol */
typedef struct {
	char *name;		/* name for back end */
	int offset;		/* frame offset */
} Xsymbol;
/* end Xsymbol */

/* include defaddress */
#define defaddress(p) print(".long %s\n", (p)->x.name)
/* end defaddress */
/* include export */
#define export(p) print(".globl %s\n", (p)->x.name)
#define import(p)
/* end export */
/* include progend */
#define progend(x)
/* end progend */
/* include space */
#define space(x) print(".space %d\n", (x))
/* end space */

#define stabblock(a,b,c)
#define stabend(a,b,c,d,e)
#define stabfend(a,b)
#define stabinit(a,b,c)
#define stabline(a)
#define stabsym(a)
#define stabtype(a)

#ifdef vax
dclproto(extern double atof,(char *));
#define strtod(a,b) atof(a)
#endif
