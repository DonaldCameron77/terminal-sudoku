
// Provides access to exported items from the View (ala MVC) module

#ifndef VIEW_H_INCLUDED

#define VIEW_H_INCLUDED

#include "sudoku.h"

extern void display_grid( sgame & puzzle );

extern void write_line( const char * p );

#endif // VIEW_H_INCLUDED
