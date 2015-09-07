/*
 * Line.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Dimitar Gueorguiev
 */

#ifndef LINE_H_
#define LINE_H_

#include <vector>
#include <cmath>

#include "Symbol.h"

using namespace std;

namespace sudoku
{

class Line
{
protected:
	unsigned char m_iDim, m_iRegionDim;
	Symbol **	m_pSymbols;
	Region **   m_pRegions;
	unsigned char m_iLastSymbolIdx;
	unsigned char m_iLastRegionIdx;
public:
	Line(unsigned char dim, unsigned char regDim) :
		m_iDim(dim), m_iRegionDim(regDim), m_iLastSymbolIdx(0), m_iLastRegionIdx(0)
    {
		m_pSymbols = new Symbol* [m_iDim];
	    m_pRegions = new Region* [m_iRegionDim];
    }

	bool addSymbol(Symbol* symb)
	{
		if (m_iLastSymbolIdx < m_iDim)
		{
           m_pSymbols[m_iLastSymbolIdx++] = symb;
           return true;
		}
		else
			return false;
	}

    bool addRegion(Region* region)
    {
        if (m_iLastRegionIdx < m_iRegionDim)
        {
    	   m_pRegions[m_iLastRegionIdx++] = region;
    	   return true;
        }
        else
        	return false;
    }
};

class HorizLine : public Line
{
public:
	HorizLine(unsigned char dim, unsigned char regionDim) : Line(dim, regionDim) {};



};

class VertLine : public Line
{
public:
   VertLine(unsigned char dim, unsigned char regionDim) : Line(dim, regionDim) {};



};

}

#endif /* LINE_H_ */
