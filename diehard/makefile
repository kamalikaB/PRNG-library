OBJS :=diehard.o d3sphere.o kstest.o squeez.o cdbday.o cdosum.o df.o \
       mindist.o cdbinrnk.o cdpark.o cdoperm5.o cdbitst.o cnt1s.o \
       funct.o cdomso.o craptest.o runtest.o 

# link
proggie: $(OBJS)
	gcc   $(OBJS) -o proggie -lm

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info;
# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o
	gcc -MM $(CFLAGS) $*.c > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

# remove compilation products
clean:
	rm -f proggie *.o *.d
