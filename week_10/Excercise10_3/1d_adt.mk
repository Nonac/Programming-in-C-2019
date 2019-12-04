CFLAGS = -Wall -Wextra -Werror -Wfloat-equal -pedantic -ansi -O2 -Werror -Wno-overlength-strings
DEBUGFLAGS = -g3
SANITIZEFLAGS = -fsanitize=address -fsanitize=undefined -g3
BASEARR = varr
TARGET = test$(BASEARR)
DTARGET = $(TARGET)_d
STARGET = $(TARGET)_s
# Lab machines might not have a recent enough gcc ?
CC = gcc

# Build TARGET, using all the 'normal' flags
$(TARGET): $(BASEARR).c $(BASEARR).h $(TARGET).c
	$(CC) $(TARGET).c $(BASEARR).c -o $@ $(CFLAGS)

# Remove an executables we've built
clean:
	rm -f $(TARGET) $(DTARGET) $(STARGET)

# Run the code
run: $(TARGET)
	./$(TARGET)

# Build DTARGET, an executable suitable for debugging with
$(DTARGET): $(BASEARR).c $(BASEARR).h $(TARGET).c
	$(CC) $(TARGET).c $(BASEARR).c -o $@ $(DEBUGFLAGS)

# Build STARGET, an executable suitable for sanitizing with
$(STARGET): $(BASEARR).c $(BASEARR).h $(TARGET).c
	$(CC) $(TARGET).c $(BASEARR).c -o $@ $(SANITIZEFLAGS)

# Run the (debug) code using with memory-leak checking
debug: $(DTARGET) $(STARGET) 
	@echo "Valgrind memory leaks :"
	@valgrind --error-exitcode=1 --quiet --leak-check=full ./$(DTARGET)
	@echo "Checking Sanitize :"
	@./$(STARGET)

.PHONY: clean run debug
