//============================================================================
// Name        : HackerRankPureStorage2.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <climits>

using namespace std;

// Problem Statement:
//
// Problem 2 from SelectedProblems 8-25_to_8-31
// Let N denotes an integer. Remove all sequential nodes of the list
// which are repeating more than N times leaving just N values/nodes from
// the whole repeating subsequence. (Count pruning problem)

struct node
{
	node (int v) : v(v), next(NULL) {};


	int v;
	node * next;
};


void init_list(node ** list, int n, int arr[])
{
	if (n < 1)
		return;

   *list = new node(arr[0]);
   node * last = *list;

   int i=1;
   for (; i < n; i++)
   {
      last->next = new node(arr[i]);
      last = last->next;
   }
};



void remove_repetitions(node ** list, int N)
{
    node * c = *list, * n = NULL, * p = NULL;
    int count = 0;
    while (c != NULL)
    {
        n = c->next;
        while (n != NULL && n->v == c->v && count < N - 1)
        {
        	c = c->next;
        	n = n->next;
        	count++;
        };

        while (n != NULL && n->v == c->v)
        {
        	p = n;
        	n = n->next;
        	delete p;
        }
        count = 0;
        c->next = n;
        c=c->next;
    }
}

bool validate_list(node ** list, int arr[], int n)
{
    node * cur = *list;

    int indx = 0, val = INT_MIN;
    while (cur != NULL)
    {
        if (indx < n)
        {
           val = arr[indx];
           if (cur->v != val)
           {
        	   cout << "The supplied array has a value at index " << indx << " different than the supplied list node value!" << endl;
           }
        }
        else
        {
            cout << "The supplied array has less elements than the supplied list!" << endl;
        	return false;
        }
    	cur=cur->next;
    	indx++;
    }

    if (indx < n-1)
    {
    	cout << "The supplied list has less elements than the supplied array!" << endl;
    }

	return true;
}


bool test_case1()
{
    node * list = NULL;
    int arr[] = {1, 2, 5, 2, 2, 3, 7, 8};
    init_list(&list, 8 , arr);
    remove_repetitions(&list, 2);

    int res[] = {1, 2, 5, 2, 2, 3, 7, 8};
    return validate_list(&list, res, 8);
}

bool test_case2()
{
    node * list = NULL;
    int arr[] = {1, 2, 5, 2, 2, 2, 3, 7, 8};
    init_list(&list, 9 , arr);
    remove_repetitions(&list, 2);

    int res[] = {1, 2, 5, 2, 2, 3, 7, 8};
    return validate_list(&list, res, 8);

}

bool test_case3()
{
    node * list = NULL;
    int arr[] = {1, 1, 1, 1, 2, 5, 2, 2, 2, 3, 7, 8};
    init_list(&list, 12 , arr);
    remove_repetitions(&list, 2);

    int res[] = {1, 1, 2, 5, 2, 2, 3, 7, 8};
    return validate_list(&list, res, 9);
}


int main() {
	cout << "HackerRank coding challenge for PureStorage interview" << endl; // prints HackerRank coding challenge for PureStorage interview

	if (!test_case1())
	{
		cout << "test_case1 has failed!" << endl;
	}

	if (!test_case2())
	{
		cout << "test_case2 has failed!" << endl;
	}

	if (!test_case3())
	{
		cout << "test_case3 has failed!" << endl;
	}


	return 0;
}


