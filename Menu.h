#ifndef __MENU__
#define __MENU__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include "Person.h"
#include "Project.h"
#include "Date.h"
#include "AcademicYear.h"
#include "Theme.h"
#include "Exceptions.h"
#include "utilities.h"

/*PART 2*/
#include "BST.h"
#include <queue>
#include <unordered_set>


#define NTRIES 4
#define BSTMAXTIME 5

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

    Person* findPersonName(const string &name);

    //Save files
    void savePeopleFile(const string fileName) const;
    void saveProjectsFile(const string fileName) const;
    void saveThemesFile(const string fileName) const;

    //Displays

    //Subs Menus
    //TIER 0
    void menu(); // show @ start
    void shutDown();

    //ALL YEARS
    void allYears();

    //TIER 1
    void generalDisplays();

    void displayAllStudents();

    void displayAllStudentsD();

    void displayRecentProjectTheme() const;

    void displayRecentProjectType() const;

    void displayNonGradedQueue();

    unsigned int numberProjectsYear(unsigned int year);

    void displayAllProjects() const;

    //
    void displayThemes() const;

    void displayThemesD() const;

    void addStudent();

    void deleteStudent();

    void deleteThemes();

    void compactabilityAlgorithm();

    //TIER 1
    //TIER 2

    //TIER3
    void displayStudentProjects() const;

    void displayProjectsYear();

    //Compactability
    void allPercentage(const vector<Person*> &group);

    int PointsRun(Theme &theme, const vector<Person*> &group);

    int PointsToPercentage(int points);

    vector<Person*> projPreviousStudents(Theme &t);

    //Utilities
    //Name Lengths
    static unsigned int maxNameLength; //max size name of all persons
    static unsigned int maxTitleLength; //max size of all projects title

    //-----------------------------------
    bool aYearExists(unsigned int &year);

    void checkIfMostRecent(const string &title, const unsigned int year);

    explicit MainMenu();

    vector<Person*> people;
    vector<Project*> projects;
    vector<Theme> themes;
    vector<AcademicYear> aYears;


    string asciiArt;
    bool changedPeople;
    bool changedThemes;
    FileNames fileNames;
    //Part2
    BST<RecentProject> recentProjects;
    priority_queue<NonGradedProject> nonGradedProjects;
    //unordered_set<Project*, ProjectHash, ProjectHash, ProjectHash> oldProjects;
};

bool comparePersonPtrAlpha(const Person* pLHS, const Person* pRHS);


#endif