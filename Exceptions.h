#ifndef THEMES_EXCEPTIONS_H
#define THEMES_EXCEPTIONS_H

#include <string>

using namespace std;

//Person
class InexistingStudent
{
public:
    InexistingStudent(string name)//, unsigned int id)
    {
        this->name = name;
        // this->id = id;
    }

    string name;
    //unsigned int id;
};

class ExistingStudent
{
public:
    ExistingStudent(string name, unsigned int id)
    {
        this->name = name;
        this->id = id;
    }

    string name;
    unsigned int id;
};
//Project

//Date
class InvalidDate
{
public:
    InvalidDate(string date)
    { this->date = date; }

    string date;

    string getDate() const
    { return date; }
};

//Misc
class InvalidID
{
public:
    InvalidID(unsigned int id)
    { number = id; }

    unsigned int getNumber() const
    { return number; }

    unsigned int number;

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


#endif //THEMES_EXCEPTIONS_H
