# A single file (nal.c) is used to build both the parser & interpreter
CFLAGS = -Wall -Wextra -pedantic -ansi -O2 -lm
SFLAGS = -fsanitize=address -fsanitize=undefined -g3 -lm
DFLAGS = -Wall -Wextra -pedantic -ansi -g3 -lm
CC = clang
BASE = nal
BEXECS = parse interp
SEXECS = parse_s interp_s
DEXECS = parse_d interp_d
EXECS = $(BEXECS) $(SEXECS) $(DEXECS)

all : $(BEXECS)

# I use mvm created previously to store variables ?!
parse : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(CFLAGS) -o $@
parse_s : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(SFLAGS) -o $@
parse_d : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(DFLAGS) -o $@

# I #define INTERP (via this makefile) so that only the extra code for
# the interpreter is inside #ifdef INTERP / #endif 'brackets'
interp : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(CFLAGS) -o $@ -DINTERP
interp_s : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(SFLAGS) -o $@ -DINTERP
interp_d : $(BASE).c $(BASE).h mvm.c mvm.h
	$(CC) $(BASE).c mvm.c $(DFLAGS) -o $@ -DINTERP

test : testparse testinterp

testparse : parse_s parse_d
	./parse_s test1.$(BASE)
	./parse_s test2.$(BASE)
	./parse_s test3.$(BASE)
	./parse_s test4.$(BASE)
	./parse_s test5.$(BASE)
	./parse_s test6.$(BASE)
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
	valgrind ./interp_d test1.$(BASE)
	valgrind ./interp_d test2.$(BASE)
	valgrind ./interp_d test4.$(BASE)
	valgrind ./interp_d test5.$(BASE)

clean :
	rm -fr $(EXECS)
