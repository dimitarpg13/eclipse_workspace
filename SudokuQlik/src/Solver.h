/*
 * Solver.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Dimitar Gueorguiev
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include <vector>
#include <map>
#include <list>

#include "Sudoku.h"

using namespace std;

namespace sudoku
{

class Solver
{
protected:
	Puzzle * m_pPuzzle;

	unsigned char m_iDim;
	unsigned char m_iRegionDim;

	HorizLine ** m_pRows;
	VertLine ** m_pCols;
	Region ** m_pRegions;

	void copy_input();


public:
    HorizLine ** const getRows() { return m_pRows; }
    VertLine ** const getCols() { return m_pCols; }
    Region ** const getRegions() { return m_pRegions; }


    Solver(Puzzle * puzzle) : m_pPuzzle(puzzle)
    {
    	if (m_pPuzzle != NULL)
    	{
           m_iDim = m_pPuzzle->getDim();
           m_iRegionDim = m_pPuzzle->getRegionDim();
           copy_input();
    	}
    }

    bool solve()
    {
    	return false;
    }


};


//
//
//
class BTSolver : public Solver
{
public:

private:

	// the key is the number of choices for value available for the current candidate
	//
	map<unsigned short,list<pair<Symbol*,list<char> > > > m_mRankedCandidates;
};

}


#endif /* SOLVER_H_ */
