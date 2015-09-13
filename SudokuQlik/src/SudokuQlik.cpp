//============================================================================
// Name        : SudokuQlik.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <fstream>


#include "Sudoku.h"
#include "Solver.h"


using namespace std;
using namespace sudoku;

int main() {
	cout << "SudokuQlik" << endl << endl; // prints SudokuQlik


    Puzzle * p = new Puzzle();

    cout << "Example1:" << endl;
    p->load("./src/example1.txt");
    Solver * s = new BTSolver(p);
    if (!s->solve())
    {
    	if (s->getError() > 0)
    	{
    		if (s->getError() & SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION)
    		{
    			cout << endl << "Unsolvable configuration!!!" << endl;
    		}
    		else if (s->getError() & SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE)
    		{
    			cout << endl << "Inconsistent internal state!!!" << endl;
    		}
    	}
    }

    cout << endl << "The solution is:" << endl;
    s->printToConsole();

    cout << endl << endl;



    cout << "Example2:" << endl;
    p->load("./src/example2.txt");
    cout << endl << endl;

    cout << "Example3:" << endl;
    p->load("./src/example3.txt");
    cout << endl << endl;

    cout << "Example4:" << endl;
    p->load("./src/example4.txt");
    cout << endl << endl;



    delete p;


    char c = 0101;
    cout << c ;

	return 0;
}
