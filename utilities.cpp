#include "utilities.h"

/**
 * fdsfdsfsd
 * @param name
 */
void normalizeName(string &name)
{

    //Beginning
    while (name[0] == ' ')
        name.erase(0, 1);

    while (name[name.size() - 1] == ' ')
        name.pop_back();


    //-------------------------------------------------------------
    size_t i = 1;
    while (i < name.size() - 1) //Erases character, if there are multiple blank spaces in the middle of the name
    {
        if (name[i] == ' ' && (name[i + 1] == ' '))
            name.erase(i, 1);
        else
            i++; //Only increase the cycle counter if it doesn't erase a space
    }
    //------------------------------------------------------------------


    //Change 1st letter in every word to upper case
    name[0] = toupper(name[0]); //1st word

    for (unsigned i = 1; i < name.size(); i++)
    {
        if(name[i] -1 == ' ')
            name[i] = toupper(name[i]);
    }

}