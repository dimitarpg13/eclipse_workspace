//============================================================================
// Name        : Test3.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

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

struct Entry
{
   string name;
   int number;

};

ostream& operator<<(ostream& os, const Entry& e)
{
	return os << "{\"" << e.name << "\", " << e.number << "}";
}

istream& operator>>(istream& is, Entry& e)
{
	char c, c2;
	if (is>>c && c=='{' && is>>c2 && c2=='"')
	{
       string name ;
       while (is.get(c) && c!='"')
    	   name += c;

       if (is>>c && c==',')
       {
    	   int number = 0;
    	   if (is>>number>>c && c=='}')
    	   {
    		   e = {name,number};
    		   return is;
    	   }
       }
	}

	is.setstate(ios_base::failbit);
	return is;
}

template<typename C, typename V>
vector<typename C::iterator> find_all(C& c, V v)
{
	vector<typename C::iterator> res;
	for (auto p = c.begin(); p!=c.end(); ++p)
	{
		if (*p == v)
			res.push_back(p);
	}

	return res;

}

template<typename T>
using Iterator = typename T::iterator; // T's iterator
template<typename C, typename V>
vector<Iterator<C>> find_all2(C& c, V v)
{
	vector<Iterator<C>> res;
	for (auto p = c.begin(); p!=c.end(); ++p)
	{
		if (*p == v)
			res.push_back(p);
	}

	return res;
}

void test ()
{
   string m {"Mary had a little lamb"};
   cout << m << endl;
   cout << "This is what I found: " << endl;
   for (auto p : find_all(m, 'a'))
   {
	   cout << *p;
   }

   cout << endl;


   list<double> ld {1.1, 2.2, 3.3, 1.1};
   //cout << ld << endl;
   for (auto p : find_all(ld, 1.1))
   {
	   cout << *p << ", ";
   }

   cout << endl;

   vector<string> vs { "red", "blue", "green", "green", "orange", "green" };
   for (auto p : find_all(vs, "red"))
   {
	   cout << *p << ", ";
   }

}

ostream_iterator<string> oo {cout};
istream_iterator<string> ii {cin};

struct Greater_than
{
	int val;
	Greater_than(int v) : val(v) {}
	bool operator () (const pair<string,int>& r) { return r.second > val; }
};

void f(map<string,int>& m)
{
	auto p = find_if(m.begin(), m.end(), Greater_than{42});

}

template<typename T>
void swap(T& a, T& b)
{
	T tmp{move(a)}; // move from a
	a = move(b);
	b = move(tmp);
}

template<typename T>
void swap(T& a, T&& b)
{
	T tmp{move(a)}; // move from a
	a = move(b);
	b = move(tmp);
}

template<typename T>
void swap(T&& a, T& b)
{
	T tmp{move(a)}; // move from a
	a = move(b);
	b = move(tmp);
}

void f(string& s, vector<int>& v)
{
	s.shrink_to_fit();  // make s.capacity() = s.size()
	swap(s,string {s});


}

int main() {
//	double ad[] = {1.1,2.2,3.3,4.4};
//
//
//	double s1 = accumulate2(ad,ad+4,0.0);
//	cout << "The result from accumulate over double is " << s1 << endl;
//	int s2 = accumulate2(ad,ad+4,0);
//	cout << "The result from accumulate over int is " << s2 << endl;
//
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

//	for (Entry ee; cin>>ee;)
//	{
//		cout << ee << '\n';
//	}

//	test();
//
//	*oo = "Hello";
//    //++oo;
//    *oo = "World!";

//	string from, to;
//	cin >> from >> to ; // get source and target file names
//	cout << "From file: " << from << endl;
//	cout << "To file: " << to << endl;
//	ifstream is { from }; // input stream for file from
//
//    istream_iterator<string> ii{is}; // input iterator for stream
//    istream_iterator<string> eos{};
//
//    ofstream os{to};  // output stream for file to
//    ostream_iterator<string> oo{os,"\n"};
//
//    vector<string> b{ii,eos};  // b is vector initialized from input
//    sort(b.begin(),b.end()); // sort the buffer
//
//    unique_copy(b.begin(),b.end(),oo); // copy buffer to output ,
//    								   // discard replicated values
//
//    return !is.eof() || !os;

//	const double temp[] = {double{1}, double{2}, 3.14 };
//	const initializer_list<double> tmp {double{1}, double{2}, 3.14}; //sizeof(temp)/sizeof(double));
//    vector<double> vec (tmp);
//    for (vector<double>::iterator it = vec.begin(); it != vec.end(); it++ )
//    	cout << *it << endl;

    vector<int> a;
    vector<int> b;

    a.push_back(1);
    a.push_back(13);
    a.push_back(7);
    a.push_back(0);

    b.push_back(11);
    b.push_back(1);

    swap(a, b);

    for (vector<int>::iterator it = a.begin(); it != a.end(); it++ )
      	cout << *it << endl;


	return 0;
}
