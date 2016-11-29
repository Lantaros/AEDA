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

unsigned int Project::getYear() const
{
    return year;
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

void Research::print() const
{
    cout <<this->getTitle() <<"\n" <<year <<"\n" <<this->body <<"\n\nReferences\n\n" <<references <<"\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout <<"\n" << *group[i];
    }
    cout << endl;
}


//Analysis
Analysis::Analysis(string &title, unsigned int year, string &body, string &dataRepositoryFile) : Project(title, year,
                                                                                                         body)
{ this->dataRepositoryFile = dataRepositoryFile; }


void Analysis::print() const
{
    cout <<this->getTitle() <<"\n" <<year <<"\n" <<this->body <<"\n\nData Repository\n\n" <<dataRepositoryFile <<"\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout <<"\n" <<*group[i];
    }
    cout << "\n";
}


//Development
Development::Development(string &title, unsigned int year, string &body) : Project(title, year, body)
{ this->body = body; }

void Development::print() const
{
    cout <<this->getTitle() <<"\n" <<year <<"\n\nCode\n\n"<<this->body <<"\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout <<"\n" <<*group[i];
    }
    cout << "\n";
}



