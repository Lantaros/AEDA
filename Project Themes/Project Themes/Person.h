#ifndef __Person__
#define __Person__

#include "Libraries.h"
#include "Date.h"

using namespace std;

class Person
{
public:
	Person();
	Person(string name, unsigned int age, char gender);
	virtual ~Person();
	string getName() const;
	unsigned int getAge() const;

private:
	string name;
	Date birthDate;
	char gender;
};


class Student : public Person
{
public:
	unsigned int getCurentYear() const;

private:
	unsigned int id;
	unsigned int currentYear;
	unsigned int yearClass;
	vector<Student *> currentGroup; //Him/herslef plus colleagues

};


class Professor : public Person
{
};

#endif

