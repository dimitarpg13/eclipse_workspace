//============================================================================
// Name        : addPointerExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

typedef int t1;
typedef add_pointer<t1>::type A; 	//int*


int main() {
	cout << "add_pointer example" << endl; // prints add_pointer example
	A var1 = new t1[2];
    var1[0] = 101;
    var1[1] = 1113;

    cout << "var1[0] = " << var1[0] << ", var1[1] = " << var1[1] << endl;
     vector<int> vect1;

    typedef iterator_traits<vector<int>::iterator>::value_type t1;
    typedef iterator_traits<vector<int>::iterator>::difference_type t2;
    typedef iterator_traits<vector<int>::iterator>::reference t3;
    typedef iterator_traits<vector<int>::iterator>::pointer t4;

    t1 v1 = 101;
    t2 v2;
    t3 v3 = v1;
    t4 v4 = &v1;



	return 0;
}
