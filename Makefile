# This is can be made much better

BINARY=cmonkey
TEST=test
LIBDIRS=./lib/
CODEDIRS=.
INCDIRS=. ./include/
TESTDIRS=./tests/

CC=clang
OPT=-O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

CODEFILES=$(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
LIBFILES=$(foreach D, $(LIBDIRS), $(wildcard $(D)/*.c))
TESTFILES=$(foreach D, $(TESTDIRS), $(wildcard $(D)/*.c))

CFILES=$(CODEFILES) $(LIBFILES)
CTESTFILES=$(TESTFILES) $(LIBFILES)

# pattern substitution
OBJECTS=$(patsubst %.c, %.o, $(CFILES))
DEPFILES=$(patsubst %.c, %.d, $(CFILES))

TESTOBJECTS=$(patsubst %.c, %.o, $(CTESTFILES))
TESTDEPFILES=$(patsubst %.c, %.d, $(CTESTFILES))

all: $(BINARY)

test: $(TEST)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

$(TEST): $(TESTOBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)
