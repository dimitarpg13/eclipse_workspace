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
    Solver * s = NULL;

//    cout << "example1:" << endl;
//    p->load("./src/example1.txt");
//    s = new BTSolver(p);
//    if (!s->solve())
//    {
//    	if (s->getError() > 0)
//    	{
//    		if (s->getError() & SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION)
//    		{
//    			cout << endl << "Unsolvable configuration!!!" << endl;
//    		}
//    		else if (s->getError() & SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE)
//    		{
//    			cout << endl << "Inconsistent internal state!!!" << endl;
//    		}
//    	}
//    }
//
//    cout << endl << "The solution is:" << endl;
//    s->printToConsole();
//    delete s;
//    cout << endl << endl;
//
//
//    cout << "example2:" << endl;
//    p->load("./src/example2.txt");
//    s = new BTSolver(p);
//    if (!s->solve())
//    {
//	  if (s->getError() > 0)
//      {
//		if (s->getError() & SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION)
//		{
//			cout << endl << "Unsolvable configuration!!!" << endl;
//		}
//		else if (s->getError() & SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE)
//		{
//			cout << endl << "Inconsistent internal state!!!" << endl;
//		}
//	  }
//    }
//
//
//    cout << endl << "The solution is:" << endl;
//    s->printToConsole();
//    delete s;
//    cout << endl << endl;
//
//
//    cout << "example3:" << endl;
//    p->load("./src/example3.txt");
//    s = new BTSolver(p);
//    if (!s->solve())
//    {
//    	if (s->getError() > 0)
//    	{
//    		if (s->getError() & SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION)
//    		{
//    			cout << endl << "Unsolvable configuration!!!" << endl;
//    		}
//    		else if (s->getError() & SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE)
//    		{
//    			cout << endl << "Inconsistent internal state!!!" << endl;
//    		}
//    	}
//    }
//
//    cout << endl << "The solution of example3 is:" << endl;
//    s->printToConsole();
//    delete s;
//    cout << endl << endl;



    cout << "example4:" << endl;
    p->load("./src/example4.txt");
    s = new BTSolver(p);
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

    cout << endl << "The solution of example4 is:" << endl;
    s->printToConsole();
    delete s;
    cout << endl << endl;




   delete p;




	return 0;
}
