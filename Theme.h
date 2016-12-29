#ifndef _THEME_H
#define _THEME_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Theme
{
    friend class MainMenu; //
public:
    Theme(string type, string title, string description, unsigned int diff);

    string getType() const;
    string getTitle() const;
    string getDescription() const;
    unsigned int getDifficulty() const;
    unsigned int getLastYearUsed()const;

private:
    string type, title, description;
    unsigned int difficulty, lastYearUsed;
};

ostream &operator<<(ostream& out, const Theme  &t);


#endif
