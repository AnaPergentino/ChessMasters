IDIR =includes
CC=g++
CFLAGS=-I$(IDIR) -ftest-coverage -fprofile-arcs -std=c++11 -g
ODIR=obj

_DEPS_TEST= catch.hpp
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ_TEST = test_main.o 
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

$(ODIR)/%.o: %.cpp $(DEPS_TEST)
	$(CC) -c -o $@ $< $(CFLAGS)

jogo: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test:  $(OBJ_TEST)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 