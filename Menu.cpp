#include "Menu.h"

unsigned int Menu::maxNameLength = 0;

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

unsigned int Menu::getMaxNameLength()
{
	return maxNameLength;
}

void MainMenu::loadPeopleFile(string fileName)
{
    string stringID, name, date, projects;
	Date bDay;
    unsigned int id, currentYear, yearClass;
    istringstream iss;

	ifstream file("C:\\Users\\ruile\\Desktop\\aedaP1\\"+ fileName + ".txt");//fileName + ".txt");
    //ifstream file(fileName + ".txt");
	if (!file.is_open())
		throw FileNotFound(fileName);

    //Ignore 1st line - Structure
    getline(file,name);

	while (file.good())
	{
		getline(file, name, ';');
        //file.ignore(); //ignores the blank space after the ';'
		getline(file, date, ';');
        //file.ignore();
		getline(file, stringID);

        file >> currentYear;
        file >> yearClass;

        //Projects
        getline(file, projects, '\n');
        iss.str(projects);

/*        while(!iss.eof())
        {

        }*/

		bDay = Date(date);
		id = stoi(stringID);

        Person *p = new Student(name, bDay, id, currentYear, yearClass);

		people.push_back(p);
	}

}

void MainMenu::loadFiles()
{
    FileNames fileNames;

    bool fileError;
    unsigned int nTries = NTRIES;


    //People File
    do
    {
        fileError = false; //Resets the error flag
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
