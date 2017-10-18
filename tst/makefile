tst-makefile:
	@echo 1>&2 run make from a target-specific directory

test:	$(D)/tst/8q.s \
	$(D)/tst/array.s \
	$(D)/tst/cf.s \
	$(D)/tst/cq.s \
	$(D)/tst/cvt.s \
	$(D)/tst/fields.s \
	$(D)/tst/front.s \
	$(D)/tst/incr.s \
	$(D)/tst/init.s \
	$(D)/tst/limits.s \
	$(D)/tst/paranoia.s \
	$(D)/tst/sort.s \
	$(D)/tst/spill.s \
	$(D)/tst/stdarg.s \
	$(D)/tst/struct.s \
	$(D)/tst/switch.s \
	$(D)/tst/wf1.s \
	$(D)/tst/yacc.s

T=../tst
CMD=@cd $(D); ../run $(TARGET) $(OS)

$(D)/tst/8q.s:		$(RUN) $(D)/rcc $(T)/8q.c       $(T)/8q.0;	$(CMD) 8q
$(D)/tst/array.s:	$(RUN) $(D)/rcc $(T)/array.c    $(T)/array.0;	$(CMD) array
$(D)/tst/cf.s:		$(RUN) $(D)/rcc $(T)/cf.c       $(T)/cf.0;	$(CMD) cf
$(D)/tst/cq.s:		$(RUN) $(D)/rcc $(T)/cq.c       $(T)/cq.0;	$(CMD) cq
$(D)/tst/cvt.s:		$(RUN) $(D)/rcc $(T)/cvt.c      $(T)/cvt.0;	$(CMD) cvt
$(D)/tst/fields.s:	$(RUN) $(D)/rcc $(T)/fields.c   $(T)/fields.0;	$(CMD) fields
$(D)/tst/front.s:	$(RUN) $(D)/rcc $(T)/front.c    $(T)/front.0;	$(CMD) front
$(D)/tst/incr.s:	$(RUN) $(D)/rcc $(T)/incr.c     $(T)/incr.0;	$(CMD) incr
$(D)/tst/init.s:	$(RUN) $(D)/rcc $(T)/init.c     $(T)/init.0;	$(CMD) init
$(D)/tst/limits.s:	$(RUN) $(D)/rcc $(T)/limits.c   $(T)/limits.0;	$(CMD) limits
$(D)/tst/paranoia.s:	$(RUN) $(D)/rcc $(T)/paranoia.c	$(T)/paranoia.0;$(CMD) paranoia
$(D)/tst/sort.s:	$(RUN) $(D)/rcc $(T)/sort.c     $(T)/sort.0;	$(CMD) sort
$(D)/tst/spill.s:	$(RUN) $(D)/rcc $(T)/spill.c    $(T)/spill.0;	$(CMD) spill
$(D)/tst/stdarg.s:	$(RUN) $(D)/rcc $(T)/stdarg.c   $(T)/stdarg.0;	$(CMD) stdarg
$(D)/tst/struct.s:	$(RUN) $(D)/rcc $(T)/struct.c   $(T)/struct.0;	$(CMD) struct
$(D)/tst/switch.s:	$(RUN) $(D)/rcc $(T)/switch.c   $(T)/switch.0;	$(CMD) switch
$(D)/tst/wf1.s:		$(RUN) $(D)/rcc $(T)/wf1.c      $(T)/wf1.0;	$(CMD) wf1
$(D)/tst/yacc.s:	$(RUN) $(D)/rcc $(T)/yacc.c     $(T)/yacc.0;	$(CMD) yacc

OPTS=TARGET=$(TARGET) OS=$(OS) CC='lcc -B./ -d0.1 -A' \
	CFLAGS='-N -I../../include/$(TARGET)_$(OS) $(CFLAGS)' \
	LDFLAGS='$(LDFLAGS)'

triple:	$(D)/rcc
	rm -f $(D)/*.o
	make $(OPTS) $(D)/rcc
	-od +8 <$(D)/rcc >$(D)/tst/od2
	rm -f $(D)/*.o
	make $(OPTS) $(D)/rcc
	-od +8 <$(D)/rcc >$(D)/tst/od3
	cmp $(D)/tst/od[23] && rm $(D)/tst/od[23]

clean:
	rm -f $(D)/*.o $(D)/tst/od[23] $(D)/tst/*.[12so]
	-cd $(D)/tst; rm -f 8q array cf cq cvt fields front incr init \
		limits paranoia sort spill stdarg struct switch wf1 yacc

clobber:	clean
		rm -f $(D)/rcc
