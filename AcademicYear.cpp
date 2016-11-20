#include "AcademicYear.h"


AcademicYear::AcademicYear(unsigned int year)
{
    this->year = year;
}


unsigned int AcademicYear::getYear() const
{
    return year;
}

void AcademicYear::addProject(Project *p)
{
    projects.push_back(p);
}


