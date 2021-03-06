//============================================================================
// Name        : Test2.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <thread>
#include "concurentqueue.h"

using namespace std;
using namespace Algorithms;

void func()
{

}

void foo()
{
	// simulate expensive operation
	this_thread::sleep_for(chrono::seconds(1));
}

void bar()
{
	// simulate expensive operation
	this_thread::sleep_for(chrono::seconds(1));
}

int main() {

	cout << "Starting the thread...";
	thread t(func);
	t.join();
	cout << "Ending the thread." << endl; // prints !!!Hello World!!!

	cout << "Starting the first helper ...";
	thread helper1(foo);

	cout << "Starting the second helper ...";
	thread helper2(bar);

	cout << "Waiting for the helpers to finish ... ";
	helper1.join();
	helper2.join();

	cout << "Done with the two helpers." << endl;

	thread t2;
	cout << "Before starting - joinable: " << t2.joinable() << endl;

	t2 = thread(foo);
	cout << "After starting - joinable: " << t2.joinable() << endl;

	t2.join();
	concurent_queue<string> q;
    //string s;

	return 0;
}
