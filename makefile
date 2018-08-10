.SUFFIXES:            # Delete the default suffixes
.SUFFIXES: .c .o .h   # Define our suffix list

CC=gcc
CFLAGS=-Wall -MD -MP


src := $(wildcard src/*.c) 
obj := $(src:src/%.c=src/obj/%.o)
$(info src: $(src))

bin/search: $(obj)
	$(CC) -o $@ $^

$(obj): $(src) | dir
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

dir :
	mkdir -p src/obj
	mkdir -p bin 

clean: 
	rm -f bin/search
	rm -rf src/obj/

.PHONY : clean dir makefile
