#ifndef _THEME_H
#define _THEME_H

#include <string>

using namespace std;

class Theme
{
public:
    Theme(string type, string title, string description,
          unsigned int score, unsigned int diff);

    string getType() const;

    string getTitle() const;

    string getDescription() const;

    // friend ostream &operator<<(ostream& out, const Theme  &t);
    friend class MainMenu;

private:
    string type, title, description;
    unsigned int score, difficulty, lastYearUsed;
};

//ostream &operator<<(ostream& out, const Theme  &t);


#endif
