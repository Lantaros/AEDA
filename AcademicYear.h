#ifndef __FORM__
#define __FORM__

#include "Project.h"
#include "Person.h"

class AcademicYear
{
public:
    AcademicYear(unsigned int year);
	unsigned int getYear() const;

    void addProject(Project *p);
private:
	unsigned int year;
	vector <Project *> projects;
};

#endif
