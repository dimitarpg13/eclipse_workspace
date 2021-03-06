//============================================================================
// Name        : enableIfExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <type_traits>

using namespace std;

template< bool B, class T = void >
using enable_if_t = typename enable_if<B,T>::type;

// fool overloads are enabled via the return type
template<class T>
typename enable_if<is_floating_point<T>::value, T>::type
	   foo1(T t)
{
    cout << "foo1: float" << endl;
	return t;
}

template<class T>
   enable_if_t<is_integral<T>::value, T>
       foo1(T t)
{
	cout << "foo1: int" << endl;
	return t;
}

//foo2 overload is enabled via a parameter
template<class T>
T foo2(T t, typename enable_if<is_integral<T>::value>::type* = 0 )
{
	return t;
}

//foo3 overload is enabled via a template parameter
template<class T,
		 typename enable_if<is_integral<T>::value>::type* = nullptr>
T foo3(T t)
{
	return t;
}

//A is enabled via a template parameter
template<class T, class Enable=void>
class A; //undefined

template<class T>
class A<T, typename enable_if<is_floating_point<T>::value >::type > {

};



int main() {
	cout << "enable_if usage example" << endl; // prints enable_if usage example
    foo1(1.2f);
    foo1(2);

	return 0;
}
