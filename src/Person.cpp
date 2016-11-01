#include "Person.h"


	string Person::getName()
	{
		return name;
	}
	unsigned int Person::getAge()
	{
		Date today;
		return birthDate.getYear() - today.getYear();
	}


