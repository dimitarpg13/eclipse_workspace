//============================================================================
// Name        : replaceTypeExcercise.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

//template <typename C, typename X, typename Y>
//struct replace_type
//{
//   typedef C type;
//};
//
//template <typename C, typename X, typename Y>
//struct replace_type<C &, X, Y>
//{
//   typedef Y & type;
//};
//
//template <bool _isFunc, typename C, typename X, typename Y>
//struct __replace_type_impl
//{
//   typedef C type;
//};
//
//template <typename C, typename X, typename Y>
//struct __replace_type_impl<true, C, X, Y>
//{
//   typedef C type;
//};
//
//template <typename F, typename Arg>
//struct make_func
//{
// //  typedef F type;
//};
//
//template <typename F, typename X, typename Y>
//struct __replace_type_func
//{
//  typedef F type;
//};
//
//template <typename F, typename X, typename Y>
//struct __replace_type_func<F(X),X,Y>
//{
//  //typedef typename (make_func<X,F>::type) type;
//  typedef Y type;
//};
//

namespace type_replace_helper
{
  template <typename, typename, typename>
  struct type_replace_base;
}

template<typename C, typename X, typename Y>
struct type_replace
{
	typedef typename std::conditional<std::is_same<C, X>::value, Y,
			typename type_replace_helper::type_replace_base<C, X, Y>::type
			>::type type;
};

namespace type_replace_helper
{
    template<typename C, typename X, typename Y>
    struct type_replace_base
    {
    	typedef C type;
    };

    template<typename C, typename X, typename Y>
    struct type_replace_base<C(), X, Y>
    {
    	typedef typename type_replace<C, X, Y>::type type();
    };

    template<typename C, typename X, typename Y, typename First>
    struct type_replace_base<C(First), X, Y>
    {
    	typedef typename type_replace<C,X,Y>::type
    			type(
    					typename type_replace<First,X,Y>::type
    				);
    };

    template<typename C, typename X, typename Y, typename First, typename Second>
    struct type_replace_base<C(First, Second), X, Y>
    {
    	typedef typename type_replace<C, X, Y>::type
    			type(
    					typename type_replace<First, X, Y>::type,
    					typename type_replace<Second, X, Y>::type
    				);
    };

}

class X {};
enum Y {};
struct Z {};
typedef int A;
int myfunc(int x)
{
	return 41;
};

typedef int (*fptr) (int);

fptr myfunc2()
{
     int (*mfunc) (int) = &myfunc;

     return mfunc;
};

template <typename, typename, typename>
 struct type_replace_exper;

template<typename C, typename X, typename Y>
struct type_replace_new
{
	typedef typename std::conditional<std::is_same<C, X>::value, Y,
			typename type_replace_exper<C, X, Y>::type
			>::type type;
};

template <typename C, typename X, typename Y>
struct type_replace_exper
{
   typedef C type;
};


template<typename C, typename X, typename Y>
struct type_replace_exper<C(), X, Y>
{
   typedef typename type_replace_new<
            C, X, Y
        >::type type();
};

//template<typename C, typename X, typename Y, typename First>
//    struct type_replace_exper<C(First), X, Y>
//    {
//    	typedef typename type_replace_new<C,X,Y>::type
//    			type(
//    					typename type_replace_new<First,X,Y>::type
//    				);
//    };


int main() {
	cout << "Template Metaprogramming Exercise 2.1 : replace_type" << endl; // prints Template Metaprogramming Exercise 2.0 : add_const_reference

	int (*mf1) (int) = &myfunc;

	cout << "mf1(10) = " << mf1(10) << endl;

	typedef int (mt2) (int)  ;

	mt2& mf2 = myfunc;

	cout << "mf2(100) = " << mf2(100) << endl;

     typedef int mytype ();



//remove_reference<int&>::
	cout << boolalpha << endl;


	static_assert(std::is_same<
	        type_replace<int(int, int), int, const long>::type,
	        const long(const long, const long)
	    >::value, "int should be replaced by const long");

	static_assert(std::is_same<
		        type_replace<int(), int, const long>::type,
		        const long()
		    >::value, "int should be replaced by const long");


	static_assert(std::is_same<
	        type_replace_new<int(), int, long>::type,
	        long()
	    >::value, "int should be replaced by long");


	static_assert(std::is_same<long(),long()>::value,"long() is not equal to long");

//	cout << "typedef int A is compount type: " << is_compound<A>::value << endl;
//	cout << "myfunc is a function: " << is_function<decltype(myfunc)>::value << endl;
//	typedef __replace_type_func<decltype(myfunc),float, int>::type mt1;
//	cout << "replace_type_func: " << typeid(mt1).name() << endl;
//    mt1& mtval1 = myfunc; //= -1.1f;
//    //cout << "mtval1 = " << mtval1 << endl;


	return 0;
}
