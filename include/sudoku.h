/*
	sudoku.h - for now, sole header file for sudoku "model"
*/

/* Items for the sudoku "model" */

#ifndef SUDOKU_H_INCLUDED

#define SUDOKU_H_INCLUDED

#include <vector>

// namespace sudoku {

	const unsigned CELL_CT = 81;

	const unsigned SEDGE = 9; // grid fixed at 9x9 for now

	// cell and sgame are not initialized by constructors
	
	class cell {
   		unsigned val; // init to zero
   		bool given;  // givens are not changeable
   		// may eventually have a bitset for candidates here
   	public:
   		cell() {} // do we need this default for resize of grid?
   		cell( unsigned value, bool is_given)
   			: val(value), given(is_given) {}
   		void set_val( unsigned v ) { val = v; }
   		unsigned get_val() { return val; }
   		// bool get_given()	{return given; }
	};

	class sgame {
		std::vector <std::vector <cell> > grid;
		friend class grid_iter;
		// block iterator
		// column iterator
		// row iterator
		bool solve_helper(unsigned row, unsigned col);
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
		// These methods return cells by value.
		grid_iter() { row = col = 0; }
		cell next ( sgame & puzzle );
		bool end ();
	};

// defined in sudoku.cpp
extern sgame puzzle; // ack! a global variable? what is better?

// } // namespace sudoku

#endif // SUDOKU_H_INCLUDED

