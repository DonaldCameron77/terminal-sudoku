/*
	Implementation of Sudoku Model's solving routine(s) - both
	brute force and finesse.
*/

#include <iostream>
#include <cmath>

#include "sudoku.h"
#include "view.h"
					
using namespace std;
		
/* The idea is to repeatedly run the finesse strategies in order
   until none of them succeed, after which the brute force backtracking
   algorithm takes over.
   Cf. http://www.sudokudragon.com/sudokustrategy.htm, though most
   authorities use different names for many of the techniques.
 */
 
void sgame::solve()
{
	/* Pseudocode
		try in order
			Full House (only choice)
			Single possibility
			Scanning or cross-hatching in
				3x3 block
				row
				column
			locked candidates (direct pointing)
			
		This iniitial version of the program tries to find
		a solution without filling in all candidates, although
		pairs in a block/row/column may be recognized
	*/

	if (solve_helper(0, 0)) {
		write_line((const char *)"\nSolution");
		display_grid(puzzle);
	}
	else
		write_line((const char *)"\nSOLVE ATTEMPT FAILED!\n");
		
}
 
bool sgame::solve_helper(unsigned row, unsigned col) {
	/* Pseudocode
		try in order
			Full House (only choice)
			Single possibility
			Scanning or cross-hatching in
				3x3 block
				row
				column
			locked candidates (direct pointing)
			
		This iniitial version of the program tries to find
		a solution without filling in all candidates, although
		pairs in a block/row/column may be recognized
	*/
	// For now, only this
	// Brute force and backtracking
	
	// the next two outer "ifs" make the recursion
	// snake across and then down the grid
	if (col == SEDGE) {
		// finished with row
		col = 0;
		if (++row == SEDGE) {
			// entire grid has been filled
			return true;
		}
	}
	
	if (grid[row][col].get_val() != 0) {
		// nonempty cell - advance to next column
		return solve_helper(row, col+1);
	}
	
	for (unsigned val = 1; val <= SEDGE; ++val) {
		// try values in turn for current cell
		if (valid_insertion(val, row, col)) {
			grid[row][col].set_val(val);
#ifdef DEBUG
			cout << "grid["<<row<<"]["<<col<<"] set to "<<val<<endl;
#endif
			if (solve_helper(row, col+1)) {
				return true;
			}
			else {
				// failed downstream so undo the assignment
				grid[row][col].set_val(0);
			}
		}
	}
	
	return false;
}
 
 bool sgame::valid_insertion(
 			 unsigned value, unsigned row, unsigned col )
 {
 	// a trial value has been chosen for a previously-valid
 	// grid at indices [row][column].  If the value were inserted,
 	// would the board still be valid?
 	// Must check the neighbors of row and column - the other row
 	// and column cells, and the 3x3 block
 	
 	// check row
 	for (unsigned r = 0; r < SEDGE; r++) {
 		if (grid[r][col].get_val() == value) {
#ifdef DEBUG1
			cout << "conflict at row " << r
				 << ", column " << col << ", for value "
				 << value << endl;
			cout << "grid[row][col] is " 
			     << grid[r][col].get_val() << endl;
			display_grid(puzzle);
#endif
 			return false;
 		}
 	}
 	
 	// check column
 	for (unsigned c = 0; c < SEDGE; c++) {
 		if (grid[row][c].get_val() == value) {
 			return false;
 		}
 	}
 	
 	// check block
 	unsigned const blocksize = (unsigned)sqrt(SEDGE); // i.e., 3
 	
 	unsigned const rstart = (row/blocksize) * blocksize;
 	unsigned const rlim = rstart + blocksize - 1;
 	unsigned const cstart = (col/blocksize) * blocksize;
 	unsigned const clim = cstart + blocksize - 1;
 	
 	for (unsigned r = rstart; r <= rlim; ++r) {
 		for (unsigned c = cstart; c <= clim; ++c) {
 			if (grid[r][c].get_val() == value) {
 				return false;
 			}
 		}
 	}
 	
 	return true; // no conflict found
 }  			


// EOF


