CC=gcc
CFLAGS=-Wall
PROGRAMS=buffer1 buffer2

# Default target
all: $(PROGRAMS)

# Rule to compile .c files into executables
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Rules to run each program
run-%: %
	./$<

# Clean up executables
clean:
	rm -f $(PROGRAMS)
