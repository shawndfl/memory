.SUFFIXES:            # Delete the default suffixes
.SUFFIXES: .c .o .h   # Define our suffix list

CC=gcc
CFLAGS=-Wall -MD -MP


src := $(wildcard src/*Test.c) 
app := $(src:src/%.c=bin/%.bin) 
obj := $(src:src/%.c=src/obj/%.o)

#$(info src: $(src))

# main app
$(app): $(obj)
	$(CC) $(CFLAGS) -o $@ $^

# Obj files
$(obj): $(src) | dir
	$(CC) -c $(CFLAGS) -o $@ $<

# Include dependencies
-include $(src:src%.c=src/obj/%.d)

dir :
	mkdir -p src/obj
	mkdir -p bin 

clean: 
	rm -rf bin/
	rm -rf src/obj/

.PHONY : clean dir makefile
