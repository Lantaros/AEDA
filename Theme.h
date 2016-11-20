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

private:
    string type, title, description;
    unsigned int score, difficulty;
};


#endif
