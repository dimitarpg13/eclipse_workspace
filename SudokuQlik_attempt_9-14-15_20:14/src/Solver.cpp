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
            	std::cout << "[" << (int) itRL->first->getRow()->getIdx()
            			  << "," << (int) itRL->first->getCol()->getIdx()
            			  << "]\t{";
            	for (itCL = itRL->second->begin(); itCL != itRL->second->end(); itCL++)
            	{
            		std::cout << *itCL << " ";
            	}
            	std::cout << "}" << endl;
            }
	  	}
   }

  RankNode * BTSolver::init_rank_node_list(vector<rank_list *> & c)
  {
	  RankNode * head = NULL, * cur = NULL, * prev = NULL;

	  vector<rank_list *>::iterator itC;
	  list<rank_pair>::iterator itRL;

	  for (itC = c.begin(); itC != c.end(); itC++)
	  {
		  if (*itC == NULL)
		     continue;

	      for (itRL = (*itC)->begin(); itRL != (*itC)->end(); itRL++)
	      {
              cur = new RankNode(&(*itRL));
              if (prev == NULL)
                head = cur;
              else
            	prev->Next = cur;

              cur->Prev = prev;
              prev = cur;
	      }
	  }

	  return head;
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

      m_lstRankedCandidates = init_rank_node_list(m_vRankedCandidates);


      RankNode * head = m_lstRankedCandidates, * end = NULL, * cur = m_lstRankedCandidates;
      while (cur != NULL)
      {
    	  end = cur;
    	  cur = cur->Next;
      }

      int count = 0;
      while (!solve_internal(head))
      {
    	  cur = end;
    	  end = head;
    	  cur->Next= end;
    	  head = head->Next;
    	  end->Next=NULL;
    	  m_pSol = m_pSrc->getCopy();
//    	  m_vRankedCandidates.resize(m_pSrc->getDim(),NULL);
//    	  assign_rank_to_candidates(m_vRankedCandidates);
//    	  m_lstRankedCandidates = init_rank_node_list(m_vRankedCandidates);
    	  count++;
    	  if (count == 46)
    	  {
    		  int iii=0;

    	  }
      }
      //res &= solve_internal(m_lstRankedCandidates);

      int len=0;
      while (head != NULL)
      {
    	  head = head->Next;
    	  len++;
      }

      cout << endl << "-------------Solution!------------" << endl;
      m_pSol->printToConsole();
      cout << endl << "-------------Solution!------------" << endl;
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



  bool BTSolver::update_symbols(Symbol* s, Symbol ** arr, unsigned char dim)
  {
	  bool res = true;

	  Symbol * curSymbol = NULL;
	  list<char> * curAssignments = NULL;
	  list<char>::iterator itA;

      for (int i = 0; i < dim; i++)
      {
          curSymbol = arr[i];
          if (curSymbol->isEmpty())
          {
       		  curAssignments = curSymbol->getAssignments();

       		  if (curAssignments != NULL)
       		  {
       			  unsigned short sz = curAssignments->size();
       			  if (sz > 1)
       			  {
                     curAssignments->remove_if(Remover(s->getValue()));
                     if (curAssignments->size() < sz)
                     {
                    	 // there was a removal so we need to update the corresponding rank list
                         rank_list * curRankList = m_vRankedCandidates[sz-1];
                         if (curRankList != NULL)
                         {
                             curRankList->remove_if(SymbolFinder(curSymbol));
                             if (sz - 2 >= 0)
                             {
                                 m_vRankedCandidates[sz-2]->push_back(rank_pair(curSymbol,curAssignments));
                             }
                             else
                             {
                            	 m_lError |= SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION;
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
       			  else
       			  {
       				  if (sz == 1)
       				  {
                         if (curAssignments->front() == s->getValue())
                         {
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
       		  else
       		  {
             	  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
               	  return false;
       		  }


          }

      }

	  return res;

  }


  bool BTSolver::update_line(Symbol * s, Line * l)
  {
	  bool res = true;
	  if (l != NULL && l->getSymbols() != NULL)
	  {
          res &= update_symbols(s,l->getSymbols(),l->getDim());
          if (!res)
        	  return false;
	  }
	  else
	  {
		  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
		     return false;
	  }

	  return res;
  }

  bool BTSolver::update_region(Symbol * s, Region * r)
  {
	  bool res = true;
	  if (r != NULL && r->getSymbols() != NULL)
	  {
          res &= update_symbols(s,r->getSymbols(),r->getDim());
          if (!res)
        	  return false;
	  }
	  else
	  {
		  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
		     return false;
	  }

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

	  res &= update_line(s,s->getRow());
      if (!res)
    	  return false;

      res &= update_line(s,s->getCol());
      if (!res)
          return false;


      res &= update_region(s,s->getRegion());
      if (!res)
    	  return false;

	  return res;
  }


  bool BTSolver::restore_symbol(Symbol* s, Symbol ** arr, unsigned char dim)
  {
  	  bool res = true;

  	  if (s == NULL)
  	  {
  		  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
  		  return false;
  	  }

  	  Symbol * curSymbol = NULL;
  	  list<char> * curAssignments = NULL;
  	  list<char>::iterator itA;

        for (int i = 0; i < dim; i++)
        {
            curSymbol = arr[i];
            if (curSymbol->isEmpty())
            {
         		  curAssignments = curSymbol->getAssignments();
         		  if (curAssignments != NULL)
         		  {
         			  if (curSymbol->getLastRemoved() == s->getValue())
         			  {
         				 unsigned short sz = curAssignments->size();
         				 curAssignments->push_back(s->getValue());
         				 curSymbol->setLastRemoved(0);

                         if (sz > 0)
                         {
                             rank_list * curRankList = m_vRankedCandidates[sz-1];
                             if (curRankList != NULL)
                             {
                                  //remove the rank_pair with curSymbol from the current rank list
                            	  // and move it to the rank list with rank one higher than the current
                            	  curRankList->remove_if(SymbolFinder(curSymbol));
                            	  m_vRankedCandidates[sz]->push_back(rank_pair(curSymbol,curAssignments));

                             }
                             else
                             {
                            	 m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
                            	 return false;
                             }
                         }
                         else
                         {
                        	 // this is a situation which should not happen
                        	 // the current Symbol has the last value removed but it appears
                        	 // to have had empty candidate list before the removal
                        	 m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
                        	 return false;
                         }

         			  }
         		  }
         		  else
         		  {
               	     m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
                 	  return false;
         		  }
            }

        }

  	  return res;

  }


  bool BTSolver::restore_line(Symbol * s, Line * l)
  {
  	  bool res = true;
  	  if (l != NULL && l->getSymbols() != NULL)
  	  {
            res &= restore_symbol(s,l->getSymbols(),l->getDim());
            if (!res)
          	  return false;
  	  }
  	  else
  	  {
  		  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
  		     return false;
  	  }

  	  return res;
   }

   bool BTSolver::restore_region(Symbol * s, Region * r)
   {
  	  bool res = true;
  	  if (r != NULL && r->getSymbols() != NULL)
  	  {
            res &= restore_symbol(s,r->getSymbols(),r->getDim());
            if (!res)
          	  return false;
  	  }
  	  else
  	  {
  		  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
  		     return false;
  	  }

  	  return res;
   }



  bool BTSolver::restore_assignment(Symbol * s)
  {
	  bool res = true;

	 	  res &= restore_line(s,s->getRow());
	       if (!res)
	     	  return false;

	       res &= restore_line(s,s->getCol());
	       if (!res)
	           return false;


	       res &= restore_region(s,s->getRegion());
	       if (!res)
	     	  return false;

	 	  return res;
  }


  bool BTSolver::solve_internal(RankNode * head)
  {
	  bool res = true;

	  RankNode * curNode = head;

	  Symbol * curSymbol=NULL;
	  list<char> * curAssignments=NULL;
	  char curChar= 0;
	  bool processed = false;
	  while (curNode != NULL)
	  {
	        curSymbol = curNode->Val->first;

	        if (curSymbol == NULL)
	        {
	           m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
	           return false;
	        }

	        curAssignments = curSymbol->getAssignments();
	        if (!curSymbol->isEmpty())
	        {
               // this symbol is not empty because the algorithm has returned to it due to backtracking
	           // so we need to make it empty and restore the state of the enclosing containers
		       //
	           // updating the assignments with the new change
			   // failed which indicates infeasible configuration
			   // was reached so restore the assignments before the
			   // last attempt and check for a different value to be
			   // assigned to curSymbol
			   restore_assignment(curSymbol);

			   curAssignments->push_back(curSymbol->getValue());
			   curSymbol->setValue(0);

	        }



			if (curAssignments != NULL)
			{
				if (!curAssignments->empty())
				{
				   processed = false;
				   int idx = 0, sz = (int) curAssignments->size();//, prevFailures = curSymbol->getFailedCount();
				   //int effectiveSize = sz - prevFailures;
				   while (idx++ < sz)
				   { // while loop start
					  curChar = curAssignments->front();
					  if (curChar != 0)
					  {
						curAssignments->pop_front();
						curSymbol->setValue(curChar);
						curSymbol->setLastRemoved(curChar);
						res = update_assignments(curSymbol);

#ifdef _DEBUG
						cout << endl << "[" << (int) curSymbol->getRow()->getIdx() << "," << (int) curSymbol->getCol()->getIdx() << "] with " << sz << " candidates. trying " << curChar << ".. "  << endl;
#endif


						if (!res)
						{
							if (m_lError == SUDOKU_NO_ERROR)
							{
							   // updating the assignments with the new change
							   // failed which indicates infeasible configuration
							   // was reached so restore the assignments before the
							   // last attempt and check for a different value to be
							   // assigned to curSymbol
							   restore_assignment(curSymbol);

							   curAssignments->push_back(curSymbol->getValue());
							   curSymbol->setValue(0);
#ifdef _DEBUG
						       cout << "[" << (int) curSymbol->getRow()->getIdx() << "," << (int) curSymbol->getCol()->getIdx() << "] failed to assign " << curChar << ".. "  << endl;
#endif
						       curSymbol->incrementFailedCount();

							 }
							 else
							   return false;
						 }
						 else
						 {
							// done with the current symbol. proceed one level further
							// down onto the solution tree

#ifdef _DEBUG
						    cout << "[" << (int) curSymbol->getRow()->getIdx() << "," << (int) curSymbol->getCol()->getIdx() << "] Assigned " << curChar << endl;
#endif

							processed = true;
							break;
						 }
					   }
					   else
					   {
						  m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
						  return false;
					   }

					 } // while loop end


					 if (!processed)
					 {
						 // No feasible assignment was found for the current symbol where
						 // all attempts lead to an infeasible configuration. So take a step
						 // back (backtracking) one level up the solution tree if the stack
						 // is not empty

						 curNode = curNode->Prev;

						 while ( curNode != NULL && curNode->Val->second->size() <= 1 )
								 //( curNode->Val->second->size() < 1 ||
								 //  curNode->Val->first->getFailedCount() >= curNode->Val->second->size()))
							 curNode = curNode->Prev;

						 if (curNode == NULL)
						 {
							 // we cannot backtrack from the head of the list with the rank_pairs so it has to be
							 // infeasible configuration
							 m_lError |= SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION;
							 return false;
						 }

						 continue;

					 }
				}
				else
				{
				   m_lError |= SUDOKU_ERROR_UNSOLVABLE_CONFIGURATION;
				   return false;
				}
			}
			else
			{
			   m_lError |= SUDOKU_ERROR_INCONSISTENT_INTERNAL_STATE;
			   return false;
			}


	        curNode = curNode->Next;
	  }

	  return res;

  }


  void Solver::printToConsole()
  {
	  if (m_pSol != NULL)
		  m_pSol->printToConsole();
  }


}



