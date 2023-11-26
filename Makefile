#
# Makefile for CHIP-8 emulator
#

# compiler flags (uncomment DEBUG for debugging)
# DEBUG    = -ggdb
OPTIMISE  = -O2
WARNINGS  = -Wall -Wextra -Wno-variadic-macros -Wno-overlength-strings -pedantic
SDL2	  = $(sdl2-config --cflags --libs)
CFLAGS    = $(DEBUG) $(OPTIMISE) $(WARNINGS)
LDLIBS    = 

# commands
CC        = clang
RM        = rm -f
COMPILE   = $(CC) $(CFLAGS) $(LDLIBS) $(SDL2)

# file and folder rules
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)

EXECUTABLE = obj/emulator 

all: clean compile run

compile: $(OBJS)
	@echo Compiling...
	$(COMPILE) -o $(EXECUTABLE) $(OBJS)
	@echo

run: 
	@echo Running...
	@./$(EXECUTABLE)
	@echo

obj/%.o: src/%.c | obj 
	$(COMPILE) -o $@ -c $<

obj:
	mkdir -p $@

.PHONY: clean

clean:
	@echo Cleaning...
	@-rm -f obj/*.o
	@-rm ${EXECUTABLE} 
	@echo
