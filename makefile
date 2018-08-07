CC=gcc
CFLAGS=-Wall

#
# Set vpath so c file are located in src
# and o files are in obj
#
vpath %.c src
vpath %.o obj

#source := $(wildcard *.c) 
objects := $(addprefix obj/, $(patsubst %.c,%.o,$(wildcard *.c)))

search: $(objects)

%.o: %.c




clean: 
	rm -f bin/search
	rm -rf obj/

.PHONY : clean
