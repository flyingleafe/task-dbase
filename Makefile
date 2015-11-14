CC=gcc
CFLAGS=--std=c11 -O2 -I./include

SOURCEDIR=src
BUILDDIR=build

EXECUTABLE=dbase
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
OBJECTS=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))


.PHONY: all clean builddir
all: builddir $(BUILDDIR)/$(EXECUTABLE) link

builddir:
	mkdir -p $(BUILDDIR)

link:
	ln -sf $(BUILDDIR)/$(EXECUTABLE) $(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) randtest *.o *.hi
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)
