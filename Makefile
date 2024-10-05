# This is can be made much better
BINARY=cmonkey
LIBDIRS=./lib/
CODEDIRS=.
INCDIRS=. ./include/

CC=gcc
OPT=-O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD
CFLAGS= -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs

CFLAGS += -g $(foreach D,$(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

CODEFILES=$(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
LIBFILES=$(foreach D, $(LIBDIRS), $(wildcard $(D)/*.c))

CFILES=$(CODEFILES) $(LIBFILES)

# pattern substitution
OBJECTS=$(patsubst %.c, %.o, $(CFILES))
DEPFILES=$(patsubst %.c, %.d, $(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)
