.SUFFIXES:            # Delete the default suffixes
.SUFFIXES: .c .o .h   # Define our suffix list

CC=gcc
CFLAGS=-Wall -MD -MP -g

#
# Create directories
#
$(shell mkdir -p src/obj > /dev/null 2>&1)
$(shell mkdir -p bin  > /dev/null 2>&1)

src := $(wildcard src/*.c) 
obj := $(src:src/%.c=src/obj/%.o)

#$(info src: $(src))

# main app
bin/search: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

# Obj files
src/obj/%.o : src/%.c  
	$(CC) -c $(CFLAGS) -o $@ $<

# Include dependencies
-include $(src:src%.c=src/obj/%.d)

all: bin/search

clean: 
	rm -f bin/search
	rm -rf src/obj/

.PHONY : clean dir makefile
