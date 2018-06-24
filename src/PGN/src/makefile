IDIR =includes
CC=g++
CFLAGS=-I$(IDIR) -ftest-coverage -fprofile-arcs -std=c++11 -g
ODIR=obj

_DEPS_TEST=
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS_TEST))

_OBJ_TEST =
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

_DEPS= main.hpp gameHeader.hpp gameMove.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJC = gameHeader.o gameMove.o
OBJC = $(patsubst %,$(ODIR)/%,$(_OBJC))

_OBJMAIN = main.o
OBJMAIN = $(patsubst %,$(ODIR)/%,$(_OBJMAIN))

$(ODIR)/%.o: %.cpp $(DEPS_TEST)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJC) $(OBJMAIN)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean

clean:
	rm -f $(ODIR)/* *~ core $(IDIR)/*~
