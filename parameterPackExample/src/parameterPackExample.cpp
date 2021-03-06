//============================================================================
// Name        : parameterPackExample.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdarg.h>

using namespace std;

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair
{
	T1 key;
	T2 val;
};

template<class ...Args1> struct zip {
	template<class ...Args2> struct with {
		typedef Tuple<Pair<Args1,Args2>...> type;
	};
};

typedef zip<short,int>::with<unsigned short, unsigned>::type T1;

void myfun(int n_args, ...)
{
    va_list ap;
    va_start(ap, n_args);
    int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    cout << max;
    va_end(ap);
}

template<class ...Us> void f(Us... pargs)
{
   myfun(pargs...);
}




int main() {
	cout << "parameter pack example" << endl; // prints parameter pack example
    f<short,int,int,int>(1,7,2,-10	);


	return 0;
}
