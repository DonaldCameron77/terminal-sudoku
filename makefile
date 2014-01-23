#
# Makefile for sudoku = dcc 2014-01-16
#

IDIR =include
CPP=clang++
# DEBUGFLAGS=-DDEBUG
CPPFLAGS=-I$(IDIR) -g -std=c++11 -stdlib=libc++ -Weverything -Wno-logical-op-parentheses -Wno-c++98-compat -Wno-missing-prototypes

ODIR=obj
# LDIR =../lib

# LIBS=-lm

_DEPS = sudoku.h view.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = controller.o sudoku.o view.o solve.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS) $(DEBUGFLAGS)

sudoku: $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

