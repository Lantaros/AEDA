#include "Menu.h"

unsigned int Menu::maxNameLength = 0;

Menu::Menu()
{
}


Menu::~Menu()
{
}

unsigned int Menu::getMaxNameLength()
{
	return maxNameLength;
}

void Menu::loadPeopleFile(string fileName)
{
	string stringID, name, date;
	Date bDay;
	unsigned int id;

	ifstream file("C:\\Users\\ruile\\Desktop\\aedaP1\\"+ fileName + ".txt");//fileName + ".txt");
    //ifstream file(fileName + ".txt");
	if (!file.is_open())
		throw FileNotFound(fileName);

    //Ignore 1st line - Structure
    getline(file,name);

	while (file.good())
	{
		getline(file, name, ';');
		file.ignore(); //ignores the blank space after the ';'
		getline(file, date, ';');
		file.ignore();
		getline(file, stringID);

		bDay = Date(date);
		id = stoi(stringID);

		Person * p = new Student(name, bDay, id);

		people.push_back(p);
	}

}
