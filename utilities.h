//
// Created by ruile on 19/11/2016.
//

#ifndef THEMES_UTILITIES_H
#define THEMES_UTILITIES_H

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
