#ifndef __MENU__
#define __MENU__

#include <iomanip>
#include <fstream>
#include <algorithm>

#include "Person.h"
#include "Project.h"
#include "Date.h"
#include "AcademicYear.h"
#include "Theme.h"
#include "Exceptions.h"
#include "sortNSearch.h"
#include "utilities.h"


#define NTRIES 4


class MainMenu
{
public:
    //Loads
    void loadPeopleFile(string fileName);

    void loadProjects(string fileNames);

    void loadThemesFile(string fileName);

    void loadAsciiArt();

    void loadFiles();

    void setUpAYears();

    Person *findPersonName(const string &name);


    //Displays

    //Subs Menus
    //TIER 0
    void menu(); // show @ start
    void shutDown();

    //ALL YEARS
    void allYears();

    //TIER 1
    void generalDisplays();

    void displayAllProjects() const;

    void displayAllStudents();



    void displayThemes() const;

    void manageThemes();

    void addTheme();

    void removeTheme();

    void addStudent();

    void compactabilityAlgorithm();

    //SPECIFIC AYEAR
    void specificYear();
    //TIER 1
    //TIER 2

    //TIER3
    void displayStudentProjects() const;

    void displayProjectsYear(const unsigned int year) const;

    void themesOptions();
    //TIER 2

    void checkCompatibility();

    //TIER 2
    void top5Results();

    void allResults();

    //Prints
    void printAsciiArt() const;

    void viewStudents() const; //show all students on the people vector
    void viewProjects() const; //show all projects on the projects vector


    //Compactability
    int allPercentage(const vector<Person *> &group);

    int PointsRun(Theme &theme, const vector<Person *> &group);

    int PointsToPercentage(int points);

    vector<Person *> projPreviousStudents(Theme &t);

    //Utilities
    //Name Lengths
    static unsigned int maxNameLength; //max size name of all persons
    static unsigned int maxTitleLength; //max size of all projects title
    bool aYearExists(unsigned int &year);

    void checkIfMostRecent(const string &title, const unsigned int year);


    vector<Person *> people;
    vector<Project *> projects;
    vector<Theme> themes;
    vector<AcademicYear> aYears;

    string asciiArt;
};

bool comparePersonPtrAlpha(const Person *pLHS, const Person *pRHS);


#endif