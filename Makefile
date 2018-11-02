CFLAG=-std=c99 -I.
LIBS=-L.
.PHONY: clean
test_single_list: test/test_single_list.c single_list.o
	$(CC) $(CFLAG) $(LIBS) -o $(<D)/$@ $^
	$(<D)/$@
%.o: %.c
	$(CC) -c $(CFLAG) $(LIBS) -o $@ $*.c
clean:
	find . -name *.o | xargs -i rm {}


