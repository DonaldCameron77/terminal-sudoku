/*
	sudoku.h - for now, sole header file for sudoku "model"
*/

#ifndef SUDOKU_H_INCLUDED

#define SUDOKU_H_INCLUDED

#include <vector>
#include <set>

// namespace sudoku { // either use this or get rid of it

	const unsigned SEDGE = 9; // grid fixed at 9x9 for now
	
	const unsigned CELL_CT = SEDGE * SEDGE; // i.e., 81

	// cell and sgame are not initialized by constructors
	
	class cell {
   		unsigned val; // init to zero
   		bool given;  // givens are not changeable
		friend class sgame;
		// prog_candiates are cell possibles for the program's use.
		// If the user enters his own candidates, it will be into
		// a parallel data structure TBD.
		// For now, we will only maintain this vector for cells
		// not containing settled values ... non-settled values are
		// indicated by a cell value of 0.  This structure is initialized
		// in sudoku.h - sgame::init_grid()
   		std::set<unsigned> prog_cand;
   	public:
   		cell() {} // do we need this default for resize of grid?
   		cell( unsigned value, bool is_given ) 
   			: val(value), given(is_given) {} 
   		void set_val( unsigned v ) { val = v; }
		unsigned get_val() { return val; }
		// bool get_given()	{return given; }
/* clean up later
		void set_candidate(unsigned val, bool is_cand) {
		    prog_cand[val] = is_cand;
		}
*/
		// Always remove individual candidates.  We reset prog_cand to the
		// initial "all true" state by copying an entire candidate set.
		// Note: we are not checking that we are erasing an element no
		// longer present in the set.  But apparently that's ok.
		void remove_candidate(unsigned sval) {
			prog_cand.erase(sval);
		}
		void reset_cands(std::set<unsigned> & s) { // only call with sgame::all_set
		    prog_cand = s;
		}
	};

	class sgame {
		std::vector <std::vector <cell> > grid;
		friend class grid_iter;
		// block iterator
		// column iterator
		// row iterator
		std::set<unsigned> all_set; //dummy with all vals set to init candidate sets
		void set_all_candidates(); // set candidates for entire grid
		void reset_candidates(unsigned row, unsigned col);
		void set_cell_candidates( unsigned row, unsigned col);
		bool backtracker(unsigned row, unsigned col); // solver of last resort
		bool valid_insertion(
 			 unsigned value, unsigned row, unsigned col );
	public:
		sgame(); // might try singleton pattern eventually
		void init_grid( std::vector<unsigned> & inbuf );
		void solve();
	};
	
	// this is not up to STL standards, but it does isolate the View
	// component from any knowledge of how the grid is stored.
	class grid_iter {
		size_t row, col;
	public:
		// Usage: declare an object of this type, call first() to
		// init the iteration and get the first item.  Call next() for
		// subsequent items.  How will last() work?
		// THESE METHODS RETURN CELLS BY VALUE!?!
		grid_iter() { row = col = 0; }
		cell & next ( sgame & _puzzle );
		bool end ();
	};

// defined in sudoku.cpp
extern sgame puzzle; // ack! a global variable? what is better?

// } // namespace sudoku

#endif // SUDOKU_H_INCLUDED

