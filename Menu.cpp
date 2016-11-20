#include "Menu.h"

unsigned int Menu::maxNameLength = 0;
unsigned int Menu::maxTitleLength = 0;

Menu::Menu()
{}


Menu::~Menu()
{}

Menu::Menu(string displays)
{ displayOptions = displays; }

void Menu::printOptions() const
{
    cout << displayOptions;
}

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

        Person *p = new Student(name, bDay, id, currentYear, yearClass);

        people.push_back(p);
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
        getline(file, score, ';');
        getline(file, title, ';');
        getline(file, difficulty, ';');
        getline(file, description, '\n');


        if (title.size() > Menu::maxTitleLength)
            Menu::maxTitleLength = static_cast<unsigned int> (title.size());

        Theme t(type, title, description, stoi(score), stoi(difficulty));

        themes.push_back(t);
        /*if(type == "R")
        {
            t =
        }
        else
            if(type == "A")
            {

            }
        else
            if(type == "D")
            {

            }*/

    }

    file.close();
}

void MainMenu::loadProjects(string fileNames)
{
    Project *project;
    string projectFileName, trash, line = "non-empty", name;
    //All Projects
    string type, year, title, body;
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
        getline(projectFstream, year);
        getline(projectFstream, trash);
        getline(projectFstream, title);
        getline(projectFstream, trash); //Body tag


        while (getline(projectFstream, line) && line != "")
            body += line + "\n";

        getline(projectFstream, trash);
        normalizeType(type);
        cout << type << endl;
        if (type == "RESEARCH")
        {
            while (getline(projectFstream, line) && line != "DONE BY")
                references += line + "\n";

            project = new Research(title, stoi(year), body, references);
        }
        else
        {
            if (type == "ANALYSIS")
            {
                while (getline(projectFstream, line) && line != "DONE BY")
                    data += line + "\n";

                project = new Analysis(title, stoi(year), body, data);
            }
            else
            {
                project = new Development(title, stoi(year),
                                          body); //A year is always posiive, we won't be loosing information
                //getline(projectFstream, trash); //Gets rid of "DONE BY"
            }
        }


        //Loads up group of Students
        while (getline(projectFstream, name))
        {
            normalizeName(name);
            Person *student = findPersonName(name);
            if (student == nullptr)
                throw InexistingStudent(name);
            else
                project->addStudent(student);//Adds a student to the group
        }


        //Ready next iteration (Reset variables)
        type = "";
        body = "";
        line = "non-empty";
        references = "";
        data = "";

        MainMenu::projects.push_back(project);

        projectFstream.close();
    }
    filesName.close();
}

void MainMenu::loadFiles()
{
    FileNames fileNames = {"Students", "ProjectFileNames", "ProjectThemes"};

    try
    {
        loadPeopleFile(fileNames.peopleFile);
        loadProjects(fileNames.projectsFile);
        loadThemesFile(fileNames.themeIndexFile);
    }
    catch (FileNotFound &fileNFound)
    {
        cout << fileNFound.name;
    }
    catch (InexistingStudent &inexStudent)
    {
        cout << inexStudent.name;
    }
}

/*{
    FileNames fileNames;

    bool fileError;
    unsigned int nTries = NTRIES;


    //People File
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
        cerr << "Excceded maximum number of atempts\n";



    //Projects File
    nTries = NTRIES;

    do
    {
        fileError = false; //Resets the error flag
        getline(cin, fileNames.projectsFile); // Reads the file name
        try
        {
            loadPeopleFile(fileNames.projectsFile);
        }
        catch (FileNotFound fileNF)
        {
            cerr << "File " << fileNF.name << " couldn't be opened.\n";
            fileError = true;
            nTries--;
        }

    } while (fileError && nTries);

    if (!nTries)
        cerr << "Excceded maximum number of atempts\n";


    //ProjectsIndexer
    nTries = NTRIES;

    do
    {
        fileError = false; //Resets the error flag
        cout << "Type the people's file name (extention is not needed)\n";
        getline(cin, fileNames.themeIndexFile); // Reads the file name
        try
        {
            loadPeopleFile(fileNames.themeIndexFile);
        }
        catch (FileNotFound fileNF)
        {
            cerr << "File " << fileNF.name << " couldn't be opened.\n";
            fileError = true;
            nTries--;
        }

    } while (fileError && nTries);

    if (!nTries)
        cerr << "Excceded maximum number of atempts\n";


}*/

Person *MainMenu::findPersonName(const string &name)//Alterar
{
    for (unsigned int i = 0; i < people.size(); i++)
    {
        if (people[i]->getName() == name)
            return people[i];
    }

    return nullptr;
}


MainMenu::MainMenu(string displays) : Menu(displays)
{}

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

void MainMenu::viewStudents() const
{
    cout << left << setw(Menu::maxNameLength) << "NAME" << "DATA DE NASCIMENTO" << "       ID/n"
         << "          CURRENT YEAR";
    for (unsigned int i = 0; i < people.size(); ++i)
    {
        cout << people[i];
    }
}

void MainMenu::viewProjects() const
{
    cout << "TYPE          " << "SCORE    " << "DIFFICULTY    " << left << setw(Menu::maxTitleLength) << "TITLE"
         << "DESCRIPTION/n";
    for (unsigned int i = 0; i < projects.size(); ++i)
    {
        cout << projects[i];
    }
}

void MainMenu::addStudent()
{
    string name, bDay;
    unsigned int id, currentYear, yearClass;
    Date date;
    bool errorFlag;

    cout << "Insert Name: ";
    getline(cin, name);
    do
    {
        errorFlag = false;
        cout << "Insert Birthday (dd/mm/yyyy): ";
        cin >> bDay;
        try
        {
            date = Date(bDay);
        }
        catch (InvalidDate &invDate)
        {
            cerr << "Invalid date " << invDate.date << endl;
        }
    } while (errorFlag);
    do
    {
        cout << "Insert ID: ";
        cin >> id;
        //try if id number digits is smaller different than 8 and if the id already exists
        try
        {
            if (numberDigits<unsigned int>(id) != 8)
                throw InvalidID(id);
        }
        catch (InvalidID &invID)
        {
            cerr << "The Student ID, must be a 8 digits number";
        }
    } while (errorFlag);
    cout << "Insert Current Year: ";
    cin >> currentYear;
    cout << "Insert Class: ";
    cin >> yearClass;


    Person *p = new Student(name, date, id, currentYear, yearClass);
    people.push_back(p);
}


