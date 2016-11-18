#ifndef __FORM__
#define __FORM__

#include "Project.h"
#include "Person.h"

class AcademicYear
{
public:
	unsigned int getYear() const;

private:
	unsigned int year;
	vector <Project *> projects;
	vector <Person *> people;

};

#endif
