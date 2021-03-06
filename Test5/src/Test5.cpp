//============================================================================
// Name        : Test5.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
//#include <complex>

using namespace std;

int j = 110;

void afunc(const int * iptr)
{
	iptr = &j;
	//*iptr=111;
}



void bfunc(int * const iptr)
{
   //iptr
}

void f(string& s, int n, char ch)
{
	//s.move(string({n,ch}));
}

struct Point {
	int x, y, z;
	constexpr Point up(int d) { return {x,y,z+d}; }
	constexpr Point move(int dx, int dy) { return {x+dx,y+dy}; }
};

/*template<> class complex<double> {
public:
	constexpr complex (double re = 0.0, double im = 0.0);
	constexpr complex (const complex<float>& );
	explicit constexpr complex(const complex<long double>&);
	constexpr double real();
	void real(double);
	constexpr double imag();
	void imag(double);
	complex<double>& operator= (double);
	complex<double>& operator+=(double);

};*/

void print_modulo(const vector<int>& v, ostream& os, int m)
// output v[i] to os if v[i]%m == 0
{
	for_each(v.begin(), v.end(),
			[&os,m](int x) { /*if (x%m == 0)*/ os << x << '\n'; });
};

void print_vect(const vector<int>& v, ostream& os)
// output v[i] to os if v[i]%m == 0
{
	for_each(v.begin(), v.end(),
			[&os](int x) { os << x << '\n'; });
};

/*int n = 0;
struct C {
  explicit C(int) {}
  C(const C&) { ++n; } // the copy constructor has a visible side effect
};                     // it modifies an object with static storage duration
*/

void f(vector<int>& v)
{
	bool sensitive = true;
	sort(v.begin(),v.end(),
			[sensitive](int x, int y) { return sensitive ? x<y : abs(x) < abs(y); } );
};

//template<typename... Values> class mytuple
//{
//public:
//   Values... val;
//};
//mytuple<int, vector<int>, map<string, vector<int> > > some_instance_name;

void printf1(const char * s)
{
	while (*s)
	{
		if (*s == '%')
		{
			if (*(s + 1) == '%') {
				++s;
			}
			else
			{
				throw std::runtime_error("invalid format string: missing arguments!");
			}
		}
		cout << *s++;
	}
}

/*template<typename T, typename... Args>
void printf(const char *s, T value, Args... args)
{
	while (*s)
	{
		if (*s == '%') {
			if (*(s + 1) == '%') {
				++s;
		    }
		    else {
			   cout << value;
			   s += 2;
			   printf(s, args...);  // call even when *s == 0 to detect extra arguments
			   return;
		    }
		}
		cout << *s++;
	}

}*/

template<typename T, typename... Args>
void printf1(const char *s, T value, Args... args)
{
	while (s && *s)
	{
		if (*s == '%' && *++s!='%')
		{
			cout << value;
			return printf1(++s, args...);
		}
		cout << *s++;
	}
	throw runtime_error("extra arguments provided to printf");
}

template<typename U, typename V>
ostream& operator<<(ostream& os, const pair<U,V>& p)
{
	return os << '{' << p.first << ',' << p.second << '}';
}

void print_all(const map<string,int>& m, const string& label)
{
	cout << label << ":\n{\n";
    for_each(m.begin(), m.end(),
    		[](const pair<string,int>& p) { cout << p << '\n'; }  );
    cout << "}\n";
}

void algo (vector<int>& v)
{
	int count = v.size();
	generate(v.begin(),v.end(),
	     [count]()mutable{ return --count;});

}

void f1(double y)
{
	cout << "Calling f(double y) : "<< y;
}

void g(double y)
{
	auto z0 = [&] { f1(y); };
	auto z1 = [=] (int x) { return x+y; }; // return type is double
	//auto z2 = [y] { if (y > 0.0) return 1; else return 2; };
	auto z3 = [y]() { return (y) ? 1 : 2; };
	auto z4 = [=,y]()->int { if (y) return 1; else return 2; };
}

void f (string& s1, string& s2)
{
	function<void(char *b, char* e)> rev =
			[&rev](char* b, char* e) { if (1 < e-b) { swap(*b, *--e); rev(++b,e); } };
    rev(&s1[0],&s1[0]+s1.size());
    rev(&s2[0],&s2[0]+s2.size());
}

struct Sum {
	int sum;
	Sum() : sum(0) {};
	void operator()(int n) { sum += n; }
};

class Modulo_print
{
	ostream& os; // members to hold the capture list
	int m;
public:
	Modulo_print(ostream& s, int mm) : os(s), m(mm) {}
	void operator()(int x) const
	{
		if (x%m == 0) os << x << '\n';
	}
};

constexpr int fac (int n)
{
	return (n>1) ? n*fac(n-1) : 1;
}

constexpr int ftbl[] {0, 1, 1, 2, 3, 5, 8, 13};

constexpr int fib(int n)
{
	return (n<sizeof(ftbl)/sizeof(*ftbl)) ? ftbl[n] : fib(n-2)+fib(n-1);
}

template<typename T>
void f1(initializer_list<T>)
{

}

struct S
{
	int a;
	string s;
};

void f2(S)
{

}

template<typename T, int N>
void f3(T (&r)[N])
{

}

void f4(int)
{

}

void g()
{
	f1({1,2,3,4});
	f2({1,"MKS"});
	//f3({1,2,3,4});
	f4({1});
};

struct User
{
	const char* name;
	const char* id;
	int dept;
};

vector<User> heads = {
		{"Ritchie D.M.",	"dmr",	11271},
		{"Sethi R.",	"ravi",	11272},
		{"Szymaniski T.G.", "tgs", 11273},
		{"Schryer N.L.", "nls", 11274},
		{"Schryer N.L.", "nls", 11275},
		{"Kernighan B.W.", "bwk", 11276}
};

void print_id(vector<User>& v)
{
	for (auto& x : v)
	{
		cout << x.name << '\t' << x.id << '\t' << x.dept << '\n';
	}
}


// sort the "n" elements of vector "base" into increasing order
// using comparison sort function pointed by "cmp". The elements are of size "sz".
// Shell sort (Knuth, Vol3, pg84)


void ssort(void* base, size_t n, size_t sz, int cmp(const void*, const void*))
{
   for (int gap=n/2; 0<gap; gap/=2)
   {
	   for (int i=gap; i!=n; i++)
	   {
		   for (int j=i-gap; 0<=j; j-=gap)
		   {
			   char* b = static_cast<char*>(base); // necessary cast
			   char* pj = b+j*sz; // &base[j]
               char* pjg = b+(j+gap)*sz; // &base[j+gap]
               if (cmp(pjg,pj)<0)  // swap &base[j] with &base[j+gap]
               {
            	   for (int k=0; k<sz; k++)
            	   {
            	      char temp = pj[k];
            	      pj[k] = pjg[k];
            	      pjg[k] = temp;
            	   }
               }

		   }
	   }
   }
}

int cmp1(const void* p, const void* q) // compare name strings
{
	return strcmp(static_cast<const User*> (p)->name, static_cast<const User*> (q)->name);
}

int cmp2(const void* p, const void* q) // compare dept numbers
{
	return static_cast<const User*> (p)->dept - static_cast<const User*> (q)->dept;
}

#define err_print(...) fprintf(stderr, "error: %s %d",__VA_ARGS__)

int main() {

	//int i = 101;
	//afunc(&i);
	//cout << "j=" << j << endl;
    //int* ii  = (int*) ((int[]){ 1, 2, 3 });
    //ii[0] = 3;
    //cout << ii[0];

//	constexpr Point origo {0,0};
//	constexpr int z = origo.x;
//
//	constexpr Point a[] = {
//			origo, Point{1,1}, Point{2,2}, origo.move(3,3)
//	};
//
//	constexpr int x = a[1].x;
//
//	constexpr Point xy{0,sqrt(9)};
//
//	cout << "xy.x="  << xy.x << ", xy.y=" << xy.y << endl;

//	 C c1(42); // direct-initialization, calls C::C(42)
//	  C c2 = C(42); // copy-initialization, calls C::C( C(42) )
//
//	  std::cout << n << std::endl; // prints 0 if the copy was elided, 1 otherwise

    vector<int> v { 1, 4, 7, 11, 3 };
//    //cout << v.size();
//    //print_modulo(v, cout, 6);
//    f(v);
//    print_modulo(v, cout, 6);
//printf1("%d %d", 10, 11);

//algo(v);
//print_vect(v, cout);

//    string s1 = "My first string";
//    string s2 = "My second string";
//    f(s1,s2);

//    cout << "s1=" << s1 << endl;
//    cout << "s2=" << s2 << endl;
//	Sum s = for_each(v.begin(), v.end(), Sum());

//	cout << s.sum;

//    constexpr int f9 = fac(9);

//    cout << f9;

    cout << "Using shell sort: Heads in alphabetical order:\n";
    ssort(&heads[0],6,sizeof(User),cmp1);
    print_id(heads);

    cout << "Using shell sort: Heads in order of department number:\n";
    ssort(&heads[0],6,sizeof(User),cmp2);
    print_id(heads);

    cout << "Using STL sort: Heads in alphabetical order:\n";
    sort(heads.begin(), heads.end(), [](const User& x, const User& y) { return x.name < y.name; });
    print_id(heads);

    cout << "Using STL sort: Heads in order ot department number:\n";
    sort(heads.begin(), heads.end(), [](const User& x, const User& y) { return x.dept < y.dept; });
    print_id(heads);


    err_print("The answer", 54);

	return 0;
}
