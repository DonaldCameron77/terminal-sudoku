/*
	Implementation of Sudoku Model
*/

#include "sudoku.h" // might rename to just sudoku if we use
					// local include directory

// using namespace sudoku;

cell & grid_iter::next( sgame & puzzle )
{
	cell & c = puzzle.grid[row][col++];
	if (col == SEDGE) {
		++row;
		col = 0;
	}
	return c;
}

bool grid_iter::end() {
	// if you call next() and get the last item, then
	// on that call col will be set back to zero and row incremented
	// to SEDGE (beyond the bottom of the grid)
	return row == SEDGE;
}

sgame puzzle; // ack! a global variable? what is better?

sgame::sgame() {
	// private constructor - will resize grid to SEDGE x SEDGE (9x9)
	grid.resize(SEDGE);
	for (size_t i = 0; i < SEDGE; i++)
		grid[i].resize(SEDGE);
}
				
void sgame::init_grid( std::vector<unsigned> & inbuf )
{	
	// Givens (and empty cells denoted by 0) appear in inbuf
	// in row_major order. We are guaranteed to have a total
	// of 81 items in inbuf in the range 0..9.
	
	for (unsigned row = 0; row < SEDGE; row++) {
		for (unsigned col = 0; col < SEDGE; col++)
		{
			unsigned value = inbuf[ row * SEDGE + col ];
			cell ctmp(value, value != 0);
			if (value == 0) {
				// cell does not contain "given" (initial value),
				// so initialize a candidate vector (to default val of true)
				ctmp.prog_cand.resize(SEDGE+1, true);
			}
			grid[row][col] = ctmp;
		}
	}
}

// EOF

