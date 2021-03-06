//============================================================================
// Name        : Test4.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;


void print_vector(vector<int>& vec)
{
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
	  cout << *it << endl;
	}
}

//
//  Split a set of integers into two sets with the same sums (if exists)
//
int main() {

    vector<int> vec;

    vec.push_back(10);
    vec.push_back(11);
    vec.push_back(7);
    vec.push_back(1);
    vec.push_back(11);

    sort(vec.begin(), vec.end());

    print_vector(vec);

    // a[k[0]] + a[k[1]] + ... + a[k[j]] where 0 <= j < n-1



	return 0;
}
