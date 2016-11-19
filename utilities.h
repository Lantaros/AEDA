#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

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

//InvalidID EXCEPTION
class InvalidID
{
public:
    InvalidID(unsigned int id)
    { number = id; }

    unsigned int getNumber() const
    { return number; }

    unsigned int number;

};


#endif //THEMES_UTILITIES_H