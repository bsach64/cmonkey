# This is can be made much better
TEST=test
LIBDIRS=../lib/
INCDIRS=. ../include/
TESTDIRS=.

CC=clang
OPT=-O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

LIBFILES=$(foreach D, $(LIBDIRS), $(wildcard $(D)/*.c))
TESTFILES=$(foreach D, $(TESTDIRS), $(wildcard $(D)/*.c))

CTESTFILES=$(TESTFILES) $(LIBFILES)

# pattern substitution
TESTOBJECTS=$(patsubst %.c, %.o, $(CTESTFILES))
TESTDEPFILES=$(patsubst %.c, %.d, $(CTESTFILES))

all: $(TEST)

$(TEST): $(TESTOBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(TEST) $(TESTOBJECTS) $(TESTDEPFILES)
