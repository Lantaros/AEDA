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
public:
    Project(string &title, string &date, string &body, ProjectType type);

    string getTitle() const;

    string getBody() const;

    Date getDate() const;
    unsigned int getYear() const;

    void getType(string &typeString) const;

    ProjectType getType() const;

    vector<Person*> &getGroup();

    vector<Person*> getGroupConst() const;

    vector<unsigned int> getGrades();

    virtual void print() const = 0;

    //Add Members
    void addStudent(Person* s);

    void addGrade(unsigned int grade);

    bool operator==(const Project &pRHS) const;

protected:
    ProjectType type;
    string title, body;
    Date date;
    //Notas - 1 por pessoa
    vector<Person*> group;
    vector<unsigned int> grades;

};

class Research : public Project
{
public:
    Research(string &title, string &date, string &body, string &references);

    virtual void print() const;

private:
    string references;

};

class Analysis : public Project
{
public:
    Analysis(string &title, string &date, string &body, string &dataRepositoryFile);

    virtual void print() const;

private:
    string dataRepositoryFile;
};

class Development : public Project
{
public:
    Development(string &title, string &date, string &body);

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

    Project* getPointer() const;

    bool operator<(const RecentProject &rRHS) const;

    bool operator==(const RecentProject &rRHS) const;

private:
    Project* projectPtr;
};

/*----------------PRIORITY-QUEUE------------------------*/
class NonGradedProject
{
public:
    NonGradedProject(Project* pointer);

    Project* getPointer() const;

    bool operator<(const NonGradedProject &rRHS) const;

private:
    Project* projectPtr;
};

void evaluateProject(Project* project);

/*---------------HASH--TABLE----------------------------*/
struct ProjectHash
{
    int operator()(const Project* pH) const
    {
        string title = pH->getTitle(), name;
        unsigned int hashValue = 0;

        for (unsigned int i = 0; i < title.size(); ++i) //Theme
        {
            hashValue += 37 * title[i];
        }

        Date date = pH->getDate();// Date

        hashValue += date.getDay() * date.getMonth() * date.getYear();

        for (unsigned int i = 0; i < pH->getGroupConst().size(); i++) //Group members' name
        {
            name = pH->getGroupConst()[i]->getName();
            for (unsigned int j = 0; j < name.size(); ++j)
            {
                hashValue += 37 * name[j];
            }
        }

        return hashValue;
    }

    bool operator()(const Project* pLHS, const Project* pRHS) const
    {
        return pLHS->getTitle() == pRHS->getTitle() && pLHS->getDate() == pRHS->getDate() && pLHS->getGroupConst() == pRHS->getGroupConst();
    }
};

#endif