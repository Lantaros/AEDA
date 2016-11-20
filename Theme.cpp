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


