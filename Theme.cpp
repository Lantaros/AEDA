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

unsigned int Theme::getScore() const
{
    return score;
}

unsigned int Theme::getDifficulty() const
{
    return difficulty;
}


unsigned int Theme::getLastYearUsed() const
{
    return lastYearUsed;
}

ostream &operator<<(ostream &out, const Theme &t)
{
    out << t.getType() << " " << t.getTitle() << setw(12);
    out << t.getDifficulty();

    return out;
}




