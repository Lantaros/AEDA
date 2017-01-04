#include "Menu.h"
#include <unistd.h>

unsigned int MainMenu::maxNameLength = 0;
unsigned int MainMenu::maxTitleLength = 0;


MainMenu::MainMenu(): recentProjects(RecentProject(nullptr))
{}

void MainMenu::loadPeopleFile(string fileName)
{
    string stringID, name, date, projects;
    Date bDay;
    unsigned int id, currentYear, yearClass;

    ifstream file(fileName + ".txt");//fileName + ".txt");
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

        normalizeName(name);

        if (name.size() > MainMenu::maxNameLength)
            MainMenu::maxNameLength = (unsigned int) name.size();

        Person* p = new Student(name, bDay, id, currentYear, yearClass);

        people.push_back(p);
    }

    file.close();
}

void MainMenu::savePeopleFile(const string fileName) const
{
    ofstream file(fileName + ".txt");//fileName + ".txt");
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


void MainMenu::saveThemesFile(const string filename) const
{

}

void MainMenu::loadThemesFile(string fileName)
{
    string type, score, title, difficulty, description;


    ifstream file(fileName + ".txt");//fileName + ".txt");

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
    bool noGradeFlag;
    //All Projects
    string type, dateString, title, body;
    //Research
    string references;
    //Analysis
    string data;


    ifstream filesName(fileNames + ".txt");//fileName + ".txt");
    if (!filesName.is_open())
        throw FileNotFound(fileNames);


    while (getline(filesName, projectFileName))
    {
        ifstream projectFstream;
        projectFstream.open(projectFileName + ".txt");
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

        noGradeFlag = true;
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

                if (!grade.empty())
                {
                    noGradeFlag = false;
                    project->addGrade((unsigned int) stoi(grade));
                }
            }
        }


        //Ready next iteration (Reset variables)
        type = "";
        body = "";
        line = "non-empty";
        references = "";
        data = "";

        if (noGradeFlag)
            nonGradedProjects.push(NonGradedProject(project));

        else if (Date().getYear() - project->getYear() <= BSTMAXTIME) //If this project is a recent one (completed at max BSTMAXTIME years), insert it in recentProjects (BST)
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
        cout << " The Student '" << inexStudent.name << "' does not exist:\n";
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
    ifstream file("C:\\Users\\Alias\\Desktop\\AEDA\\aedaP1-rui\\AsciiArt.txt");

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
void MainMenu::allYears()
{

    int choice;
    bool exitFlag = false;
    do
    {
        choice = -1;
        system("CLS");

        cout << "    /= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\\ " << "\n";
        cout << "   /= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\\" << "\n";
        cout << "  ||                             Main Menu                         ||" << "\n";
        cout << "  ||                                                               ||" << "\n";
        cout << "  ||                        1. Displays                            ||" << "\n";
        cout << "  ||                        2. Delete Themes                       ||" << "\n";
        cout << "  ||                        3. Add student                         ||" << "\n";
        cout << "  ||                        4. Delete student                      ||" << "\n";
        cout << "  ||                        5. Compatibility Algorithem            ||" << "\n";
        cout << "  ||                        0. Exit                                ||" << "\n";
        cout << "  ||                                                               ||" << "\n";
        cout << "   \\= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =/" << "\n";
        cout << "    \\= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =/" << "\n";

        cout << "           Your choice: ";
        readOpt(choice);

        switch (choice)
        {
            case 1:
                generalDisplays();
                break;
            case 2:
                deleteThemes();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
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

void MainMenu::menu()
{



        cout << " _______  _                 _        _______ _________ _______  ______   _______  _______" << "\n";
        cout << "(  ____ \\( (    /||\\     /|( (    /|(  ____ \\\\__   __/(  ___  )(  __  \\ (  ___  )(  ____ \\"
             << "\n";
        cout << "| (    \\/|  \\  ( || )   ( ||  \\  ( || (    \\/   ) (   | (   ) || (  \\  )| (   ) || (    \\/"
             << "\n";
        cout << "| (__    |   \\ | || |   | ||   \\ | || |         | |   | (___) || |   ) || |   | || (_____" << "\n";
        cout << "|  __)   | (\\ \\) || |   | || (\\ \\) || |         | |   |  ___  || |   | || |   | |(_____  )"
             << "\n";
        cout << "| (      | | \\   || |   | || | \\   || |         | |   | (   ) || |   ) || |   | |      ) |" << "\n";
        cout << "| (____/\\| )  \\  || (___) || )  \\  || (____/\\___) (___| )   ( || (__/  )| (___) |/\\____) |"
             << "\n";
        cout << "(_______/|/    )_)(_______)|/    )_)(_______/\\_______/|/     \\|(______/ (_______)\\_______)" << "\n";

        cout << "                                    ______   _______" << "\n";
        cout << "                                   (  __  \\ (  ____ \\" << "\n";
        cout << "                                   | (  \\  )| (    \\/" << "\n";
        cout << "                                   | |   ) || (__" << "\n";
        cout << "                                   | |   | ||  __)" << "\n";
        cout << "                                   | |   ) || (" << "\n";
        cout << "                                   | (__/  )| (____/\\" << "\n";
        cout << "                                   (______/ (_______/" << "\n";

        cout << "_________ _______  _______  ______   _______  _                 _______  _______ " << "\n";
        cout << "\\__   __/(  ____ )(  ___  )(  ___ \\ (  ___  )( \\      |\\     /|(  ___  )(  ____ \\" << "\n";
        cout << "   ) (   | (    )|| (   ) || (   ) )| (   ) || (      | )   ( || (   ) || (    \\/" << "\n";
        cout << "   | |   | (____)|| (___) || (__/ / | (___) || |      | (___) || |   | || (_____ " << "\n";
        cout << "   | |   |     __)|  ___  ||  __ (  |  ___  || |      |  ___  || |   | |(_____  )" << "\n";
        cout << "   | |   | (\\ (   | (   ) || (  \\ \\ | (   ) || |      | (   ) || |   | |      ) |" << "\n";
        cout << "   | |   | ) \\ \\__| )   ( || )___) )| )   ( || (____/\\| )   ( || (___) |/\\____) |" << "\n";
        cout << "   )_(   |/   \\__/|/     \\||/ \\___/ |/     \\|(_______/|/     \\|(_______)\\_______)" << "\n";

        sleep(2);
        allYears();
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
        cout << "    /= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\\ " << "\n";
        cout << "   /= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\\" << "\n";
        cout << "  ||                             Displays                          ||" << "\n";
        cout << "  ||                                                               ||" << "\n";
        cout << "  ||                1. Display all Students                        ||" << "\n";
        cout << "  ||                2. Display all Themes                          ||" << "\n";
        cout << "  ||                3. Display all Projects                        ||" << "\n";
        cout << "  ||                4. Display Projects from a specific year       ||" << "\n";
        cout << "  ||                5. Display recent projects of a specific theme ||" << "\n";
        cout << "  ||                6. Display recent projects of a specific type  ||" << "\n";
        cout << "  ||                7. Display non-graded projects queue           ||" << "\n";
        cout << "  ||                0. Go back                                     ||" << "\n";
        cout << "  ||                                                               ||" << "\n";
        cout << "   \\= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =/" << "\n";
        cout << "    \\= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =/" << "\n";

        cout << "           Your choice: ";
        readOpt(choice);

        switch (choice)
        {
            case 1:
                displayAllStudents();
                waitInput();
                break;
            case 2:
                displayThemes();
                waitInput();
                break;
            case 3:
                displayAllProjects();
                break;
            case 4:
                displayProjectsYear();
                break;
            case 5:
                displayRecentProjectTheme();
                waitInput();
                break;
            case 6:
                displayRecentProjectType();
                waitInput();
                break;
            case 7:
                displayNonGradedQueue();
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

void MainMenu::displayAllStudentsD()
{
    sort(people.begin(), people.end(), comparePersonPtrAlpha); //Sorts people alphabetically
    cout << "Number      " << left << setw(MainMenu::maxNameLength) << "NAME" << "DATA DE NASCIMENTO" << "     ID"
         << "          CURRENT YEAR\n\n";
    for (unsigned int i = 0; i < people.size(); ++i)
    {
        cout << "  " << left << setw(6) << (i + 1);
        people[i]->print();
    }
}

void MainMenu::displayAllProjects() const
{
    for (unsigned int i = 0; i < projects.size(); ++i)
    {
        system("CLS");
        projects[i]->print();
        cout << "Press 0 or any other key to continue...\n";
        if (cin.get() == '0')
            return;
    }
}

void MainMenu::displayRecentProjectTheme() const
{
    string themeInput;

    cout << "Please type the theme form which the projects you want to see\n";
    getline(cin, themeInput);

    cout << left << setw(MainMenu::maxTitleLength) << "Theme" << setw(10) << " " << "Date of Delivery\n\n";
    BSTItrIn<RecentProject> it(recentProjects);

    while (!it.isAtEnd())
    {
        if (it.retrieve().getPointer()->getTitle() == themeInput)
        {
            cout << left << setw(MainMenu::maxTitleLength) << it.retrieve().getPointer()->getTitle() << setw(10)
                 << " " << it.retrieve().getPointer()->getDate().getDate() << endl;
        }

        it.advance();
    }
}

void MainMenu::displayRecentProjectType() const
{
    string typeInput;
    ProjectType pType;
    cout << "Please insert the type form which the projects you want to see\n";
    getline(cin, typeInput);

    if(typeInput == "Research")
    {
        pType = RESEARCH;

    }
    else if (typeInput == "Analysis"){

        pType = ANALYSIS;
    }
    else if (typeInput == "Development"){

        pType = DEVELOPMENT;
    }
    else
    {
        cerr << "That Type does not exist\n";
        return;
    }
    cout << left << setw(MainMenu::maxTitleLength) << "Type   " << "Title" << setw(10) << " " << "Date of Delivery\n\n";
    BSTItrIn<RecentProject> it(recentProjects);

    while (!it.isAtEnd())
    {
        if (it.retrieve().getPointer()->getType() == pType)
        {
            cout << typeInput << "      "<< left << setw(MainMenu::maxTitleLength) << it.retrieve().getPointer()->getTitle() << setw(10)
                 << " " << it.retrieve().getPointer()->getDate().getDate() << endl;
        }

        it.advance();
    }
}

void MainMenu::displayNonGradedQueue()
{
    priority_queue<NonGradedProject> aux = nonGradedProjects;
    Project* project = nullptr;
    int choice = -1;

    if (nonGradedProjects.empty())
    {
        cout << "There are no projects to grade\n";
        return;
    }
    cout << "Type" << "       " << left << setw(MainMenu::maxTitleLength) << "Theme" << " " << "Date of Delivery\n\n";

    while (!aux.empty())
    {
        project = aux.top().getPointer();

        cout << project->getType() << "     "<< left << setw(MainMenu::maxTitleLength) << project->getTitle() << setw(10)
             << " " << project->getDate().getDate() << endl;

        aux.pop();
    }

    cout << "\nEvaluate most recent project?\n";
    cout << "1. Yes\n" << "2. No\n";

    readOpt(choice);

    if (choice == 1)
    {
        project = nonGradedProjects.top().getPointer();
        evaluateProject(project);
        recentProjects.insert(RecentProject(project));
        nonGradedProjects.pop();
    }
}

unsigned int MainMenu::numberProjectsYear(unsigned int year)
{
    unsigned int counter = 0;
    for (int i = 0; i < projects.size(); ++i)
    {
        if (projects[i]->getYear() == year)
            counter++;
    }
    return counter;
}

void MainMenu::displayProjectsYear()
{
    unsigned int year;
    bool exitFlag = false;

    system("CLS");
    cout << "Specific Year\n\n";
    cout << "Existing years:\n\n";

    for (unsigned int i = 0; i < aYears.size() ; ++i)
    {
        cout << aYears[i].getYear() << " - " << numberProjectsYear(aYears[i].getYear()) << " projects";
        cout << endl;
    }
    cout << "\n(press 0 to back)\nType the year you want to display\n";
    cin >> year;
    cin.ignore();
    if (year == 0)
        return;

    if (!aYearExists(year))
        throw InexistingAYear(year);

    bool foundOne = false;
    for (unsigned int i = 0; i < projects.size(); ++i)
    {
        system("CLS");
        if (projects[i]->getYear() == year)
        {
            foundOne = true;
            projects[i]->print();
            cout << "Press 0 or any other key to continue...\n";
            if (cin.get() == '0')
                return;
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

    cout << "(press 0 to cancel)\nInsert Name: ";
    getline(cin, name);
    normalizeName(name);
    if (name == "0")
        return;
    do
    {
        errorFlag = false;
        cout << "(press 0 to cancel)\nInsert Birthday (dd/mm/yyyy): ";
        getline(cin, bDay);
        if (bDay == "0")
            return;
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
        cout << "(press 0 to cancel)\nInsert ID: ";
        cin >> id;
        if (id == 0)
            return;
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
    cout << "Student ";
    people[people.size()-1]->print();
    cout << "successfully added";
    sleep(3);
}

void MainMenu::deleteStudent()
{
    unsigned int number;
    displayAllStudentsD();
    cout << "\n(press 0 to back\nChoose a student by it's number\n";
    while (1)
    {
        cin >> number;
        if (number == 0)
            return;
        if ((number - 1) <= people.size() && (number - 1) >= 0)
            break;

        cerr << "Invalid number\n";
    }
    cout << "Student ";
    people[number - 1]->print();
    cout << "successfully removed";
    changedPeople = true;
    people.erase(people.begin() + (number - 1));
    sleep(3);
}

void MainMenu::deleteThemes()
{
    unsigned int number;
    displayThemesD();
    cout << "\n(press 0 to back\nChoose a Theme by it's number\n";
    while (1)
    {
        cin >> number;
        if (number == 0)
            return;
        if ((number - 1) <= themes.size() && (number - 1) >= 0)
            break;

        cerr << "Invalid number\n";
    }
    cout << "Theme ";
    cout << themes[number - 1];
    cout << "successfully removed";
    changedThemes = true;
    themes.erase(themes.begin() + (number - 1));
    sleep(3);
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
    cout  << "TYPE   ";
    cout << left << setw(MainMenu::maxTitleLength) << "TITLE" << "    DIFFICULTY\n";

    for (unsigned int i = 0; i < themes.size(); i++)
    {
        cout << themes[i] << endl;
    }
}

void MainMenu::displayThemesD() const
{
    cout << "Number   " << "TYPE   ";
    cout << left << setw(MainMenu::maxTitleLength) << "TITLE" << "    DIFFICULTY\n";

    for (unsigned int i = 0; i < themes.size(); ++i)
    {
        cout << "  " << left << setw(6) << (i + 1);
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
void MainMenu::allPercentage(const vector<Person*> &group) //PROTOTYPE
{
    Project* project;
    string theme;
    string body = "Project to develop";
    string ref = "References";
    string date = Date().getDate();
    int compatability;
    bool themeFlag = false;
    for (size_t i = 0; i < themes.size(); i++)
    {
        compatability = PointsRun(themes[i], group); // returns a percentage (0-100) without the '%'
        cout << "\n\n" << "Project " << themes[i].getTitle() << " has " << compatability
             << "% compatability with selected group\n\n";
    }
    do {
        themeFlag = false;
        cout << "(press 0 to go back)\nWhich Theme would you like to choose?\n";
        getline(cin, theme);
        if (theme == "0")
        return;
        for (int i = 0; i < themes.size(); i++)
        {
            if (theme == themes[i].getTitle())
            {
                if(themes[i].getType() == "R")
                    project = new Research(theme, date, body, ref);
                else if(themes[i].getType() == "A")
                    project = new Analysis(theme, date, body, ref);
                else if(themes[i].getType() == "D")
                    project = new Development(theme, date, body);
                else
                {
                    cerr << "Not a valid type\n";
                    return;
                }
                project->getGroup() = group;
                projects.push_back(project);
                nonGradedProjects.push(NonGradedProject(project));
                themeFlag = true;
            }
        }
        cerr << "That Theme does not exist\n\n";
    }while (!themeFlag);
}

int MainMenu::PointsRun(Theme &theme, const vector<Person*> &group)
{
    // dificulty --
    // years since last use ++
    // individual student has done it before (bool) ++

    float points = 0;

    int dificulty = theme.difficulty;
    int lastTimeUsed = theme.lastYearUsed;

int doneByStudents;

    if (group.size() == 1)
        doneByStudents = 100;

    if (group.size() == 2)
        doneByStudents = 50;

    if (group.size() == 3)
        doneByStudents = 40;

    if (group.size() >= 4)
        doneByStudents = 30;

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
                points += doneByStudents;
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
    displayAllStudents();
    cout << "\n(type 0 to cancel and 1 to finish selection)\nType up to 5 Student's names\n";
    for (int i = 0; i < 5; ++i)
    {
        cout << "Student: " << i + 1 << endl;
        getline(cin, name);
        if (name == "0")
            return;
        if (name == "1")
            break;
        normalizeName(name);
        personPtr = findPersonName(name);
        if (personPtr == NULL)
            throw InexistingStudent(name);
        group.push_back(personPtr);
    }
if (group.size() <= 0)
{
    cerr << "The group has no students\n";
    return;
}
    allPercentage(group);
}

void MainMenu::shutDown()
{
    if (changedPeople)
        savePeopleFile(fileNames.peopleFile);
    if (changedThemes)
        saveThemesFile(fileNames.themeIndexFile);
}









/* INTERFACE PLANS

- START MENU
    - SELECT USER
        - CHECK COMPATABILITY FOR GROUP
            -
        - CHECK COMPATABILITY FOR CLASS (ALL GROUPS)*/