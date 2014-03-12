/*
	Candidate management - see classes Sgame and Cell
	brute force and finesse.
*/

#include <cmath>

#include "sudoku.h"
					
using namespace std;
		
void Sgame::reset_candidates(unsigned row, unsigned col) {
    grid[row][col].reset_cands(all_set);
}

// For each value in cells neighboring an empty cell,
// remove its value from this cell's candidate list.
void Sgame::set_cell_candidates( unsigned row, unsigned col )
{
    
    Cell & the_cell = grid[row][col];
    if (the_cell.get_val() != 0) return; // nonempty cells don't have/need candidates
    
    // Uses set assignment to copy over a pre_initialized set containing 1..9.
    // We can use this same canned set for all resets. However, we anticipate
    // only initializing the candidates once, and updating them as solve techniques
    // are applied successfully.
    reset_candidates(row, col);
    
    // do column
 	for (unsigned r = 0; r < SEDGE; r++) {
 		unsigned neighbor_value = grid[r][col].get_val();
        the_cell.remove_candidate(neighbor_value);
 	}
 	
 	// do row
 	for (unsigned c = 0; c < SEDGE; c++) {
 		unsigned neighbor_value = grid[row][c].get_val();
        the_cell.remove_candidate(neighbor_value);
 	}
 	
 	// do 3x3 block containing row, col
 	static unsigned const blocksize = (unsigned)sqrt(SEDGE); // i.e., 3
 	
 	unsigned const rstart = (row/blocksize) * blocksize;
 	unsigned const rlim = rstart + blocksize - 1;
 	unsigned const cstart = (col/blocksize) * blocksize;
 	unsigned const clim = cstart + blocksize - 1;
 	
 	for (unsigned r = rstart; r <= rlim; ++r) {
 		for (unsigned c = cstart; c <= clim; ++c) {
 			unsigned neighbor_value = grid[r][c].get_val();
 			the_cell.remove_candidate(neighbor_value);
 		}
 	}
}
 
void Sgame::set_all_candidates()
{
    // Do for each cell in grid ...
    for (unsigned row = 0; row < SEDGE; ++row) {
        for (unsigned col = 0; col < SEDGE; ++ col) {
            set_cell_candidates(row, col);
        }
    }
}

bool Cell::is_naked_single( unsigned & val) {
	if (prog_cand.size() != 1) return false;
/*
	for (auto it = prog_cand.begin(); it != prog_cand.end(); it++) {
		if (it->find(
	}
*/
	auto it = prog_cand.begin(); // best way to get single unknown val?
	val = *it;
	return true;
}

// EOF

