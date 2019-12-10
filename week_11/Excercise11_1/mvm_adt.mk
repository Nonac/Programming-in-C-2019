CFLAGS = -O2 -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi
DFLAGS = -g3 -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi
SFLAGS = -g3 -fsanitize=undefined -fsanitize=address
TESTBASE = testmvm
INCS = mvm.h
SOURCES =  $(TESTBASE).c mvm.c
EXECS = $(TESTBASE) $(TESTBASE)_d $(TESTBASE)_s homophone
CC = clang

run: $(TESTBASE)
	./$(TESTBASE) 

all: $(EXECS)

$(TESTBASE): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(TESTBASE)_d: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(DFLAGS) 

$(TESTBASE)_s: $(SOURCES) $(INCS) 
	$(CC) $(SOURCES) -o $@ $(SFLAGS) 

clean:
	rm -f $(EXECS)

memleaks: $(TESTBASE)_d $(TESTBASE)_s
	@echo "Sanitize :"
	@./$(TESTBASE)_s
	@echo "Valgrind :"
	@valgrind --leak-check=full ./$(TESTBASE)_d

