#include "Project.h"
#include "Menu.h"

//Project

bool Project::operator==(const Project &pRHS) const
{
    return title == pRHS.title;
}

//Research

ostream & Research::operator<<(ostream & out)
{
    out << "Research        " << score << "    " << difficulty << "    " << left << setw(Menu::maxTitleLength) << title << description;

    return out;

}


//Analysis

ostream & Analysis::operator<<(ostream & out)
{
    out << "Analysis       " << score << "    " << difficulty << "    " << left << setw(Menu::maxTitleLength) << title << description;

    return out;

}

//Development

ostream & Development::operator<<(ostream & out)
{
    out << "Development    " << score << "    " << difficulty << "    " << left << setw(Menu::maxTitleLength) << title << description;

    return out;

}


