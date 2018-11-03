CFLAG=-g -std=c99 -I.
LIBS=-L.
define COMPILE_AND_RUN=
$(CC) $(CFLAG) $(LIBS) -o $(<D)/$@ $^
$(<D)/$@
endef
.PHONY: clean
test_array_list: test/test_array_list.c array_list.o
	$(COMPILE_AND_RUN)
test_single_list: test/test_single_list.c single_list.o
	$(COMPILE_AND_RUN)
%.o: %.c
	$(CC) -c $(CFLAG) $(LIBS) -o $@ $*.c
clean:
	find . -name *.o | xargs -i rm {}


