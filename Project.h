#ifndef __PROJECT__
#define __PROJECT__

#include "Person.h"
#include <string>

enum ProjectType
{
    RESEARCH, ANALYSIS, DEVELOPMENT
};//Only need for BST (recentProject) operator<

class Project
{
    //friend class MainMenu; //Workaround
public:
    Project(string &title, unsigned int year, string &body, ProjectType type);

    string getTitle() const;

    string getBody() const;
    unsigned int getYear() const;

    ProjectType getType() const;

    vector<Person*> &getGroup();
    virtual void print() const = 0;

    //Add Members
    void addStudent(Person* s);

    bool operator==(const Project &pRHS) const;

protected:
    ProjectType type;
    string title, body;
    unsigned int year;
    //Notas - 1 por pessoa
    vector<Person*> group;

};

class Research : public Project
{
public:
    Research(string &title, unsigned int year, string &body, string &references);

    virtual void print() const;

private:
    string references;

};

class Analysis : public Project
{
public:
    Analysis(string &title, unsigned int year, string &body, string &dataRepositoryFile);

    virtual void print() const;

private:
    string dataRepositoryFile;
};

class Development : public Project
{
public:
    Development(string &title, unsigned int year, string &body);

    virtual void print() const;

private:
    string body;
};

/*-------------------BST-----------------------------*/
class RecentProject
{
public:
    RecentProject(Project* pointer);

    void setPointer(Project* pointer);

    Project* getPointer();

    bool operator<(const RecentProject &rRHS) const;

    bool operator==(const RecentProject &rRHS) const;

private:
    Project* projectPtr;
};

#endif