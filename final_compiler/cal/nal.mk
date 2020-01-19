CFLAGS = -Wall -Wextra -pedantic -ansi -O2 -lm
SFLAGS = -fsanitize=address -fsanitize=undefined -g3 -lm
DFLAGS = -Wall -Wextra -pedantic -ansi -g3 -lm
BASE = nal
BEXECS = parse interp
SEXECS = parse_s interp_s
DEXECS = parse_d interp_d
EXECS = $(BEXECS) $(SEXECS) $(DEXECS)
CC = clang

all : $(BEXECS)

parse : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(CFLAGS) -o $@
parse_s : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(SFLAGS) -o $@
parse_d : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(DFLAGS) -o $@


interp : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(CFLAGS) -o $@ -D INTERPRET
interp_s : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(SFLAGS) -o $@ -D INTERPRET
interp_d : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(DFLAGS) -o $@ -D INTERPRET


run : runparse runinterp


runparse  :  parse
	./parse test1.$(BASE)
	./parse test2.$(BASE)
	./parse test3.$(BASE)
	./parse test4.$(BASE)
	./parse test5.$(BASE)
	./parse test6.$(BASE)


runinterp  :  interp
	./interp test1.$(BASE)
	./interp test2.$(BASE)
	./interp test4.$(BASE)
	./interp test5.$(BASE)


test : testparse testinterp

testparse : parse_s parse_d
	./parse_s test1.$(BASE)
	./parse_s test2.$(BASE)
	./parse_s test3.$(BASE)
	./parse_s test4.$(BASE)
	./parse_s test5.$(BASE)
	./parse_s test6.$(BASE)
	./parse_s cal_mac.$(BASE)
	valgrind ./parse_d test1.$(BASE)
	valgrind ./parse_d test2.$(BASE)
	valgrind ./parse_d test3.$(BASE)
	valgrind ./parse_d test4.$(BASE)
	valgrind ./parse_d test5.$(BASE)
	valgrind ./parse_d test6.$(BASE)

testinterp : interp_s interp_d
	./interp_s test1.$(BASE)
	./interp_s test2.$(BASE)
	./interp_s test4.$(BASE)
	./interp_s test5.$(BASE)
	./interp_s cal_mac.$(BASE)
	valgrind ./interp_d test1.$(BASE)
	valgrind ./interp_d test2.$(BASE)
	valgrind ./interp_d test4.$(BASE)
	valgrind ./interp_d test5.$(BASE)

clean :
	rm -fr $(EXECS)
