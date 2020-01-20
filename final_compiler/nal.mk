CFLAGS = -Wall -Wextra -pedantic -ansi -O2 -lm
SFLAGS = -fsanitize=address -fsanitize=undefined -g3 -lm
DFLAGS = -Wall -Wextra -pedantic -ansi -g3 -lm
BASE = nal
BEXECS = parse interp
SEXECS = parse_s interp_s
DEXECS = parse_d interp_d
EXECS = $(BEXECS) $(SEXECS) $(DEXECS)
CC = clang

runescape211  :  interp
	./interp ./test/escape211/escape211.$(BASE)

runpi : interp
	./interp ./test/Monte_Carlo_toPI.nal

runbasictest : runparse runinterp


test : testparse testinterp


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


runparse  :  parse
	./parse ./test/basic_test/test1.$(BASE)
	./parse ./test/basic_test/test2.$(BASE)
	./parse ./test/basic_test/test3.$(BASE)
	./parse ./test/basic_test/test4.$(BASE)
	./parse ./test/basic_test/test5.$(BASE)
	./parse ./test/basic_test/test6.$(BASE)


runinterp  :  interp
	./interp ./test/basic_test/test1.$(BASE)
	./interp ./test/basic_test/test2.$(BASE)
	./interp ./test/basic_test/test4.$(BASE)
	./interp ./test/basic_test/test5.$(BASE)


testparse : parse_s parse_d
	./parse_s ./test/basic_test/test1.$(BASE)
	./parse_s ./test/basic_test/test2.$(BASE)
	./parse_s ./test/basic_test/test3.$(BASE)
	./parse_s ./test/basic_test/test4.$(BASE)
	./parse_s ./test/basic_test/test5.$(BASE)
	./parse_s ./test/basic_test/test6.$(BASE)
	valgrind ./parse_d ./test/basic_test/test1.$(BASE)
	valgrind ./parse_d ./test/basic_test/test2.$(BASE)
	valgrind ./parse_d ./test/basic_test/test3.$(BASE)
	valgrind ./parse_d ./test/basic_test/test4.$(BASE)
	valgrind ./parse_d ./test/basic_test/test5.$(BASE)
	valgrind ./parse_d ./test/basic_test/test6.$(BASE)

testinterp : interp_s interp_d
	./interp_s ./test/basic_test/test1.$(BASE)
	./interp_s ./test/basic_test/test2.$(BASE)
	./interp_s ./test/basic_test/test4.$(BASE)
	./interp_s ./test/basic_test/test5.$(BASE)
	valgrind ./interp_d ./test/basic_test/test1.$(BASE)
	valgrind ./interp_d ./test/basic_test/test2.$(BASE)
	valgrind ./interp_d ./test/basic_test/test4.$(BASE)
	valgrind ./interp_d ./test/basic_test/test5.$(BASE)

clean :
	rm -fr $(EXECS)
