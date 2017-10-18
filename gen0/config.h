/* C compiler: symbolic configuration parameters */

/* type metrics: size,alignment,constants */
#define CHAR_METRICS		1,1,0
#define SHORT_METRICS		2,2,0
#define INT_METRICS		4,4,0
#define FLOAT_METRICS		4,4,1
#define DOUBLE_METRICS		8,4,1
#define POINTER_METRICS		4,4,0
#define	STRUCT_ALIGN		4

#define LEFT_TO_RIGHT		/* define for left-to-right argument evaluation */
/*#define LITTLE_ENDIAN		/* define for right-to-left bit fields */
#define JUMP_ON_RETURN	1

typedef int Env;
typedef struct {
	short lev;		/* node nesting level */
	short id;		/* node identification number */
	int state;
	Node next;		/* next node on output list */
} Xnode;

typedef struct {
	char *name;		/* name for back end */
	int offset;		/* locals: frame offset */
} Xsymbol;

dclproto(extern void sym,(char *, Symbol, char *));

#define defaddress(p) print("defaddress %s\n", (p)->x.name)
#define export(p) print("export %s\n", (p)->x.name)
#define global(p) sym("global", (p), "\n")
#define import(p) print("import %s\n", (p)->x.name)
#define progend(x) print("progend\n")
#define segment(x) print("segment %s\n", &"text\0bss\0.data\0lit\0.sym\0."[5*(x)-5])
#define space(x) print("space %d\n", (x))

#define stabblock(a,b,c)
#define stabfend(a,b)
#define stabinit(a,b,c)
#define stabsym(a)
#define stabtype(a)
