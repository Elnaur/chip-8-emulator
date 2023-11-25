#
# Makefile for CHIP-8 emulator
#

# compiler flags (uncomment DEBUG for debugging)
# DEBUG    = -ggdb
OPTIMISE  = -O2
WARNINGS  = -Wall -Wextra -Wno-variadic-macros -Wno-overlength-strings -pedantic
CFLAGS    = $(DEBUG) $(OPTIMISE) $(WARNINGS)
LDLIBS    = 

# commands
CC        = clang
RM        = rm -f
COMPILE   = $(CC) $(CFLAGS) $(LDLIBS)

# file and folder rules
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)

EXECUTABLE = obj/emulator 

all: clean compile run

compile: $(OBJS)
	$(COMPILE) -o $(EXECUTABLE) $(OBJS)

run: 
	@echo Running...
	@./$(EXECUTABLE)

obj/%.o: src/%.c | obj 
	$(COMPILE) -o $@ -c $<

obj:
	mkdir -p $@

clean:
	rm -f obj/*.o
	rm ${EXECUTABLE} 