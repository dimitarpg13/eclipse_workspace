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
#include <algorithm>
#include <iterator>
#include <stack>

#include "Sudoku.h"

using namespace std;

namespace sudoku
{

class Solver
{
protected:
	Puzzle * m_pSrc;
	Puzzle * m_pSol;
	long long m_lError;

public:
    HorizLine ** const getRows()
    {
    	if (m_pSol != NULL)
    	   return m_pSol->getRows();
    	else
    	   return NULL;
    }

    VertLine ** const getCols()
    {
       if (m_pSol != NULL)
    	  return m_pSol->getCols();
       else
    	  return NULL;
    }

    Region ** const getRegions()
    {
    	if (m_pSol != NULL)
    	   return m_pSol->getRegions();
    	else
    	   return NULL;
    }


    Solver(Puzzle * puzzle) : m_pSrc(puzzle), m_lError(0)
    {
    	if (m_pSrc != NULL)
    	{
          m_pSol = m_pSrc->getCopy();
          m_lError |= m_pSrc->getError();
    	}
    	else
    	  m_pSol = NULL;
    }

    long long getError() { return m_lError; };

    virtual bool solve() = 0;


    virtual ~Solver()
    {
	   // TO DO: do base class clean-up
    };

};

typedef pair<Symbol*,list<char>*> rank_pair;
typedef list<rank_pair>  rank_list;

struct printer {
    std::ostream& os;
    printer(std::ostream& os) : os(os) {}
    template<typename T>
    void operator()(const T& obj) { os << obj << ' '; }
};

// solver using backtracking i.e. depth first search
//
//
class BTSolver : public Solver
{
public:
	BTSolver(Puzzle * puzzle) : Solver(puzzle), m_iRankCount(0)
    {
	    if (puzzle != NULL)
	    {
	    	m_vRankedCandidates.resize(puzzle->getDim(),NULL);
	    }
    };

	bool solve();
    ~BTSolver()
    {
    	for (vector<rank_list *>::iterator it = m_vRankedCandidates.begin(); it != m_vRankedCandidates.end(); it++)
    		delete *it;
    };
private:

	// the map entry key is the number of possible assignments available for the current candidate
	// the map entry value is a list of pairs where the pair key is the current empty symbol which
	// needs to be assigned a value and the pair vaue is a list of possible assignments available.
	//
	vector<rank_list *> m_vRankedCandidates;
	unsigned short m_iRankCount;

	bool assign_rank_to_candidates(vector<rank_list *> &);
	bool get_available_assignments(Symbol *,list<char> &);
	bool process_line_assignments(Line *, set<char> &);
	bool process_region_assignments(Region *, set<char>&);

	bool solve_internal(vector<rank_list *> &, stack<Symbol *> &);

	bool update_ranked_list(vector<rank_list *> &);

	bool update_assignments(Symbol * s);

	// helper methods for debugging
	void print_ranked_candidates(vector<rank_list *> &);
	template<typename Iterator>
	void print_collection(Iterator begin, Iterator end)
	{
		for_each(begin,end,printer(cout));
	}

};



}


#endif /* SOLVER_H_ */
