//
// Created by ruile on 19/11/2016.
//

#ifndef THEMES_UTILITIES_H
#define THEMES_UTILITIES_H

template <class T>
unsigned int numberDigits (T number)
{
    unsigned int counter = 0;
    while (number)
    {
        counter++;
        number /= 10;
    }
    return counter;
}

#endif //THEMES_UTILITIES_H
