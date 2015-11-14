CC=gcc
CFLAGS=--std=c11 -O2 -I./include
HC=ghc
HFLAGS=-O2

SOURCEDIR=src
BUILDDIR=build

EXECUTABLE=dbase
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
OBJECTS=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))


.PHONY: all clean builddir
all: builddir $(BUILDDIR)/$(EXECUTABLE)

builddir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)

randtest:
	$(HC) $(HFLAGS) randtest.hs -o randtest
