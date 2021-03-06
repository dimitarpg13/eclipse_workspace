//============================================================================
// Name        : testTmp01.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

template<class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
	typename ForwardIterator1::value_type tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

template<class ForwardIterator>
void iter_swap(ForwardIterator i1, ForwardIterator i2)
{
	std::swap(*i1,*i2); // sometimes faster
	cout << "iter_swap specialization";
}

template<class ForwardIterator>
void print_vect( ForwardIterator begin, ForwardIterator end )
{
   while (begin != end)
   {
	   cout << *begin << ' ';
	   begin++;
   }

}

int main() {
	cout << "Templates Metaprogramming Test01" << endl; // prints Templates Metaprogramming Test01
	vector<int> vect{1,2,3,4,5};
    print_vect(vect.begin(),vect.end());
    cout << endl;
    iter_swap(vect.begin(),vect.begin()+2);
    print_vect(vect.begin(),vect.end());


	return 0;
}
