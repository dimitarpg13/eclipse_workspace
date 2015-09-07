/*
 * Parser.h
 *
 *  Created on: Sep 4, 2015
 *      Author: Dimitar Gueorguiev
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

#include "Line.h"
#include "Symbol.h"

using namespace std;

namespace sudoku
{

enum Error
{
   SUDOKU_NO_ERROR=0,
   SUDOKU_ERROR_INCORRECT_INPUT_FORMAT=1,
   SUDOKU_ERROR_INCORRECT_INPUT_ROW_COUNT=2,
   SUDOKU_ERROR_INCORRECT_INPUT_COL_COUNT=4
};

class Parser
{
public:
	Parser(unsigned char dim, unsigned char regionDim, char sep = '.', char eol = '\n');

	bool parse(string inputFile);
	~Parser();
    HorizLine ** getRows() { return m_pRows; }
    VertLine **  getCols() { return m_pCols; }
    long long getError() { return m_lError; }

private:
	bool is_symbol(char c);
	bool is_separator(char c);
	bool is_end_of_line(char c);
	void cleanup_rows_and_cols(unsigned char rowCount, unsigned char colCount);

    set<char> * m_pSymbols;
    unsigned char m_iDim, m_iRegionDim;
    char m_cSep;
    char m_cEol;
    HorizLine ** m_pRows;
    VertLine ** m_pCols;
    long long m_lError;
    static char symbolTable[];
};

}

#endif /* PARSER_H_ */
