//============================================================================
// Name        : cormen.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdexcept>
#include "RBT.h"

using namespace std;
using namespace Algorithms;



int integer_comp(const void * l, const void * r)
{
	if (l != nullptr && r != nullptr)
	{
		const int* lv = static_cast<const int*>(l);
		const int* rv = static_cast<const int*>(r);
		if (static_cast<const void*>(lv) != l || static_cast<const void*>(rv) != r)
			throw runtime_error("incompatible argument type in comparer!");

		if (*lv > *rv)
			return 1;
		else if (*lv < *rv)
			return -1;
		else
			return 0;
	}
	else
		return 0;
}

int main() {


    RBT rbt(&integer_comp);

	return 0;
}
