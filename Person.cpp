#include "Person.h"


string Person::getName() const
{
	return name;
}
unsigned int Person::getAge() const
{
	Date today;
	return birthDate.getYear() - today.getYear();
}


