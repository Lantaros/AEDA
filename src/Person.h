#ifndef __Person__
#define __Person__

#include "Libraries.h"
#include "Project.h"
#include "Date.h"

using namespace std;

class Person
{
public:
	Person();
	Person(string name, unsigned int age, char gender);
	virtual ~Person();
	string getName();
	unsigned int getAge();

private:
	string name;
	Date birthDate;
	char gender;
};


class Student: public Person
{
public:


private:
	unsigned int currentYear;
	vector<Project *> projects;

};


class Professor: public Person
{
};

#endif

