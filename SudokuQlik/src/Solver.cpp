/*
 * Solver.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: Dimitar Gueorguiev
 */

#include "Solver.h"

namespace sudoku
{
   void BTSolver::print_ranked_candidates(vector<rank_list *> & c)
   {
	   cout << "Total number of distinct ranks: " << m_iRankCount << endl;
	 	vector<rank_list *>::iterator itR;
	  	list<pair<Symbol*,list<char>* > >::iterator itRL;
	  	list<char>::iterator itCL;
	  	int indx = 1;
	  	for (itR = c.begin(); itR != c.end(); itR++)
	  	{
	  		if (*itR == NULL)
	  			continue;

            cout << indx++ << " => " << endl;
            for (itRL = (*itR)->begin(); itRL != (*itR)->end(); itRL++)
            {
            	std::cout << "\t{";
            	for (itCL = itRL->second->begin(); itCL != itRL->second->end(); itCL++)
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
      res &= assign_rank_to_candidates(m_vRankedCandidates);
      if (!res)
    	  return res;

#ifdef _DEBUG
      print_ranked_candidates(m_vRankedCandidates);
#endif


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


  bool BTSolver::get_available_assignments(Symbol * s,list<char>&  assignments)
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

      const set<char>& symbTable = *m_pSrc->getSymbolTable();

#ifdef _DEBUG
      cout << endl;
      print_collection(symbTable.begin(),symbTable.end());
      cout << endl;
      print_collection(assigned.begin(),assigned.end());
      cout << endl;
#endif

      set<char> diff;
      set_symmetric_difference(assigned.begin(),assigned.end(),symbTable.begin(),symbTable.end(),inserter(diff,diff.end()));

#ifdef _DEBUG
      print_collection(diff.begin(),diff.end());
      cout << endl;
#endif

      assignments.assign(diff.begin(), diff.end());


      return true;
  }


  bool BTSolver::assign_rank_to_candidates(
		  vector<rank_list *> & rankedCandidates)
  {
     bool res=true;
     if (m_pSol != NULL && m_lError == 0)
     {
    	HorizLine *  curRow=NULL;
    	Symbol * curSymbol=NULL;
    	list<char> * curAssignments = NULL;
    	unsigned short curRank=0;
    	rank_list * curRankList = NULL;

        for (int i = 0; i < m_pSol->getDim(); i++)
        {
           curRow = m_pSol->getRows()[i];
           for (int j = 0; j < m_pSol->getDim(); j++)
           {
        	   if (curRow == NULL)
        	   {
        	       m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
        	      return false;
        	   }

               curSymbol = curRow->getSymbols()[j];
               if (curSymbol == NULL)
               {
                  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
                  return false;
               }

               if (curSymbol->isEmpty())
               {
            	   if (curSymbol->getAssignments() == NULL)
                       curAssignments = new list<char>();
            	   else
            	   {
            		   curAssignments = curSymbol->getAssignments();
            		   curAssignments->clear();
            	   }

                   get_available_assignments(curSymbol,*curAssignments);
                   curSymbol->setAssignments(curAssignments);

                   if (curAssignments->size() > 0)
                      curRank = (unsigned short) curAssignments->size() - 1;
                   else
                   {
                	   m_lError |= SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION;
                	   return false;
                   }



                   curRankList = rankedCandidates[curRank];
                   if (curRankList != NULL)
                   {
                	   curRankList->push_back(rank_pair(curSymbol,curAssignments));
                   }
                   else
                   {
                	   curRankList = new list<rank_pair>();
                	   curRankList->push_back(rank_pair(curSymbol,curAssignments));
                       rankedCandidates[curRank] = curRankList;
                       m_iRankCount++;
                   }
               }
           }

        }
     }
     else
    	 res=false;

     return res;
  }

  bool BTSolver::update_ranked_list(vector<rank_list *> & c)
  {
 	  bool res = true;

 	  return res;
  }


  // called in case the current symbol was empty but now it has been assigned a value.
  // this means that the other symbols in the containing row, column and region need
  // have update in their candidate lists. The update in the candidate lists will
  // trigger an update in the map with the list of ranked pairs since the rank of all
  // empty symbols in the containing row, column and region will be decremented.
  //

  bool BTSolver::update_assignments(Symbol * s)
  {
	  bool res = true;

	  Symbol * curSymbol = NULL;
	  HorizLine * curRow = s->getRow();
	  list<char> * curAssignments = NULL;
	  list<char>::iterator itA;
	  if (curRow != NULL)
	  {
          for (int i = 0; i < curRow->getDim(); i++)
          {
        	  if (curRow->getSymbols() != NULL)
                 curSymbol = curRow->getSymbols()[i];
        	  else
        	  {
        	      m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
        	      return false;
        	  }
        	  if (curSymbol->isEmpty())
        	  {
        		  curAssignments = curSymbol->getAssignments();
        		  if (curAssignments != NULL)
        		  {
                     itA = find(curAssignments->begin(),curAssignments->end(),s->getValue());
                     if (itA != curAssignments->end())
                     {
#ifdef _DEBUG
                        cout << endl << "Found redundant assignment for element with value " << s->getValue() << endl;
#endif
                     }
        		  }
        		  else
        		  {
              	      m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
                	  return false;
        		  }
        	  }

          }
	  }
	  else
	  {
	       m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
	       return false;
	  }


	  return res;
  }

  bool BTSolver::solve_internal(vector<rank_list *> & c, stack<Symbol *> & s)
  {
      bool res = true;
	  vector<rank_list *>::iterator itC;
	  list<rank_pair>::iterator itRL;
	  list<char>::iterator itCL;
	  Symbol * curSymbol=NULL;
	  list<char> * curAssignments=NULL;
	  char curChar= 0;
	  for (itC = c.begin(); itC != c.end(); itC++)
	  {
          for (itRL = (*itC)->begin(); itRL != (*itC)->end(); itRL++)
          {
              curSymbol = itRL->first;
              if (curSymbol == NULL)
              {
            	  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
            	  return false;
              }
              if (curSymbol->isEmpty())
              {
            	  curAssignments = curSymbol->getAssignments();
            	  if (curAssignments != NULL)
            	  {
					  curChar = curAssignments->front();
					  if (curChar != 0)
					  {
						 curAssignments->remove(curAssignments->front());
						 curSymbol->setValue(curChar);
						 s.push(curSymbol);
						 res &= update_assignments(curSymbol);
						 if (!res)
							 return false;
					  }
					  else
					  {
						 m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
						 return false;
					  }
            	  }
            	  else
            	  {
            		  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
                      return false;
            	  }
              }

          }

	  }

	  return res;
  }




}



