#ifndef __Project__
#define __Project__

#include <string>
#include "Person.h"

class Project
{
public:


private:
	string title, description;
	vector<Student *> group;
};

class Research: public Project
{
public:


private:

};

class Analisys: public Project
{
public:


private:
};

class Development: public Project
{
public:


private:
};

#endif
