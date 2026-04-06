# Makefile for Dave's Shell
# Full-featured Unix shell with job control, pipes, and redirection

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L
TARGET = shell

# Source files
SRCS = t.c run.c l.c s.c util.c
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = jobs.h util.h

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS) *.o

# Rebuild
rebuild: clean all

# Install (optional)
install: $(TARGET)
	@echo "Installing to ~/bin/dshell"
	@mkdir -p ~/bin
	@cp $(TARGET) ~/bin/dshell
	@echo "Add ~/bin to your PATH if not already there"

# Uninstall
uninstall:
	rm -f ~/bin/dshell

# Run
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: rebuild

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the shell (default)"
	@echo "  clean    - Remove built files"
	@echo "  rebuild  - Clean and build"
	@echo "  run      - Build and run the shell"
	@echo "  debug    - Build with debug symbols"
	@echo "  install  - Install to ~/bin/dshell"
	@echo "  help     - Show this help"

.PHONY: all clean rebuild install uninstall run debug help
