//============================================================================
// Name        : testPangrams.cpp
// Author      : Dimitar Gueorguiev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


const int capA = 0x41;
const int capZ = 0x5a;
const int smlA = 0x61;
const int smlZ = 0x7a;

char convertToLarge(char ch)
{
   return ch - 0x20;
}

bool isSmallCap(char ch)
{
    if ( ch >= smlA && ch <= smlZ )
        return true;
    else
        return false;
}

bool isLargeCap(char ch)
{
    if ( ch >= capA && ch <= capZ )
        return true;
    else
        return false;
}

bool isLetter(char ch)
{

   if ( (ch >= capA && ch <= capZ) ||
        (ch >= smlA && ch <= smlZ) )
       return true;
   else
       return false;
}

bool isPangram(char const * cstr)
{

    if (cstr == NULL)
        return false;

    int i=0;
    char ch;
    bool present[26] = {};
    //for (i = 0 ; i < 26; i++)
    //    present[i]=false;
    while (ch = cstr[i++])
    {
        if (isSmallCap(ch))
        {
            ch = convertToLarge(ch);
            present[ch-capA]=true;
        }
        else if (isLargeCap(ch))
        {
            present[ch-capA]=true;
        }
    }

    for (i = 0; i < 26; i++)
        if (!present[i])
        {
           return false;
        }

    return true;

}



int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    //char arr[1000] = "We promptly judged antique ivory buckles for the next prize";
    //char arr[1000] = "We promptly judged antique ivory buckles for the prize";
    string str;
    getline(cin,str);


    cout << str << endl;

    if (isPangram(str.c_str()))

        cout << "pangram";

    else

        cout << "not pangram";





    return 0;

}
