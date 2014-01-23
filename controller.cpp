
/*  Sudoku controller - this version assumes puzzle givens are
    supplied via a command-line argument referencing a file, or
    via stdin
*/
    
#include <iostream>
#include <fstream>
#include <vector>

#include "sudoku.h"
#include "view.h"

using namespace std;
// using namespace sudoku;

// extern class sgame game; // for now

void get_puzzle( ifstream & ifs, vector<unsigned> & givens)
{
	unsigned givens_seen = 0;
	while (givens_seen < CELL_CT) {
		unsigned char c;
		ifs >> c;
		unsigned val;
		// anything except digit chars 0..9 and . are ignored
		if (c == '.')
			c = '0';
		if (c >= '0' && c <= '9') {
			val = c - '0';
			givens.push_back(val);
			givens_seen++;
		}
	}	
}
    
int main(int argc, char *argv[])
{
	// Can we assume the grid already exists?  Does it have to
	// thus be a global variable?
	
	if (argc > 2) {
		cerr << argv[0] << ": excess arguments on command line" << endl;
		return 1;
	}
	
	ifstream ifs(argv[1]);
	
	vector<unsigned> givens; // temp storage for initial board
							// better to not have this in main,
							// where it consumes storage for the 
							// entire execution?
	get_puzzle(ifs, givens);
	
// #ifdef DEBUG
	cout << "size of givens vector: " << givens.size() << endl;
	for (unsigned i = 0; i < givens.size(); i++) {
		cout << givens[i];
	}
	cout << endl;
// #endif

	puzzle.init_grid(givens);
	display_grid(puzzle);
	puzzle.solve();
	// display_grid(puzzle);
	
	return 0;	
}
	
// EOF

