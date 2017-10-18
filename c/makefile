SHELL=/bin/sh

COBJS=$(D)/dag.o \
	$(D)/decl.o \
	$(D)/enode.o \
	$(D)/error.o \
	$(D)/expr.o \
	$(D)/init.o \
	$(D)/input.o \
	$(D)/lex.o \
	$(D)/main.o \
	$(D)/output.o \
	$(D)/profio.o \
	$(D)/simp.o \
	$(D)/stmt.o \
	$(D)/string.o \
	$(D)/sym.o \
	$(D)/tree.o \
	$(D)/types.o

c-makefile:
	@echo 1>&2 run make from a target-specific directory

$(D)/rcc:	$(COBJS) $(OBJS)
		$(CC) $(LDFLAGS) -o $@ $(COBJS) $(OBJS)

C=../c

$(COBJS):	$(C)/c.h $(C)/token.h $(C)/ops.h
$(OBJS):	$(C)/c.h $(C)/token.h $(C)/ops.h

CCOPT=-D$(TARGET)_$(OS) $(CFLAGS) $(INCLUDES)

$(D)/lex.o:	$(C)/keywords.h

$(D)/dag.o:	$(C)/dag.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/dag.c
$(D)/decl.o:	$(C)/decl.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/decl.c
$(D)/enode.o:	$(C)/enode.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/enode.c
$(D)/error.o:	$(C)/error.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/error.c
$(D)/expr.o:	$(C)/expr.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/expr.c
$(D)/init.o:	$(C)/init.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/init.c
$(D)/input.o:	$(C)/input.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/input.c
$(D)/lex.o:	$(C)/lex.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/lex.c
$(D)/main.o:	$(C)/main.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/main.c
$(D)/output.o:	$(C)/output.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/output.c
$(D)/profio.o:	$(C)/profio.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/profio.c
$(D)/simp.o:	$(C)/simp.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/simp.c
$(D)/stmt.o:	$(C)/stmt.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/stmt.c
$(D)/string.o:	$(C)/string.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/string.c
$(D)/sym.o:	$(C)/sym.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/sym.c
$(D)/tree.o:	$(C)/tree.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/tree.c
$(D)/types.o:	$(C)/types.c;	cd $(D); $(CC) -c $(CCOPT) ../../c/types.c
