.SUFFIXES:            # Delete the default suffixes
.SUFFIXES: .c .o .h   # Define our suffix list

#
# Set Flags
#
CC=gcc
CFLAGS=-Wall -MD -MP -I../src

#
# Create directories
#
$(shell mkdir -p src/obj > /dev/null 2>&1)
$(shell mkdir -p bin  > /dev/null 2>&1)


src := $(wildcard src/*.c) 
app := bin/tests 
obj := $(src:src/%.c=src/obj/%.o)

#$(info src: $(src))
#$(info obj: $(obj))

# main app
$(app): $(obj)
	$(CC) $(CFLAGS)  -o $@ $^

# Obj files
$(obj): $(src)
	$(CC) -c $(CFLAGS) -o $@ $<

# Include dependencies
-include $(src:src%.c=src/obj/%.d)

test: $(app)
	$(app)

clean: 
	rm -rf bin/
	rm -rf src/obj/

.PHONY : clean dir makefile test
