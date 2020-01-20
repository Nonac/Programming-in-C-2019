CFLAGS = -Wall -Wextra -pedantic -ansi -O2 -lm
SFLAGS = -fsanitize=address -fsanitize=undefined -g3 -lm
DFLAGS = -Wall -Wextra -pedantic -ansi -g3 -lm
BASE = nal
BEXECS = parse interp
EXECS = $(BEXECS)
CC = clang

test : .IGNORE

.IGNORE :  runparse runinterp

parse : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(CFLAGS) -o $@


interp : $(BASE).c $(BASE).h
	$(CC) $(BASE).c $(CFLAGS) -o $@ -D INTERPRET


runparse  :  parse
	./parse ./test/additional_test/test1.$(BASE)
	./parse ./test/additional_test/test2.$(BASE)
	./parse ./test/additional_test/test3.$(BASE)
	./parse ./test/additional_test/test4.$(BASE)
	./parse ./test/additional_test/test5.$(BASE)
	./parse ./test/additional_test/test6.$(BASE)
	./parse ./test/additional_test/test7.$(BASE)
	./parse ./test/additional_test/test8.$(BASE)
	./parse ./test/additional_test/test9.$(BASE)
	./parse ./test/additional_test/test10.$(BASE)
	./parse ./test/additional_test/test11.$(BASE)
	./parse ./test/additional_test/test12.$(BASE)
	./parse ./test/additional_test/test13.$(BASE)
	./parse ./test/additional_test/test14.$(BASE)
	./parse ./test/additional_test/test15.$(BASE)
	./parse ./test/additional_test/test16.$(BASE)
	./parse ./test/additional_test/test17.$(BASE)
	./parse ./test/additional_test/test18.$(BASE)
	./parse ./test/additional_test/test19.$(BASE)
	./parse ./test/additional_test/test20.$(BASE)
	./parse ./test/additional_test/test21.$(BASE)
	./parse ./test/additional_test/test22.$(BASE)
	./parse ./test/additional_test/test23.$(BASE)
	./parse ./test/additional_test/test24.$(BASE)
	./parse ./test/additional_test/test25.$(BASE)
	./parse ./test/additional_test/test26.$(BASE)
	./parse ./test/additional_test/test27.$(BASE)
	./parse ./test/additional_test/test28.$(BASE)
	./parse ./test/additional_test/test29.$(BASE)
	./parse ./test/additional_test/test30.$(BASE)
	./parse ./test/additional_test/test31.$(BASE)


runinterp  :  interp
	./interp ./test/additional_test/test1.$(BASE)
	./interp ./test/additional_test/test2.$(BASE)
	./interp ./test/additional_test/test3.$(BASE)
	./interp ./test/additional_test/test4.$(BASE)
	./interp ./test/additional_test/test5.$(BASE)
	./interp ./test/additional_test/test6.$(BASE)
	./interp ./test/additional_test/test7.$(BASE)
	./interp ./test/additional_test/test8.$(BASE)
	./interp ./test/additional_test/test9.$(BASE)
	./interp ./test/additional_test/test10.$(BASE)
	./interp ./test/additional_test/test11.$(BASE)
	./interp ./test/additional_test/test12.$(BASE)
	./interp ./test/additional_test/test13.$(BASE)
	./interp ./test/additional_test/test14.$(BASE)
	./interp ./test/additional_test/test15.$(BASE)
	./interp ./test/additional_test/test16.$(BASE)
	./interp ./test/additional_test/test17.$(BASE)
	./interp ./test/additional_test/test18.$(BASE)
	./interp ./test/additional_test/test19.$(BASE)
	./interp ./test/additional_test/test20.$(BASE)
	./interp ./test/additional_test/test21.$(BASE)
	./interp ./test/additional_test/test22.$(BASE)
	./interp ./test/additional_test/test23.$(BASE)
	./interp ./test/additional_test/test24.$(BASE)
	./interp ./test/additional_test/test25.$(BASE)
	./interp ./test/additional_test/test26.$(BASE)
	./interp ./test/additional_test/test27.$(BASE)
	./interp ./test/additional_test/test28.$(BASE)
	./interp ./test/additional_test/test29.$(BASE)
	./interp ./test/additional_test/test30.$(BASE)
	./interp ./test/additional_test/test31.$(BASE)

clean :
	rm -fr $(EXECS)
