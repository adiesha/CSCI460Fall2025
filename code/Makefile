CC=gcc
CFLAGS=-Wall
PROGRAMS=thread_initial test_signal_handler fork mutex_example semaphore_example thread_advance

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
