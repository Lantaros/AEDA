#ifndef __PERSON__
#define __PERSON__

#include "Libraries.h"
#include "Date.h"
#include <iomanip>

using namespace std;

class Person
{
public:
	Person(const string & name, const Date & birthday);
	Person(string & name, Date & birthday);
	string getName() const;
	unsigned int getAge() const;
	virtual void print() const = 0;

protected:
	const string name;
	const Date birthDate;
};


class Student : public Person
{
public:
	Student(const string &name, const Date &birthDate,
		const unsigned int &id, const unsigned int &currentYear, const unsigned int &yearClass);
	Student(string &name, Date &birthDate, unsigned int &id);

	~Student();
	unsigned int getCurentYear() const;
	virtual void print() const;
	ostream& operator<<(ostream& out);

private:
	const unsigned int id;
	unsigned int currentYear;
    unsigned int yearClass; //class
	vector<Student *> currentGroup; //Him/herself plus colleagues

};


class Professor : public Person
{
public:
	Professor();
	virtual void print() const;
	ostream& operator<<(ostream& out);
private:
	const unsigned int id;
};

#endif

