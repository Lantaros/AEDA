#include "Menu.h"

unsigned int MainMenu::maxNameLength = 0;
unsigned int MainMenu::maxTitleLength = 0;


MainMenu::MainMenu(): recentProjects(RecentProject(nullptr))
{}

void MainMenu::loadPeopleFile(string fileName)
{
    string stringID, name, date, projects;
    Date bDay;
    unsigned int id, currentYear, yearClass;

    ifstream file("C:\\Users\\ruile\\Desktop\\aedaP1\\" + fileName + ".txt");//fileName + ".txt");
    //ifstream file("Students.txt");
    if (!file.is_open())
        throw FileNotFound(fileName);

    //Ignore 1st line - Structure
    getline(file, name);

    while (file.good())
    {
        getline(file, name, ';');
        getline(file, date, ';');
        getline(file, stringID, ';');

        file >> currentYear;
        file.ignore(); //Ignores delimiter ';'
        file >> yearClass;
        file.ignore(); //Ignores the newline '\n'

        bDay = Date(date);
        id = static_cast<unsigned int> (stoi(stringID));
        if (name.size() > MainMenu::maxNameLength)
            MainMenu::maxNameLength = (unsigned int) name.size();

        Person* p = new Student(name, bDay, id, currentYear, yearClass);

        people.push_back(p);
    }

    file.close();
}

void MainMenu::savePeopleFile(const string fileName) const
{
    ofstream file("C:\\Users\\ruile\\Desktop\\aedaP1\\" + fileName + ".txt");//fileName + ".txt");
    //ifstream file("Students.txt");
    if (!file.is_open())
        throw FileNotFound(fileName);

    //Leave 1st line blank - Structure

    vector<Person*>::const_iterator ite;
    for (ite = people.begin(); ite != people.end(); ite++)
    {
        file << "\n" << (*ite)->getName() << ";" << (*ite)->getDateBirth() << ";"
             << (*ite)->getId() << ";" << (*ite)->getCurrentYear() << ";"
             << (*ite)->getClass();
    }

    file.close();
}

void MainMenu::loadThemesFile(string fileName)
{
    string type, score, title, difficulty, description;


    ifstream file("C:\\Users\\ruile\\Desktop\\aedaP1\\" + fileName + ".txt");//fileName + ".txt");

    if (!file.is_open())
        throw FileNotFound(fileName);

    //Ignore 1st line - Structure
    getline(file, type);

    while (file.good())
    {
        getline(file, type, ';'); //Type
        getline(file, title, ';');
        getline(file, difficulty, ';');
        getline(file, description, '\n');


        if (title.size() > MainMenu::maxTitleLength)
            MainMenu::maxTitleLength = static_cast<unsigned int> (title.size());

        Theme t(type, title, description, stoi(difficulty));

        themes.push_back(t);
    }

    file.close();
}

void MainMenu::loadProjects(string fileNames)
{
    Project* project;
    string projectFileName, trash, line = "non-empty", name;
    //All Projects
    string type, dateString, title, body;
    //Research
    string references;
    //Analysis
    string data;


    ifstream filesName("C:\\Users\\ruile\\Desktop\\aedaP1\\" + fileNames + ".txt");//fileName + ".txt");
    if (!filesName.is_open())
        throw FileNotFound(fileNames);


    while (getline(filesName, projectFileName))
    {
        ifstream projectFstream;
        projectFstream.open("C:\\Users\\ruile\\Desktop\\aedaP1\\" + projectFileName + ".txt");
        if (!projectFstream.is_open())
            throw FileNotFound(projectFileName);

        getline(projectFstream, type);
        getline(projectFstream, trash); //Ignore file Information

        getline(projectFstream, dateString);
        getline(projectFstream, trash);
        getline(projectFstream, title);
        getline(projectFstream, trash); //Body tag

        Date date(dateString);
        checkIfMostRecent(title, date.getYear());

        while (getline(projectFstream, line) && line != "")
            body += line + "\n";

        getline(projectFstream, trash);
        normalizeType(type);

        //cout << type << " " << type.size() << endl; Test type length

        if (type == "RESEARCH")
        {
            while (getline(projectFstream, line) && line != "DONE BY")
                references += line + "\n";

            project = new Research(title, dateString, body, references);
        } else if (type == "ANALYSIS")
        {

            while (getline(projectFstream, line) && line != "DONE BY")
                data += line + "\n";

            project = new Analysis(title, dateString, body, data);
        } else
        {
            project = new Development(title, dateString, body); //A year is always positive, we won't be loosing information
        }

        //Loads up group of Students
        while (getline(projectFstream, name, ';'))
        {
            normalizeName(name);
            Person* student = findPersonName(name);
            if (student == nullptr)
                throw InexistingStudent(name);
            else
            {
                string grade;
                project->addStudent(student);//Adds a student to the group
                getline(projectFstream, grade);
                project->addGrade((unsigned int) stoi(grade));
            }
        }


        //Ready next iteration (Reset variables)
        type = "";
        body = "";
        line = "non-empty";
        references = "";
        data = "";

        if (Date().getYear() - project->getYear() <= BSTMAXTIME) //If this project is a recent one (completed at max BSTMAXTIME years), insert it in recentProjects (BST)
            MainMenu::recentProjects.insert(RecentProject(project));
        //else
        //MainMenu::oldProjects.insert(project);

        MainMenu::projects.push_back(project);

        projectFstream.close();
    }
    filesName.close();
}

void MainMenu::loadFiles()
{
    fileNames = {"Students", "ProjectFileNames", "ProjectThemes"};

    try
    {
        loadPeopleFile(fileNames.peopleFile);
        changedPeople = false;
        loadProjects(fileNames.projectsFile);
        loadThemesFile(fileNames.themeIndexFile);
    }
    catch (FileNotFound &fileNFound)
    {
        cout << fileNFound.name;
        waitInput();
    }
    catch (InexistingStudent &inexStudent)
    {
        cout << " The Student '" << inexStudent.name << "' does not exist:";
        waitInput();
    }
}

/*{
    bool fileError;
    unsigned int nTries = NTRIES;


    //People File
    changedPeople = false;
    do
    {
        fileError = false; //Resets the error flag
        cout << "Type the people's file name (extention is not needed)\n";
        getline(cin, fileNames.peopleFile); // Reads the file name
        try
        {
            loadPeopleFile(fileNames.peopleFile);
        }
        catch (FileNotFound fileNF)
        {
            cerr << "File " << fileNF.name << " couldn't be opened.\n";
            fileError = true;
            nTries--;
        }

    } while (fileError && nTries);

    if (!nTries)
        cerr << "Exceeded maximum number of attempts\n";



    //Projects File
    nTries = NTRIES;

    do
    {
        fileError = false; //Resets the error flag
        cout << "Type the projects' file name (extension is not needed)\n";
        getline(cin, fileNames.projectsFile); // Reads the file name
        try
        {
            loadProjects(fileNames.projectsFile);
        }
        catch (FileNotFound fileNF)
        {
            cerr << "File " << fileNF.name << " couldn't be opened.\n";
            fileError = true;
            nTries--;
        }

    } while (fileError && nTries);

    if (!nTries)
        cerr << "Exceeded maximum number of attempts\n";


    //ProjectsIndexer
    nTries = NTRIES;

    do
    {
        fileError = false; //Resets the error flag
        cout << "Type the themes' file name (extension is not needed)\n";
        getline(cin, fileNames.themeIndexFile); // Reads the file name
        try
        {
            loadThemesFile(fileNames.themeIndexFile);
        }
        catch (FileNotFound fileNF)
        {
            cerr << "File " << fileNF.name << " couldn't be opened.\n";
            fileError = true;
            nTries--;
        }

    } while (fileError && nTries);

    if (!nTries)
        cerr << "Exceeded maximum number of attempts\n";


}*/

void MainMenu::setUpAYears()
{
    bool addedFlag;
    for (unsigned int p = 0; p < projects.size(); p++)
    {
        addedFlag = false;
        for (unsigned int a = 0; a < aYears.size(); a++)
        {
            if (projects[p]->getYear() == aYears[a].getYear())
            {
                aYears[a].addProject(projects[p]);
                addedFlag = true;
            }
        }

        if (!addedFlag)//If Academic year when project was done, does't exist
        {
            aYears.push_back(AcademicYear(projects[p]->getYear()));//Create a new Academic Year
            aYears[aYears.size() - 1].addProject(projects[p]);
        }
    }
}


void MainMenu::loadAsciiArt()
{
    ifstream file("C:\\Users\\ruile\\Desktop\\aedaP1\\AsciiArt.txt");

    if (!file.is_open())
        throw FileNotFound("AsciiArt");

    else
    {
        string line, art;
        asciiArt = "";
        while (getline(file, line))
        {
            asciiArt += line;
        }
    }

    file.close();
}

//MainMenu
void MainMenu::menu()
{
    int choice;
    bool exitFlag = false;
    do
    {
        choice = -1;

        system("CLS");
        cout << "Choose an Academic Year\n\n";
        cout << "1. All Years\n";
        cout << "2. Specific Year\n";
        cout << "\n\n0. Exit\n";

        cout << "Your choice: ";

        readOpt(choice);


        switch (choice)
        {
            case 1:
                allYears();
                break;
            case 2:
                try
                {
                    specificYear();
                }
                catch (InexistingAYear &y)
                {
                    cout << "\n\nThe academic year " << y.year << ", does't exist\n\n";
                    waitInput();
                }
                break;
            case 0:
                exitFlag = true;
                break;
            default:
                cout << "The option you typed isn't avaiable\n";
                waitInput();
        }
    } while (!exitFlag);
}

//All Years
void MainMenu::allYears()
{

    int choice;
    bool exitFlag = false;
    do
    {
        choice = -1;
        system("CLS");
        cout << "All Years\n\n";
        cout << "1. Displays\n";
        cout << "2. Manage Themes\n";
        cout << "3. Add Student\n";
        cout << "4. Compatibility Algorithm\n";
        cout << "\n\n0. Go Back\n";

        cout << "Your choice: ";
        readOpt(choice);

        switch (choice)
        {
            case 1:
                generalDisplays();
                break;
            case 2:
                //manageThemes();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                try
                {
                    compactabilityAlgorithm();

                }
                catch (InexistingStudent &invStud)
                {
                    cerr << "\nThe student " << invStud.name << " doesn't exist!\n\n";
                }
                waitInput();
                break;
            case 0:
                exitFlag = true;
                break;
            default:
                cout << "The option you typed isn't available\n";
                waitInput();
        }
    } while (!exitFlag);
}


//Displays
void MainMenu::generalDisplays()
{
    int choice;
    bool exitFlag = false;

    do
    {
        choice = -1;
        system("CLS");
        cout << "Displays\n\n";
        cout << "1. Display all Students\n";
        cout << "2. Display all Projects\n";
        cout << "3. Display all Themes\n";
        cout << "4. Display recent projects of a specific theme";

        cout << "\n\n0. Go Back\n";

        cout << "Your choice: ";
        readOpt(choice);

        switch (choice)
        {
            case 1:
                displayAllStudents();
                waitInput();
                break;
            case 2:
                displayAllProjects();
                break;
            case 3:
                displayThemes();
                waitInput();
                break;
            case 4:
                //displayRecentProjectTheme();
                waitInput();
                break;
            case 0:
                exitFlag = true;
                waitInput();
                break;
            default:
                cout << "The option you typed isn't available\n";
                waitInput();
                break;
        }
    } while (!exitFlag);
}

bool comparePersonPtrAlpha(const Person* pLHS, const Person* pRHS)
{
    return pLHS->getName() < pRHS->getName();
}

void MainMenu::displayAllStudents()
{
    sort(people.begin(), people.end(), comparePersonPtrAlpha); //Sorts people alphabetically
    cout << left << setw(MainMenu::maxNameLength) << "NAME" << "DATA DE NASCIMENTO" << "     ID"
         << "          CURRENT YEAR\n\n";
    for (unsigned int i = 0; i < people.size(); ++i)
    {
        people[i]->print();
    }
}

void MainMenu::displayAllProjects() const
{
    for (unsigned int i = 0; i < projects.size(); ++i)
    {
        system("CLS");
        projects[i]->print();
        waitInput();
    }
}


//Specific Year
void MainMenu::specificYear()
{
    int choice;
    unsigned int year;
    bool exitFlag = false;

    system("CLS");
    cout << "Specific Year\n\n";
    cout << "Type the year you want to consult\n";
    readOpt(year);

    if (!aYearExists(year))
        throw InexistingAYear(year);

    do
    {
        choice = -1;
        system("CLS");
        cout << "Specific Year\n\n";
        cout << "1. Display all Projects from " << year << "\n";
        cout << "\n\n0. Go Back\n";

        cout << "Your choice: ";
        readOpt(choice);

        switch (choice)
        {
            case 1:
                displayProjectsYear(year);
                break;
            case 0:
                exitFlag = true;
                break;
            default:
                cout << "The option you typed isn't avaiable";
        }
    } while (!exitFlag);
}


void MainMenu::displayProjectsYear(const unsigned int year) const
{
    bool foundOne = false;
    for (unsigned int i = 0; i < projects.size(); ++i)
    {
        system("CLS");
        if (projects[i]->getYear() == year)
        {
            foundOne = true;
            projects[i]->print();
            waitInput();
        }
    }

    if (!foundOne)
        cout << "There are no Projects from " << year;
}

void MainMenu::addStudent()
{
    string name, bDay;
    unsigned int id, currentYear, yearClass;
    Date date;
    bool errorFlag;

    cout << "Insert Name: ";
    getline(cin, name);
    normalizeName(name);
    do
    {
        errorFlag = false;
        cout << "Insert Birthday (dd/mm/yyyy): ";
        getline(cin, bDay);
        try
        {
            date = Date(bDay);

        }
        catch (InvalidDate &invDate)
        {
            errorFlag = true;
            cerr << "Invalid date " << invDate.date << endl;

        }
    } while (errorFlag);
    do
    {
        errorFlag = false;
        cout << "Insert ID: ";
        cin >> id;
        //try if id number digits is smaller different than 8 and if the id already exists
        try
        {
            if (numberDigits<unsigned int>(id) != 9)
                throw InvalidID(id);

            if (BinarySearch(people, id) != nullptr)
                throw UsedID(id);

        }
        catch (InvalidID &invID)
        {
            cerr << "The Student ID, must be a 9 digits number\n";
            errorFlag = true;
        }
        catch (UsedID &uID)
        {
            cerr << "There is already a student that possesses that id\n";
            errorFlag = true;
        }
    } while (errorFlag);


    do
    {
        cout << "Insert Current Year: ";
        cin >> currentYear;
    } while (currentYear <= 0 || currentYear > 5);

    cout << "Insert Class: ";
    cin >> yearClass;


    changedPeople = true;
    Person* p = new Student(name, date, id, currentYear, yearClass);
    people.push_back(p);
}


//AUX
Person* MainMenu::findPersonName(const string &name)//Alterar
{
    for (unsigned int i = 0; i < people.size(); i++)
    {
        if (people[i]->getName() == name)
            return people[i];
    }

    return nullptr;
}

bool MainMenu::aYearExists(unsigned int &year)
{
    for (int i = 0; i < aYears.size(); i++)
    {
        if (aYears.at(i).getYear() == year)
            return true;
    }

    return false;
}

void MainMenu::displayThemes() const
{
    cout << "TYPE   TITLE   SCORE   DIFFICULTY\n";

    for (int i = 0; i < themes.size(); i++)
    {
        cout << themes[i] << endl;
    }
}

vector<Person*> MainMenu::projPreviousStudents(Theme &t)
{
    vector<Person*> prevStud;

    for (unsigned int i = 0; i < projects.size(); i++)
    {
        if (projects[i]->getTitle() == t.getTitle())
        {
            for (int j = 0; j < projects[i]->getGroup().size(); ++j)
                prevStud.push_back(projects[i]->getGroup()[j]);

        }
    }

    return prevStud;
}


//Compactability Algorithm
int MainMenu::allPercentage(const vector<Person*> &group) //PROTOTYPE
{

    int compatability;
    for (size_t i = 0; i < themes.size(); i++)
    {
        compatability = PointsRun(themes[i], group); // returns a percentage (0-100) without the '%'
        cout << "\n\n" << "Project " << themes[i].getTitle() << " has " << compatability
             << "% compatability with selected group\n";
    }
}

int MainMenu::PointsRun(Theme &theme, const vector<Person*> &group)
{
    // dificulty --
    // years since last use ++
    // individual student has done it before (bool) ++

    float points = 0;

    int dificulty = theme.difficulty;
    int lastTimeUsed = theme.lastYearUsed;

    // DIFICULTY ADDER

    if (dificulty == 1 || dificulty == 2)
    {
        points += 15;
    } else
    {
        if (dificulty == 3 || dificulty == 4)
        {
            points += 8;
        } else
        {
            if (dificulty == 5 || dificulty == 6)
            {
                points += 0;
            } else
            {
                if (dificulty == 7 || dificulty == 8)
                {
                    points -= 8;
                } else
                {
                    if (dificulty == 9)
                    {
                        points -= 15;
                    } else
                    {
                        if (dificulty == 10)
                        {
                            points -= 20;
                        }
                    }
                }
            }
        }
    }

    // LAST TIME USED ADDER

    int yearSub = lastTimeUsed;

    switch (yearSub)
    {
        case 1:
            points += 30;
            break;
        case 2:
            points += 15;
            break;
        case 3:
            points += 5;
            break;
        case 4:
            points -= 5;
            break;
        case 5:
            points -= 10;
            break;
        default:
            if (yearSub > 5)
            {
                points -= 15;
            }
    }

    // INDIVIDUAL STUDENT ADDER

    vector<Person*> prevStudents = projPreviousStudents(theme);
    for (size_t i = 0; i < prevStudents.size(); i++) // error on class?
    {
        unsigned int focusStudent = prevStudents[i]->getId();
        for (size_t i = 0; i < group.size(); i++)
        {
            if (group[i]->getId() == focusStudent) // have to overload == for students class if not doing with .getId
            {
                points += 30;
            } else
            {
                points += 0;
            }

        }
    }

    return PointsToPercentage(points);
}


int MainMenu::PointsToPercentage(int points)
{
    //takes os pontos e devolve uma percentagem;
    /*

    1 an 30
    2 an 15
    3 an 5
    4 an -5
    5 an -10
    >6 an -15

    dif
    1-2  15
    3-4  8
    5-6  0
    7-8  -8
    9    -15
    10   -20

    aluno rep 30

    examples:

    SUPER BAD
    1 year ago, 1 dif, 2 aluno rep
    30+15+60 105

    BAD
    2 years ago, 3 dif, 1 aluno rep
    15+8+30 53

    MEH
    3 years ago, 5 dif, 1 aluno rep
    5+0+30 35

    OKAY
    3 years ago, 5 dif, 0 aluno rep
    5+0+0 5

    GOOD
    4 years ago, 5 dif, 0 aluno rep
    -5

    */

    int n;

    if (points >= 100)
    {
        return 0;
    } else if (points <= 0)
    {
        return 100;
    } else
    {
        n = 100 - points;
        return n;

    }


    return 0;
}

void MainMenu::checkIfMostRecent(const string &title, const unsigned int year)
{
    for (int i = 0; i < themes.size(); ++i)
    {
        if (themes[i].getTitle() == title)
        {
            if (year > themes[i].lastYearUsed)
                themes[i].lastYearUsed = year;
        }
    }
}

void MainMenu::compactabilityAlgorithm()
{
    vector<Person*> group;
    Person* personPtr;
    string name;
    cout << "Type 5 Student's names\n";
    for (int i = 0; i < 5; ++i)
    {
        cout << "Student: " << i + 1 << endl;
        getline(cin, name);
        normalizeName(name);
        personPtr = findPersonName(name);
        if (personPtr == NULL)
            throw InexistingStudent(name);
        group.push_back(personPtr);
    }

    allPercentage(group);
}

void MainMenu::shutDown()
{
    if (changedPeople)
        savePeopleFile(fileNames.peopleFile);
}





/* INTERFACE PLANS

- START MENU
    - SELECT USER
        - CHECK COMPATABILITY FOR GROUP
            -
        - CHECK COMPATABILITY FOR CLASS (ALL GROUPS)*/