//============================================================================
// Name        : TestSudoku.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <stack>


using namespace std;

void arraySizeFinder(int ** r)
{
	cout << endl << "Inside arraySizeFinder: The array size is " << sizeof(*r) << " bytes" << endl;
}

void arraySizeFinder2(int (&r) [5])
{
	cout << endl << "Inside arraySizeFinder2: The array size is " << sizeof(r) << " bytes" << endl;
}


int main() {

	cout << "TestSudoku" << endl; // prints TestSudoku

//    std::set<char> s1, s2;
//	s1.insert('1');
//	s1.insert('2');
//	s1.insert('3');
//	s1.insert('4');
//	s1.insert('5');
//	s2.insert('2');
//	s2.insert('3');
//	const set<char> & s11 = s1;
//	const set<char> & s22 = s2;
//
//	// Fill in s1 and s2 with values
//	std::set<char> result;
//	std::set_difference(s11.begin(), s11.end(), s22.begin(), s22.end(),
//	    std::inserter(result, result.end()));
//
//	for (set<char>::iterator it = result.begin(); it != result.end(); it++)
//		cout << *it;

	stack<int*> s;
	if (!s.empty())
	{
    int * p = s.top();
    if (p != NULL)
      cout << "p not null!" << endl;
    else
      cout << "p is null" << endl;
	}
	else
		cout << "the stack is empty!" << endl;

	cout << 2 + 3*2 << endl;

	int r[] = {1,2,5,11,1111};
	int * s1 = r;

	cout << "The array size is : " << sizeof(r) << " bytes" << endl;
	cout << endl << "sizeof(s1) = " << sizeof(s1) << endl;

	arraySizeFinder(&s1);
	arraySizeFinder2(r);
    int value=10;
    int * p = &value;

    cout << endl << "sizeof(p) = " << sizeof(p) << endl;

    char ch[] = "Dimitarius";
    cout << endl << "sizeof(ch)=" << sizeof(ch) << " ";
	return 0;
}
