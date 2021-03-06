//============================================================================
// Name        : polymorphicDowncastExcercise.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
//#include <boost/polymorphic_cast.hpp>

using namespace std;

struct A { virtual ~A() {}; virtual string name() { return string("A"); }; };
struct B : A { string name() { return string("B"); }; };


template <class Target, class Source>
inline Target polymorphic_downcast_simple(Source* x)
{
   BOOST_ASSERT( dynamic_cast<Target>(x) == x );  // detect logic error
   return static_cast<Target>(x);
}

template <class Target, class Source>
inline Target polymorphic_downcast_simple(Source& x)
{
   //BOOST_ASSERT( dynamic_cast<Target>(x) == x );  // detect logic error
   return static_cast<Target>(x);
}



/*template <class Target, class Source>
inline Target polymorphic_downcast(Source& x)
{
   //BOOST_ASSERT( dynamic_cast<Target>(x) == x );  // detect logic error
   //return static_cast<Target>(x);
  // return std::conditional<std::is_same<C, X>::value, Y,
	//		typename type_replace_helper::type_replace_base<C, X, Y>::type
	//		>
	//BOOST_ASSERT( dynamic_cast<Target>(x) == x );  // detect logic error

	return static_cast<Target>(x);
}*/

//template<typename Target>
//struct polymorphic_downcast
//{
//	Target * value ;
//
//
//
//	template<typename Source>
//	polymorphic_downcast(Source & x)
//	{
//		value = & ( static_cast<Target &>(x) );
//	}
//
//};

//template<typename Target, typename Source>
//struct polymorphic_downcast
//{
//	typedef typename std::conditional<std::is_same<C, X>::value, Y,
//			typename type_replace_helper::type_replace_base<C, X, Y>::type
//			>::type type;
//};

template<typename Target, typename Source>
struct polymorphic_downcast
{

};


int main() {
	cout << "polymorphic downcast example" << endl; // prints polymorphic downcast example

//	A * inst = new B();
//
//
//	B * b = boost::polymorphic_downcast<B*>(inst);
//	A * a = new A();
//    cout << b->name() << endl;
//    cout << a->name() << endl;

    B x;
    B & y = x;
    A & z = x;

   // B & t = static_cast<B&> (z);
   // B & t = polymorphic_downcast_simple<B&> (z);
   //B & t = polymorphic_downcast<B&> (z);
   // B * t  = polymorphic_downcast<B> (z).value;

   // cout << t.name() << endl;

	return 0;
}
