#include "Project.h"
#include "Menu.h"

//Project

Project::Project(string &title, unsigned int year, string &body)
{
    Project::title = title;
    Project::year = year;
    Project::body = body;
}


string Project::getTitle() const
{
    return title;
}



bool Project::operator==(const Project &pRHS) const
{
    return title == pRHS.title;
}

void Project::addStudent(Person *s)
{
    for (unsigned int i = 0; i < group.size(); i++)
    {
        if ((*group[i]) == (*s))
            throw ExistingStudent(s->getName(), s->getId());
    }

    group.push_back(s);
}




//Research
Research::Research(string &title, unsigned int year, string &body, string &references) : Project(title, year, body)
{ this->references = references; }

/*ostream & Research::operator<<(ostream & out)
{
    out << "Research        " << score << "    " << difficulty << "    " << left << setw(Menu::maxTitleLength) << title << description;

    return out;

}*/


//Analysis
Analysis::Analysis(string &title, unsigned int year, string &body, string &dataRepositoryFile) : Project(title, year,
                                                                                                         body)
{ this->dataRepositoryFile = dataRepositoryFile; }
/*ostream & Analysis::operator<<(ostream & out)
{
    out << "Analysis       " << score << "    " << difficulty << "    " << left << setw(Menu::maxTitleLength) << title << description;

    return out;

}*/


//Development
Development::Development(string &title, unsigned int year, string &body) : Project(title, year, body)
{ this->body = body; }

/*ostream & Development::operator<<(ostream & out)
{
    out << "Development    " << score << "    " << difficulty << "    " << left << setw(Menu::maxTitleLength) << title << description;

    return out;

}*/



