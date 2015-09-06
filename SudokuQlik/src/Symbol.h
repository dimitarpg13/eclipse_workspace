/*
 * Symbol.h
 *
 *  Created on: Sep 5, 2015
 *      Author: root
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "Region.h"
#include "Line.h"

namespace sudoku
{
class HorizLine;
class VertLine;

class Symbol
{
private:
	char m_cVal;

	Region * m_pRegion;
	HorizLine * m_pHorizLine;
	VertLine * m_pVertLine;

public:
	Symbol(char val)  { m_cVal = val; }
	Symbol() { m_cVal = 0; }

	bool isEmpty() {  return m_cVal == 0; }

	char getValue() { return m_cVal; }
    void setValue(char val) { m_cVal = val; }

	Region * getRegion() { return m_pRegion; };
	HorizLine * getHorizLine() { return m_pHorizLine; }
	VertLine * getVertLine() { return m_pVertLine; }

    void setRegion(Region * region) { m_pRegion = region; }
    void setHorizLine(HorizLine * hline) { m_pHorizLine = hline; }
    void setVertLine(VertLine * vline) { m_pVertLine = vline; }

};

}

#endif /* SYMBOL_H_ */
