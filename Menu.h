#ifndef __MENU__
#define __MENU__

#include "Person.h"
#include "Date.h"
#include "AcademicYear.h"
#include <fstream>

#define NTRIES 4

class Menu
{
public:
	Menu();
	virtual ~Menu();
	unsigned int getMaxNameLength();
	void loadPeopleFile(string fileName);

	void loadFiles();

	vector<Person *> people;
	vector<Project *> projects;
    AcademicYear aYears;
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

struct FileNames
{
	string peopleFile, projectsFile, themeIndexFile;
};

#endif