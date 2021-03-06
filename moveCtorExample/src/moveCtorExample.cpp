//============================================================================
// Name        : moveCtorExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>
#include <iostream>

using namespace std;

struct A
{
	std::string s;
	A() : s("test") {}
	A(const A& o) : s(o.s) { std::cout << "move failed!\n"; }
	A(A&& o) : s(std::move(o.s)) {}
};

A f(A a)
{
	return a;
}

struct B : A {
	std::string s2;
	int n;
	// implicit move constructor
	// calls A's move constructor
	// calls s2's move constructor
	// and makes a bitwise copy of n
};

struct C : B {
	~C() {}; // destructor prevents implicit move constructor C::C(C&&)
};

struct D : B {
	D() {};
	~D() {};
	D(D&&) = default; // force a move ctor anyway
};



int main() {
	cout << "move constructor - move from temporary rvalue" << endl; // prints move constructor example
	A a1 = f(A()); // move-construct from rvalue temporary

	cout << "before the move : a1 = " << a1.s << endl;

	A a2 =std::move(a1);

    cout << "after the move: a2.s = " << a2.s << ", a1.s = " << a1.s << endl;

    cout << "move constructor - move using implicit move constructor" << endl;
    B b1;
    cout << "before the move: b1.s = " << b1.s << endl;
    B b2 = std::move(b1); // calls implicit move constructor
    cout << "after the move: b2.s = " << b2.s << ", b1.s = " << b1.s <<  endl;

    cout << "move constructor: inheriting class has explicit destructor which prevents the implicit move constructor" << endl;
    C c1;
    cout << "before the move: c1.s = " << c1.s << endl;
    C c2 = std::move(c1);
    cout << "after the move: c2.s = " << c2.s << ", c1.s = " << c1.s <<  endl;

    cout << "move constructor: inheriting class has explicit destructor but move ctor is forced anyway" << endl;
    D d1;
    cout << "before the move: d1.s = " << d1.s << endl;
    D d2 = std::move(d1);
    cout << "after the move: d2.s = " << d2.s << ", d1.s = " << d1.s <<  endl;


	return 0;
}
