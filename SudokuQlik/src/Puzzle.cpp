/*
 * Puzzle.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: Dimitar Gueorguiev
 */

#include "Puzzle.h"

namespace sudoku
{

bool Puzzle::process_parsed_config()
{
   bool res = true;
   vector<HorizLine*> & rows = m_pParser->getRows();
   vector<VertLine*> & cols = m_pParser->getCols();

   return res;
}

}
