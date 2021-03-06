//============================================================================
// Name        : testTmp02.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iterator> // for iterator traits
#include <utility>  // for swap

using namespace std;

namespace my_mpl
{


template<bool use_swap> struct iter_swap_impl; // see text

template< class ForwardIterator1, class ForwardIterator2 >
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
	typedef iterator_traits<ForwardIterator1> traits1;
	typedef typename traits1::value_type v1;
	typedef typename traits1::reference r1;

	typedef iterator_traits<ForwardIterator2> traits2;
	typedef typename traits2::value_type v2;
	typedef typename traits2::reference r2;

	bool const use_swap =    boost::is_same<v1,v2>::value
						  && boost::is_reference<r1>::value
						  && boost::is_reference<r2>::value;

	iter_swap_impl<use_swap>::do_it(i1,i2);

}


template<>
struct iter_swap_impl<true> // the "fast" one
{
	template< class ForwardIterator1, class ForwardIterator2 >
	static void do_it (ForwardIterator1 i1, ForwardIterator2 i2)
	{
		std::swap(*i1, *i2);
	}
};

template<>
struct iter_swap_impl<false> // the one that always works
{
	template<class ForwardIterator1, class ForwardIterator2>
	static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
	{
		typename iterator_traits<ForwardIterator1>::value_type tmp = *i1;
		*i1 = *i2;
		*i2 = tmp;
	}
};

template<class ForwardIterator>
void print_vect( ForwardIterator begin, ForwardIterator end )
{
   while (begin != end)
   {
	   cout << *begin << ' ';
	   begin++;
   }

}

}

using namespace std;
using namespace my_mpl;

int main() {
	cout << "Template Metaprogramming Book code excerpt 02" << endl; // prints Template Metaprogramming Book code excerpt 02
	vector<int> vect{1,2,3,4,5};
	print_vect(vect.begin(),vect.end());
	cout << endl;
	vector<int>::iterator i1 = vect.begin();
	vector<int>::iterator i2 = vect.begin() + 2;
	my_mpl::iter_swap(i1,i2);
	//iter_swap_impl<true>::do_it(i1,i2);
	print_vect(vect.begin(),vect.end());


	return 0;
}
