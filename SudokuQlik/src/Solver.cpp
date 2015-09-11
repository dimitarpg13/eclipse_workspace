/*
 * Solver.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: Dimitar Gueorguiev
 */

#include "Solver.h"

namespace sudoku
{
   void BTSolver::print_ranked_candidates(map<unsigned short,rank_list > & c)
   {
	   cout << "Total number of distinct ranks: " << c.size() << endl;
	 	map<unsigned short,rank_list>::iterator itR;
	  	list<pair<Symbol*,list<char> > >::iterator itRL;
	  	list<char>::iterator itCL;
	  	for (itR = c.begin(); itR != c.end(); itR++)
	  	{
	  		rank_list & rl = itR->second;
            cout << itR->first << " => " << endl;
            for (itRL = rl.begin(); itRL != rl.end(); itRL++)
            {
            	std::cout << "\t{";
            	for (itCL = itRL->second.begin(); itCL != itRL->second.end(); itCL++)
            	{
            		std::cout << *itCL << " ";
            	}
            	std::cout << "}" << endl;
            }
	  	}
   }


  bool BTSolver::solve()
  {
	  bool res = true;
      res &= assign_rank_to_candidates(m_mRankedCandidates);

      print_ranked_candidates(m_mRankedCandidates);

	  return res;
  }

  bool BTSolver::process_line_assignments(Line * l, set<char> & assigned)
  {
	  if (l == NULL)
	  {
	     m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
	     return false;
	  }

	  Symbol * cur=NULL;
	  for (int i=0; i < l->getDim(); i++)
	  {
	     cur = l->getSymbols()[i];
	     if (cur != NULL)
	     {
	        if (!cur->isEmpty())
	           assigned.insert(cur->getValue());
	     }
	     else
	     {
	        m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
	        return false;
	     }
	  }

	  return true;
  }

  bool BTSolver::process_region_assignments(Region * r, set<char> & assigned)
  {
	  if (r == NULL)
	  {
	     m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
	     return false;
	  }

	  Symbol * cur=NULL;

	  for (int i=0; i < r->getSymbCount(); i++)
	  {
	     cur = r->getSymbols()[i];
	     if (cur != NULL)
	     {
	        if (!cur->isEmpty())
	           assigned.insert(cur->getValue());
	     }
	     else
	     {
	        m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
	        return false;
	     }
	  }

	  return true;
  }

  bool BTSolver::get_available_assignments(Symbol * s,list<char> & assignments)
  {
	  if (s == NULL)
		  return false;

      set<char> assigned;

      if (!process_line_assignments(s->getRow(),assigned))
    	  return false;

      if (!process_line_assignments(s->getCol(),assigned))
    	  return false;

      if (!process_region_assignments(s->getRegion(),assigned))
    	  return false;


      assignments.assign(assigned.begin(), assigned.end());


      return true;
  }


  bool BTSolver::assign_rank_to_candidates(
		  map<unsigned short,rank_list > & rankedCandidates)
  {
     bool res=true;
     if (m_pSol != NULL && m_lError == 0)
     {
    	HorizLine *  curRow=NULL;
    	Symbol * curSymbol=NULL;
    	list<char> curAssignments;
    	unsigned short curRank=0;
    	map<unsigned short,rank_list>::iterator itR;
    	rank_list curRankList;
        for (int i = 0; i < m_pSol->getDim(); i++)
        {
           curRow = m_pSol->getRows()[i];
           for (int j = 0; j < m_pSol->getDim(); j++)
           {
               curSymbol = curRow->getSymbols()[j];
               if (curSymbol->isEmpty())
               {
                   curAssignments.clear();
                   get_available_assignments(curSymbol,curAssignments);
                   curRank = (unsigned short) curAssignments.size();

                   itR = rankedCandidates.find(curRank);
                   if (itR != rankedCandidates.end())
                   {
                	   itR->second.push_back(pair<Symbol*,list<char> >(curSymbol,curAssignments));
                   }
                   else
                   {
                	   curRankList.clear();
                	   curRankList.push_back(pair<Symbol*,list<char> >(curSymbol,curAssignments));
                       rankedCandidates.insert(pair<unsigned short,rank_list>(curRank,curRankList));
                   }
               }
           }

        }
     }
     else
    	 res=false;

     return res;
  }




}



