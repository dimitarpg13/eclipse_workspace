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

typedef list<pair<Symbol*,list<char>* > > rank_list;

struct printer {
    std::ostream& os;
    printer(std::ostream& os) : os(os) {}
    template<typename T>
    void operator()(const T& obj) { os << obj << ' '; }
};
//
//
//
class BTSolver : public Solver
{
public:
	BTSolver(Puzzle * puzzle) : Solver(puzzle) {};
	bool solve();
    ~BTSolver()
    {
    	// TO DO: do implementation cleanup
    };
private:

	// the map entry key is the number of possible assignments available for the current candidate
	// the map entry value is a list of pairs where the pair key is the current empty symbol which
	// needs to be assigned a value and the pair vaue is a list of possible assignments available.
	//
	map<unsigned short,rank_list> m_mRankedCandidates;

	bool assign_rank_to_candidates(map<unsigned short,rank_list > &);
	bool get_available_assignments(Symbol *,list<char> &);
	bool process_line_assignments(Line *, set<char> &);
	bool process_region_assignments(Region *, set<char>&);

	bool update_ranked_list(map<unsigned short,rank_list > &);

	bool solve_internal(map<unsigned short,rank_list > &);


	// helper methods for debugging
	void print_ranked_candidates(map<unsigned short,rank_list > &);
	template<typename Iterator>
	void print_collection(Iterator begin, Iterator end)
	{
		for_each(begin,end,printer(cout));
	}

};



}


#endif /* SOLVER_H_ */
