IDIR =includes
CC=g++
CFLAGS=-I$(IDIR) -ftest-coverage -fprofile-arcs -std=c++11 -g
ODIR=obj

_DEPS_TEST= catch.hpp board.hpp
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS_TEST))

_OBJ_TEST = test_main.o test_board.o board.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

_DEPS= board.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS_TEST)
	$(CC) -c -o $@ $< $(CFLAGS)

jogo: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test:  $(OBJ_TEST)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/* *~ core $(IDIR)/*~ 