//============================================================================
// Name        : OptimizedCopyExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <boost/type_traits.hpp>

using namespace std;

// opt::copy
// same semantics as std::copy
// calls memcpy where appropriate

namespace detail {
   template<typename I1, typename I2, bool b>
   I2 copy_imp(I1 first, I2 last, I2 out, const boost::integral_constant<bool, b>&)
   {
	   while (first != last)
	   {
		   *out = *first;
		   ++out;
		   ++first;
	   }
	   return out;
   }

   template<typename T>
   T* copy_imp(const T* first, const T* last, T* out, const boost::true_type&)
   {
	  memmove(out, first, (last-first) * sizeof(T));
	  return out + (last-first);
   }

   template<typename I1, typename I2>
   inline I2 copy(I1 first, I1 last, I2 out)
   {
	   //
	   // we can copy with memcpy if T has a trivial assignment operator,
	   // and if the iterator arguments are actually pointers (this last
	   // requirement we detect with overload resolution)
	   //
	   typedef typename std::iterator_traits<I1>::value_type value_type;
	   return detail::copy_imp(first, last, out, boost::has_trivial_assign<value_type>());

   }


}

int main() {
	cout << "Optimized Copy Example (From Boost.TypeTraits tutorial)" << endl; // prints Optimized Copy Example (From Boost.TypeTraits tutorial)
    int v[] = { 1, 3 , 4 , 5, 11 };
    int *w = new int[5];
    cout << "Before copy" << endl;
    detail::copy(&v[0], &v[5],&w[0]);
    cout << "Start loop around the copied array"<<endl;
    for (int i=0; i<5; i++)
    	cout << w[i] << endl;
	return 0;
}
