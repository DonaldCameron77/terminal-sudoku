/*
	Implementation of Sudoku Model
*/

#include "sudoku.h" // might rename to just sudoku if we use
					// local include directory

// using namespace sudoku;

Cell & Grid_iter::next( Sgame & _puzzle )
{
	Cell & c = _puzzle.grid[row][col++];
	if (col == SEDGE) {
		++row;
		col = 0;
	}
	return c;
}

bool Grid_iter::end() {
	// if you call next() and get the last item, then
	// on that call col will be set back to zero and row incremented
	// to SEDGE (beyond the bottom of the grid)
	return row == SEDGE;
}

Sgame puzzle; // ack! a global variable? what is better?

Sgame::Sgame()
{
	// private constructor - will resize grid to SEDGE x SEDGE (9x9)
	grid.resize(SEDGE);
	for (size_t i = 0; i < SEDGE; ++i)
		grid[i].resize(SEDGE);
	
/*
	// use this to initialize candidates	
	for (size_t i = 1; i <= SEDGE; ++i) {
	    all_set.insert(i);
	}
*/
    all_set = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
}
				
void Sgame::init_grid( std::vector<unsigned> & inbuf )
{	
	// Givens (and empty cells denoted by 0) appear in inbuf
	// in row_major order. We are guaranteed to have a total
	// of 81 items in inbuf in the range 0..9.
	
	for (unsigned row = 0; row < SEDGE; row++) {
		for (unsigned col = 0; col < SEDGE; col++)
		{
			unsigned value = inbuf[ row * SEDGE + col ];
			Cell ctmp(value, value != 0);
			grid[row][col] = ctmp;
		}
	}
}

// EOF

