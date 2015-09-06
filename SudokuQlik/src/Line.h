/*
 * Line.h
 *
 *  Created on: Sep 5, 2015
 *      Author: root
 */

#ifndef LINE_H_
#define LINE_H_

#include <vector>

#include "Symbol.h"

using namespace std;

namespace sudoku
{

class Line
{
protected:
	vector<Symbol*>	m_vSymbols;
	vector<Region*> m_vRegions;
public:
	void addSymbol(Symbol* symb)
	{
       m_vSymbols.push_back(symb);
	}

    void addRegion(Region* region)
    {
    	m_vRegions.push_back(region);
    }
};

class HorizLine : public Line
{
public:
	HorizLine()
    {

    };


};

class VertLine : public Line
{

};

}

#endif /* LINE_H_ */