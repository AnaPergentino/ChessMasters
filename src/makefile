IDIR =includes
CC=g++
CFLAGS=-I$(IDIR) -ftest-coverage -fprofile-arcs -std=c++11 -g
ODIR=obj

_DEPS_TEST= catch.hpp board.hpp ia.hpp
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS_TEST))

_OBJ_TEST = test_main.o test_board.o board.o ia.o test_ia.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

_DEPS= board.hpp io.hpp ia.hpp PGN.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o board.o io.o ia.o PGN.o
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
