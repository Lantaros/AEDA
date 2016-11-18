#ifndef __MENU__
#define __MENU__


#include "Person.h"
#include "Project.h"
#include "Date.h"
#include "AcademicYear.h"
#include <iomanip>
#include <fstream>

#define NTRIES 4

class Menu
{
public:
	Menu();

    Menu(string displays);
	virtual ~Menu();

    void printOptions() const;

    static unsigned int maxNameLength;

    unsigned int getMaxNameLength();

protected:
    string displayOptions;
};

class MainMenu : public Menu
{
public:
    MainMenu(string displays);

    void loadPeopleFile(string fileName);

    void loadAsciiArt();
    //void printAsciiArt() const;


    void loadFiles();

    vector<Person *> people;
    vector<Project *> projects;
    AcademicYear aYears;


    string asciiArt;


};

//Exceptions
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