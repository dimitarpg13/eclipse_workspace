//============================================================================
// Name        : coding.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <cmath>
#include <initializer_list>
#include <string>
#include <complex>
#include <vector>

#include "Vector.h"
#include "VectorT.h"
#include "Complex.h"
#include "Container.h"
#include "Vectorcontainer.h"
#include "Listcontainer.h"
#include "Lessthan.h"
#include "IndustryTree.h"
#include "MemsetTest.h"
#include "LCS.h"
#include "String.h"


using namespace std;
using namespace Algorithms;

double sqrt_sum(Vector& v)
{
	double sum = 0;
    for (int i=0; i!=v.size(); ++i)
    	sum+=sqrt(v[i]);

	return sum;
};

Complex operator + (Complex a, Complex b)
{
    return a += b;
};


Complex operator- (Complex a, Complex b)
{
    return a -= b;
};

Complex operator- (Complex a)
{
    return {-a.real(), -a.imag() };
};

Complex operator* (Complex a, Complex b)
{
   	return a*=b;
};

Complex  operator/ (Complex a, Complex b)
{
   	return a/=b;
};

void myfun(initializer_list<double> list)
{

}

void use(Container& c)
{
	const int sz = c.size();

	for (int i = 0; i < sz; i++)
	{
		cout << c[i] << '\n';
	}

}

void g()
{
	Vector_container vc(10); // ten elements
	use(vc);
}

void h()
{
	List_container lc = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	use(lc);
}

void write(const VectorT<string>& vs)
{
	for (int i = 0; i != vs.size(); ++i)
		cout << vs[i] << '\n';
}

template<typename Container, typename Value>
Value sum(const Container& c, Value v)
{
//	for (auto x : c)
//	{
//		v+=x;
//	}
    return v;
}

void user(VectorT<int>& vi,
		std::list<double>& ld,
		std::vector<complex<double>>& vc)
{
   int x = sum(vi,0);

}

class NotEnoughElements {};

template <typename Container, typename Function>
typename Container::value_type
Reduce(const Container& c, Function fn) throw (NotEnoughElements)
{
	if (c.begin() == c.end())
		throw NotEnoughElements();

  	typename Container::const_iterator it = c.begin();
   	typename Container::value_type sum = (*c.begin());
    while (++it != c.end())
    {
    	sum = fn(sum, *it);
    }

   	return sum;
}

template<typename Iter, typename Val>
Val sum(Iter first, Iter last)
{
	Val s = 0;
	while (first != last)
	{
		s = s + *first;
		++first;
	}
	return s;
}

template<typename Iter, typename Val>
Val accumulate2(Iter first, Iter last, Val s)
{
	while (first != last)
	{
		s = s + *first;
		++first;
	}

	return s;
}

template<typename Iter, typename Val, typename Oper>
Val accumulate3(Iter first, Iter last, Val s, Oper op)
{
	while (first != last)
	{
	   s = op(s,*first);
	   ++first;
	}

	return s;
}

class conststr {
	const char * p;
	std::size_t sz;
public:
	template<std::size_t N>
	constexpr conststr ( const char (&a)[N] ) : p(a), sz(N-1) {}
	const char operator[] (std::size_t n) const {
		return n < sz ? p[n] : throw std::out_of_range("");
	}
	constexpr std::size_t size() const { return sz; }
};

constexpr std::size_t countlower(conststr s, std::size_t n = 0, std::size_t c = 0)
{
	//return n == s.size() ? c : (s[n] >= 'a' && s[n] <= 'z' ? countlower(s, n+1, c+1) : countlower(s, n+1, c) );
	 return n == s.size() ? c :
	           s[n] >= 'a' && s[n] <= 'z' ? countlower(s, n+1, c+1) :
	           countlower(s, n+1, c) ;

}

template<int n> struct constN {
	constN() { std::cout << n << endl; }
};

int main() {

//vector<int> v;
//v.push_back(1);
//v.push_back(2);
//v.push_back(3);
//v.push_back(4);
//v.push_back(5);
//
//int sum = Reduce<vector<int>, plus<int>>(v, plus<int>());
//cout << "The sum is " << sum << "\n";
//
//vector<int> vv;
//try
//{
//	sum = Reduce<vector<int>, plus<int>>(vv, plus<int>());
//
//}
//catch (NotEnoughElements e)
//{
//	cout << "NotEnoughElements was thrown!\n";
//}
//


//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//
//	Complex a = {1.0, -1.0};
//	Complex b = {3.0, 1.0};
//	Complex c = a * b;
//
//	cout << "Re(c)= " << c.real() << " Im(c) = " << c.imag() << "\n";
//
//	auto il = {3.0, 4.6};
//
//	Vector v = { 1.0, 1.1, 4.5 };
//    g();
//	h();
//
//	VectorT<string> vs(17);
//    write(vs);
//    char  aa[] = "Hello";
//    cout << "\n" << aa;
//
//    Less_than<int> lti { 42 };

//
//	IndustryTree itree("./industries.txt");
//    itree.addCompanies("./companies.txt");
//    itree.printIndustries();
//    itree.findCompanies("Health Care", "CompanyName");
//    itree.findIndustries("Gemvax & Kael");

 //   MemsetTest * test = new MemsetTest();

//	// 4, 2, 1, 2, 3, 4, 3, 5, 1, 2, 4, 6, 5
//	vector<int> v;
//	v.push_back(4);
//	v.push_back(2);
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(3);
//	v.push_back(4);
//	v.push_back(3);
//	v.push_back(5);
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(4);
//	v.push_back(6);
//	v.push_back(5);
//
//    LCS lcs;
//    lcs.print(v);

//	double ad[] = {1.1,2.2,3.3,4.4};
//	double s = sum<double*,double>(ad,ad+4);
//    cout << "The sum of ad elements is " << s << endl;
//    double s1 = accumulate2(ad,ad+4,0.0);
//    cout << "The result from accumulate2 over double is " << s1 << endl;
//    int s2 = accumulate2(ad,ad+4,0);
//    cout << "The result from accumulate2 over int is " << s2 << endl;
//    double s3 = accumulate3(ad, ad+4, 0.0, std::plus<double>{});
//    cout << "The result from accumulate3 using std::plus<double> is " << s3 << endl;
//    double s4 = accumulate3(ad, ad+4, 1.0, std::multiplies<double>{});
//    cout << "The result from accumulate3 using std::multiplies<double> is " << s4 << endl;

//	String<char> s;
//	vector<int> v;
//	vector<int>::value_type t1;

	//constN<countlower("Hello World!")>();
    //conststr cstr("Hello World!");
    //cout << cstr.size() << endl;
    //cout << countlower("Hello World!") << endl;
    //constN<10>();
    //int s=123;
    //constN<s>();
	return 0;
}
