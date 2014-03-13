/*
	"View" component (in MVC terms) for sudoku.
	
	This version implements a rudimentary terminal view interface.
*/

#include <iostream>
#include <vector>

#include "sudoku.h"

using namespace std;

// To reduce coupling between model (classes Sgame and Cell) and the
// View component, there must be iterators that allow access to the
// grid cell values in appropriate order (row-major).

/*	We have to think not only about a dumb terminal interface,
	but also what will happen with a GUI later.  The user will
	select a cell and manipulate the value stored there.  Or
	they will select a value, and we'll need to highlight all
	the cells with that value. To maintain the fiction that
	only the "model" knows that there is a mapping to a 2-dim
	array may be too much to ask.
*/

/*
	pretty_print() : Make terminal output look like this:
	
		|***|***|***|
		|.3.|...|...|
		|.18|.75|.6.|
		|2..|.94|83.|
		|***|***|***|
		|.7.|642|.89|
		|.9.|...|.2.|
		|54.|983|.7.|
		|***|***|***|
		|.23|41.|..8|
		|.8.|52.|61.|
		|...|...|.4.|
		|***|***|***|
	
*/

enum pstate { before, after, final };

void pretty_print( pstate state,
	 unsigned row = 9, unsigned col = 9)
{
	static const char * rowsep = "|***|***|***|";
	static const char colsep = '|';

// 	cout << "\n";

	// rows and columns are 0-based
	if (col == 0) {
		if (state == before && (row == 0 || row == 3 || row == 6)) {
			cout << rowsep << endl << colsep;
			return;
		}
		if (state == before && row != 9) { // row 1, 2, 4, 5 7, 8
			cout << colsep;
			return;
		}
		if (row == 9) {
			cout << rowsep << endl;
			return;
		}
	}
	
	if (state == after && (col == 2 || col == 5 || col == 8)) {
		cout << colsep;
		return;
	}
	if (state == final) {
		cout << rowsep << endl;
	}
}


void display_grid( Sgame & _puzzle )
{
	Grid_iter g_iter;
	Cell c;
	
	for (unsigned row = 0; row < SEDGE; ++row) {
		for (unsigned col = 0; col < SEDGE; ++col) {
			// FIX-ME: This is brain-damaged, stupid, and redundant.
			// If using an iterator, you should not need to
			// specifically index row/col.  If, OTOH,
			// you need rows and cols, and if the iterator
			// can't or shouldn't provide them, then you don't use
			// an iterator.  Also, pretty print should be simpler
			// and just print the whole grid on one call - duplicated
			// code be damned.
			c = g_iter.next(_puzzle);
			unsigned v = c.get_val();
			pretty_print(before, row, col);
			if (v == 0)
				cout << '.';
			else
				cout << v;
			pretty_print(after, row, col);
		}
		cout << endl;
	}
	pretty_print(final);
}

void write_line( const char * p ) {
	cout << p << endl;
}

// EOF
