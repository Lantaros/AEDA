#include "Theme.h"

Theme::Theme(string type, string title, string description, unsigned int score, unsigned int diff)
{
    this->type = type;
    this->title = title;
    this->description = description;
    this->score = score;
    this->difficulty = diff;
}


string Theme::getType() const
{
    return type;
}

string Theme::getTitle() const
{
    return title;
}

string Theme::getDescription() const
{
    return description;
}

/*ostream &operator<<(ostream& out, const Theme  &t)
{
    out <<t.type <<" " <<t.title <<" " << t.score <<" " <<t.difficulty   <<"\n\nDescription\n\n" <<t.description;

    return out;
}*/


