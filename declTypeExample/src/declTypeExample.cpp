//============================================================================
// Name        : declTypeExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <typeinfo>

using namespace std;

struct A {
	double x;
};

const A* a = new A{0};

decltype( a->x ) x3 = 2.0;
decltype ( ( a->x )) x4 = x3;

template < class T , class U >
auto add(T t, U u) -> decltype(t + u);  // return type depends on the template parameters

int main() {
	cout << "decltype example" << endl; // prints decltype example
	cout << "x3 = " << x3 << ", typeid(x3) = " << typeid(x3).name() << endl;
	cout << "x4 = " << x4 << ", typeid(x4) = " << typeid(x4).name() << endl;
	int i = 33;
	decltype(i) j = i*2;

	cout << "i= " << i << ", "
		 << "j= " << j << endl;

	auto f = [](int a, int b) -> int { return a*b; };
    decltype(f) f2 = f;

    cout << "typeid(f) = " << typeid(f).name() << ", typeid(f2) = " << typeid(f2).name() << endl;

    i = f(2, 2);
    j = f2(3, 3);

    cout << "i= " << i << ", "
    		"j= " << j << endl;




	return 0;
}
