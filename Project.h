#ifndef __PROJECT__
#define __PROJECT__

#include "Person.h"
#include <string>


class Project {
public:
    string getTitle() const;

protected:
    string title, description;
    vector<unsigned int> usedYears;
    unsigned int difficulty;
    unsigned int score;
    Date lastTimeUsed;
    vector<Student *> group;

};

class Research : public Project {
public:
    ostream& operator<<(ostream& out);
private:
    string dataRepositoryFile;

};

class Analysis : public Project {
public:
    ostream& operator<<(ostream& out);
private:
    vector<string> references;
};

class Development : public Project {
public:
    ostream& operator<<(ostream& out);
private:
};

#endif
