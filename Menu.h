#ifndef __MENU__
#define __MENU__

#include "Person.h"
#include "Date.h"
#include "Form.h"
#include <fstream>


class Menu
{
public:
	Menu();
	virtual ~Menu();
	unsigned int getMaxNameLength();
	void loadPeopleFile(string fileName);

	vector<Person *> people;
	vector<Form *> subjects;
	static unsigned int maxNameLength;
};


class FileNotFound
{
public:
	FileNotFound(string fileName)
	{
		name = fileName;
	}

	string name;
};



#endif