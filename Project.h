#ifndef __PROJECT__
#define __PROJECT__

#include "Person.h"
#include <string>


class Project
{
public:
    Project(string &title, unsigned int year, string &body);

    string getTitle() const;

    //Add Members
    void addStudent(Person *s);

    bool operator==(const Project &pRHS) const;

protected:
    string title, body;
    unsigned int year;
    //Notas - 1 por pessoa
    vector<Person *> group;

};

class Research : public Project
{
public:
    Research(string &title, unsigned int year, string &body, string &references);

    ostream &operator<<(ostream &out);

private:
    string references;

};

class Analysis : public Project
{
public:
    Analysis(string &title, unsigned int year, string &body, string &dataRepositoryFile);

    ostream &operator<<(ostream &out);

private:
    string dataRepositoryFile;
};

class Development : public Project
{
public:
    Development(string &title, unsigned int year, string &body);

    ostream &operator<<(ostream &out);

private:
    string body;
};

#endif
