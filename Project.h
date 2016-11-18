#ifndef __PROJECT__
#define __PROJECT__

#include <string>
#include "Person.h"

class Project {
public:
    string getTitle() const;


private:
    string title, description;
    vector<unsigned int> usedYears;
    unsigned int difficulty;
    Date lastTimeUsed;
    vector<Student *> group;
};

class Research : public Project {
public:

private:
    string dataRepositoryFile;

};

class Analisys : public Project {
public:


private:
    vector<string> references;
};

class Development : public Project {
public:


private:
};

#endif
