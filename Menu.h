#ifndef __MENU__
#define __MENU__


#include "Person.h"
#include "Project.h"
#include "Date.h"
#include "AcademicYear.h"
#include "Theme.h"
#include "Exceptions.h"
#include "utilities.h"
#include <iomanip>
#include <fstream>

#define NTRIES 4

class Menu
{
public:
	Menu();


};


class MainMenu
{
public:
    //Loads
    void loadPeopleFile(string fileName);

    void loadProjects(string fileNames);
	void loadThemesFile(string fileName);

	void loadAsciiArt();
    void loadFiles();

    Person *findPersonName(const string &name);

	//Subs Menus
	//TIER 0
	void introMenu(); // show @ start
	void chooseYear();
	void shutDown();
	//ALL YEARS
		//TIER 1
		void displayAllProjects() const;
		void displayAllStudents() const;


	//SPECIFIC AYEAR
		//TIER 1
		void addOrRemoveMenu();
			//TIER 2
			void addStudent(); //add a student to the people vector
			void addProject(); //add a complete project to the projects vector
			//TIER 2
			void displaySpecificStudentYear() const;
	        	//TIER3
				void displayStudentProjects() const;
			void displayAllStudentsYear() const;
		void displayProjectsYear() const;
		void themesOptions();
			//TIER 2
			void displayThemes() const;
			void addTheme();
			void removeTheme();
		void checkCompatibility();
			//TIER 2
			void top5Results();
			void allResults();

	//Prints
    void printAsciiArt() const;
    void viewStudents() const; //show all students on the people vector
    void viewProjects() const; //show all projects on the projects vector




	vector<Person *> people;
    vector<Project *> projects;
    vector<Theme> themes;
    AcademicYear aYears;

    string asciiArt;

    //Name Lengths
    static unsigned int maxNameLength; //max size name of all persons
    static unsigned int maxTitleLength; //max size of all projects title


};

#endif