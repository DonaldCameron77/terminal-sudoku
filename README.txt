README for Sudoku

The design pattern follows MVC.

The VIew simply prints the board to the terminal at appropriate points.  Other information may also be output.  The View module is encapsulated to hopefully allow substitution with a GUI interface later.

The Controller begins with main.  It invokes the controller to get a puzzle (from stdin or a file argument).  Once the game (in the Model) is initialized, the Controller and model interaction involves solve steps.  See Stewart's web app for an idea of how the steps might be presented.

The Model encapsulates the grid and the solving regime.

Controller.cpp - calls routine in Puzzle.cpp to get the initial grid.

Sudoku.cpp - Model

View.cpp - print routines, mostly.

----------------------------------------

Initial checkin: backtracking solutions are working in shame::solve() in solve.cpp.

