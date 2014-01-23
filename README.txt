README for Sudoku

The design pattern follows MVC, insofar as I am able to apply it.

The View module's job in this simple terminal incarnation is to print the board to stdout at appropriate points. 
Other information may also be output.  The View module is encapsulated to hopefully allow substitution with a GUI
interface later.

The Controller begins with main(),  which invokes a Controller routine to get a puzzle (from the sole file
command-line argument).  Once the game (in the Model) is initialized, the Controller and Model interaction involves solve steps, though in the initial version, backtracking is the only solve step.  See Andrew Stewart's web app
(www.sudokuwiki.org/sudoku.htm) for an idea of how the steps might be presented as they are implemented.

sudoku.cpp, solve.cpp - the Model which encapsulates the grid and the solving regime.

controller.cpp - main program flow logic, and in charge of getting input.

View.cpp - just print routines in the initial terminal version.

Phase I is to get solving working as a terminal application, reading the puzzle givens from the lone file argument,
and adding human-friendly solve steps like Crosshatching/Scanning, Full House, Single Alternative, etc.

----------------------------------------

Initial checkin: backtracking solution is working in sgame::solve() in solve.cpp.

