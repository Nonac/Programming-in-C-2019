CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -O2 -Werror
DEBUGFLAGS = -g3
SANITIZEFLAGS = -fsanitize=address -fsanitize=undefined -g3
TARGET = testset
DTARGET = $(TARGET)_d
STARGET = $(TARGET)_s
# Lab machines might not have a recent enough gcc ?
CC = gcc

# Build testarr, using all the 'normal' flags
$(TARGET): set.c set.h arr.c arr.h $(TARGET).c
	$(CC) $(TARGET).c arr.c set.c -o $@ $(CFLAGS)

# Remove an executables we've built
clean:
	rm -f $(TARGET) $(DTARGET) $(STARGET)

# Run the code
run: $(TARGET)
	./$(TARGET)

# Build testarr_d, an executable suitable for debugging with
$(DTARGET): set.c set.h arr.c arr.h $(TARGET).c
	$(CC) $(TARGET).c arr.c set.c -o $@ $(DEBUGFLAGS)

# Build testarr_d, an executable suitable for debugging with
$(STARGET): set.c set.h arr.c arr.h $(TARGET).c
	$(CC) $(TARGET).c arr.c set.c -o $@ $(SANITIZEFLAGS)

# Run the (debug) code using with memory-leak checking
memleak: $(DTARGET) $(STARGET) 
	@echo "Valgrind memory leaks :"
	@valgrind --error-exitcode=1 --quiet --leak-check=full ./$(DTARGET)
	@echo "Checking Sanitize :"
	@./$(STARGET)

.PHONY: clean run memleak
