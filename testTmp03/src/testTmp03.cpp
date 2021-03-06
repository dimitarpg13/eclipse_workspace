//============================================================================
// Name        : testTmp03.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

template<class T,class U>
struct X
{
	int f(T* x) // declaration
	{
		U y[10]; // definition
		return 0;
	}
};

int main() {
	cout << "template instantiation example" << endl; // prints template instantiation example
	typedef X<int&, char> t1; // OK, no instantiation yet
	// t1 x1;  // error - pointer to int& illegal
	typedef X<int, char&> t2;
	t2 x2; // OK, declarations check out
	// int a = x2.f(nullptr); // error - array of char& illegal


	return 0;
}
