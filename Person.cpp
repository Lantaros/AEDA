#include "Person.h"
#include "Menu.h"


//Person

/**
*
*
*/
Person::Person(const string &name, const Date &birthDate) : name(name), birthDate(birthDate)
{}


Person::Person(string &name, Date &birthDate) : name(name), birthDate(birthDate)
{}

string Person::getName() const
{
    return name;
}

unsigned int Person::getAge() const
{
    Date today;
    return birthDate.getYear() - today.getYear();
}




//Student

Student::Student(const string &name, const Date &birthDate, const unsigned int &id, const unsigned int &currentYear,
                 const unsigned int &yearClass) : Person(name, birthDate), id(id)
{
    this->currentYear = currentYear;
    this->yearClass = yearClass;
}

Student::Student(string &name, Date &birthDate, unsigned int &id) : Person(name, birthDate), id(0)
{}


Student::~Student()
{
}

unsigned int Student::getCurentYear() const
{
    return currentYear;
}


ostream &Student::operator<<(ostream &out)
{
    out << left << setw(Menu::maxNameLength) << name << birthDate.getDate() << "   " << id << "          "
        << currentYear;

    return out;

}

void Student::print() const
{
    cout << left << setw(Menu::maxNameLength) << name << birthDate.getDate() << "   " << id << "          "
         << currentYear;
}

void Student::addProject(const Project *project)
{
    for (unsigned int i = 0; i < projects.size(); i++)
    {
        if (*project == (*projects.at(i)))
        {
            cerr << "That project already exists in " << this->name << "'s portfolio\n";
            return;
        }
        projects.push_back(project);

    }
}



//Professor

    void Professor::print() const
    {
        cout << name << birthDate.getDate() << id;
    }

    ostream &Professor::operator<<(ostream &out)
    {
        out << name << birthDate.getDate() << id;

        return out;
    }
