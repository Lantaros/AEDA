#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iostream>

using namespace std;


template<class T>
unsigned int numberDigits(T number)
{
    unsigned int counter = 0;
    while (number)
    {
        counter++;
        number /= 10;
    }
    return counter;
}

void normalizeName(string &name); //removes the blank spaces before, between names and after a full name/title
void normalizeType(string &type); //Removes strange characters
void waitInput();

template<class T>
void readOpt(T &n)
{
    T tmp = n;
    cin >> n;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(INT64_MAX, '\n');
        n = tmp;
    }
    else
    cin.ignore();//Ignores the \n left in the buffer
}


#endif //THEMES_UTILITIES_H
