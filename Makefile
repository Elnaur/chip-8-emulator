#
# Makefile for CHIP-8 emulator
#

# compiler flags (uncomment DEBUG for debugging)
# DEBUG     	= -ggdb
OPTIMISE   	= -O2
WARNINGS   	= -Wall -Wextra -Wno-variadic-macros -Wno-overlength-strings -pedantic
SDL2	   	= $(sdl2-config --cflags --libs)
CFLAGS     	= $(DEBUG) $(OPTIMISE) $(WARNINGS)
LDLIBS     	= 

# commands
CC         	= clang
RM         	= rm -f
COMPILE    	= $(CC) $(CFLAGS) $(LDLIBS) $(SDL2)

# file and folder rules
SRCS	   	= $(wildcard src/*.c)
OBJS	   	= $(SRCS:src/%.c=obj/%.o)
DEPS	   	= $(SRCS:src/%.c=include/%.h)

EXECUTABLE	= obj/emulator 

all: clean compile run

# Rules

compile: $(OBJS)
	@echo Compiling executable
	$(COMPILE) -o $(EXECUTABLE) $(OBJS)
	@echo

run: 
	@echo Running executable...
	@./$(EXECUTABLE)
	@echo

obj/%.o: src/%.c | obj
	@echo Compiling files and headers
	@if [ -e include/$(notdir $*).h ]; then \
		echo Compiling $< with header file...; \
		$(COMPILE) -o $@ -c $<; \
	else \
		echo Compiling $< without header file...; \
		$(COMPILE) -o $@ -c $< -DNO_HEADER; \
	fi
	@echo 

obj:
	mkdir -p $@

.PHONY: clean

clean:
	@echo Cleaning
	@-rm -f obj/*.o
	@-rm ${EXECUTABLE} 
	@echo
