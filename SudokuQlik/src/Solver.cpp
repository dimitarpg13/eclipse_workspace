/*
 * Solver.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: Dimitar Gueorguiev
 */

#include "Solver.h"

namespace sudoku
{
   void Solver::copy_input()
   {
      HorizLine ** const rows = m_pPuzzle->getRows();
      VertLine ** const cols = m_pPuzzle->getCols();
      Region ** const regions = m_pPuzzle->getRegions();

      HorizLine * curRow=NULL;
      Symbol * curSymbol=NULL;
      for (int i=0; i < m_iDim; i++) // i - row indx
      {
    	  curRow = rows[i];
          for (int j=0; j < m_iDim; j++) // j - col indx
          {
              curSymbol = curRow->getSymbols()[j];

          }

      }




   }


}



