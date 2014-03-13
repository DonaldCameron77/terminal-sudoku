/*
	Implementation of Sudoku Model's solving routine(s) - both
	brute force and finesse.
*/

#include <iostream>
#include <cmath>
#include <cassert>

#include "sudoku.h"
#include "view.h"
					
using namespace std;
		
/* The idea is to repeatedly run the finesse strategies in order
   until none of them succeed, after which the brute force backtracking
   algorithm takes over.
   Cf. http://www.sudokudragon.com/sudokustrategy.htm, though most
   authorities use different names for many of the techniques.

   The spin on this program may be learning how to do easier to medium
   puzzles on paper (though newspaper puzzles labelled 'evil' are generally
   easier than the harder puzzles today's apps provide).

	Techniques:
		- Name??: Only one choice for cell when considering all neighbors: 
		equivalent to naked single where there is more than one empty cell in
		the surrounding block, row, and column. Appears to the program as a
		Naked Single.
		
		- Full House: Only one choice for cell when considering only its row,
		or only its column, or only its block.  This is a "Full House" condition
		and again shows up as a Naked Single.
		
		- Scanning or Crosshatching (Block): When considering each value (in 
		turn) in or intersecting a block, there is only one cell in the block 
		which can have the current value. Equivalent to Hidden Single.
		
		- Scanning or Crosshatching (Row, Column): When considering each value 
		(in turn) in or intersecting a row or column, there is only one cell in
		the row or column  which can have the current value. Equivalent to
		Hidden Single.

		From a human viewpoint, each of these techniques is different, but a 
		program would probably just compute all candidates and check for Naked
		and Hidden Singles. If we want to report to the user as though we had
		applied each of the above techniques in turn, some extra checking might
		be needed.

		The next set of human techniques involve further restricting the 
		possibilities for a cell.

		- Naked Pairs: Two cells in a row which can each have only the same two 
		values implies no other cell in that unit can have those values.  Those 
		values can then be eliminated from any cells which neighbor both
		original cells.

		Having found a Naked Pair in a Unit, when there are only two other 
		empty cells in the Unit, those latter cells must contain the remaining
 		available  symbol values, i.e., another pair.  And if there are three
 		empty cells remaining, then the three remaining values (i.e., a Triple)
 		are all that can be placed there.

		- Locked Candidates (direct pointing): It may appear that symbol S can 
		go in more than one row within block B, but a neighboring block
		must place S in row R ... thus, S can be eliminated from row R within 
		B. Of course, this works for columns also.

		Most newspaper puzzles are solvable with these techniques, 
*/

void Sgame::place_val(unsigned val, unsigned row, unsigned col) {
    Cell & the_cell = grid[row][col];
    assert(the_cell.get_val() == 0);
    the_cell.set_val(val);
    
    // now remove val from neighbors (row, column, block) candidate sets
    // check column
 	for (unsigned r = 0; r < SEDGE; r++) {
 	    Cell & tmp_cell = grid[r][col];
 		if (tmp_cell.get_val() == 0) {
            tmp_cell.remove_candidate(val);
 		}
 	}
 	
 	// check row
 	for (unsigned c = 0; c < SEDGE; c++) {
 	    Cell & tmp_cell = grid[row][c];
 		if (tmp_cell.get_val() == 0) {
 			tmp_cell.remove_candidate(val);
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
 		    Cell & tmp_cell = grid[r][c];
 			if (tmp_cell.get_val() == 0) {
 				tmp_cell.remove_candidate(val);
 			}
 		}
 	}    
}

bool Sgame::try_naked_singles() {
    // for production version, could start at a random block (being sure to still
    // visit all blocks), but for predictability in development, don't do this!
    for (unsigned row = 0; row < SEDGE; ++row) {
        for (unsigned col = 0; col < SEDGE; ++col) {
            unsigned val;
            Cell & the_cell = grid[row][col];
            if (the_cell.get_val() == 0 && the_cell.is_naked_single(val)) {
                place_val(val, row, col);
                cout << "\nNaked single " << val << 
                    " placed at (" << row << "," << col << ")\n";
                display_grid(puzzle);
                return true;
            } 
        }
    }
    return false;
}

void Sgame::solve()
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
			
		This initial version of the program tries to find
		a solution without filling in all candidates, although
		pairs in a block/row/column may be recognized
	*/

	// Techniques go here in order, in a loop. If technique k succeeds,
	// then the remaining ones are skipped (issue continue stmt),
	// unless puzzle is completed.  If all techs fail, fall out of
	// loop and do backtracking (i.e., call solve_helper()).
	// Program this part top-down.
	
	init_all_candidates();
	
	bool changed = true;
	
	while (changed) {
	    if ((changed = try_naked_singles()) == true) continue;
	}

	// Backtracking algorithm - guaranteed to work if there's a solution
	
	if (backtracker(0, 0)) {
		write_line((const char *)"\nSolution:");
		display_grid(puzzle);
	}
	else
		write_line((const char *)"\n ATTEMPT FAILED!\n");
		
}
 
bool Sgame::backtracker(unsigned row, unsigned col) {
	/* Pseudocode
		try in order
			Full House (only choice)
			Single possibility
			Scanning or cross-hatching in
				3x3 block
				row
				column
			locked candidates (direct pointing)
			
		This initial version of the program tries to find
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
		return backtracker(row, col+1);
	}
	
	for (unsigned val = 1; val <= SEDGE; ++val) {
		// try values in turn for current cell
		if (valid_insertion(val, row, col)) {
			grid[row][col].set_val(val);
#ifdef DEBUG
			cout << "grid["<<row<<"]["<<col<<"] set to "<<val<<endl;
#endif
			if (backtracker(row, col+1)) {
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
 
 bool Sgame::valid_insertion(
 			 unsigned value, unsigned row, unsigned col )
 {
 	// a trial value has been chosen for a previously-valid
 	// grid at indices [row][column].  If the value were inserted,
 	// would the board still be valid?
 	// Must check the neighbors of row and column - the other row
 	// and column cells, and the 3x3 block
 	
 	// check column
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
 	
 	// check row
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


