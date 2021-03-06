//============================================================================
// Name        : varTemplExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class NoneT {};



template<class... Ts> struct mytuple{};

template <class T, class... Ts>
struct mytuple<T, Ts...> : mytuple<Ts...> {
	mytuple(T t, Ts... ts) : mytuple<Ts...>(ts...), tail(t) {}
	T tail;
};

int main() {
	cout << "variadic templates example" << endl; // prints variadic templates example
	mytuple<double,int,const char*> t1(10.2,100,"big");
	cout << "t1.tail = " << t1.tail << endl;


	return 0;
}
