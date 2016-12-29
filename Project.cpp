#include "Project.h"
#include "Menu.h"

//Project

Project::Project(string &title, unsigned int year, string &body, ProjectType type)
{
    Project::title = title;
    Project::year = year;
    Project::body = body;
    Project::type = type;
}

//Get's

string Project::getTitle() const
{
    return title;
}


string Project::getBody() const
{
    return body;
}

unsigned int Project::getYear() const
{
    return year;
}

ProjectType Project::getType() const
{
    return type;
}

vector<Person*> &Project::getGroup()
{
    return group;
}

//Other methods
void Project::addStudent(Person* s)
{
    for (unsigned int i = 0; i < group.size(); i++)
    {
        if ((*group[i]) == (*s))
            throw ExistingStudent(s->getName(), s->getId());
    }

    group.push_back(s);
}

bool Project::operator==(const Project &pRHS) const
{
    return title == pRHS.title;
}


/*-------------Research-------------------*/
Research::Research(string &title, unsigned int year, string &body, string &references): Project(title, year, body,
                                                                                                ProjectType::RESEARCH)
{ this->references = references; }

void Research::print() const
{
    cout << this->getTitle() << "\n" << year << "\n" << this->body << "\n\nReferences\n\n" << references
         << "\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout << "\n" << *group[i];
    }
    cout << endl;
}


//Analysis
Analysis::Analysis(string &title, unsigned int year, string &body, string &dataRepositoryFile): Project(title, year,
                                                                                                        body,
                                                                                                        ProjectType::ANALYSIS)
{ this->dataRepositoryFile = dataRepositoryFile; }


void Analysis::print() const
{
    cout << this->getTitle() << "\n" << year << "\n" << this->body << "\n\nData Repository\n\n" << dataRepositoryFile
         << "\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout << "\n" << *group[i];
    }
    cout << "\n";
}


//Development
Development::Development(string &title, unsigned int year, string &body): Project(title, year, body,
                                                                                  ProjectType::DEVELOPMENT)
{ this->body = body; }

void Development::print() const
{
    cout << this->getTitle() << "\n" << year << "\n\nCode\n\n" << this->body << "\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout << "\n" << *group[i];
    }
    cout << "\n";
}

/*-------------------BST-----------------------------*/
RecentProject::RecentProject(Project* pointer): projectPtr(pointer)
{}

Project* RecentProject::getPointer()
{
    return projectPtr;
}

void RecentProject::setPointer(Project* pointer)
{
    projectPtr = pointer;
}

bool RecentProject::operator<(const RecentProject &rRHS) const
{
    if (projectPtr->getYear() == rRHS.projectPtr->getYear())
    {
        if (projectPtr->getType() == rRHS.projectPtr->getType())
        {
            return projectPtr->getTitle() < rRHS.projectPtr->getTitle();
        } else
            return projectPtr->getType() < rRHS.projectPtr->getType();
    } else
        return projectPtr->getYear() < rRHS.projectPtr->getYear();
}

bool RecentProject::operator==(const RecentProject &rRHS) const
{
    return this->projectPtr->getTitle() == rRHS.projectPtr->getTitle() &&
           this->projectPtr->getType() == rRHS.projectPtr->getType()
           && this->projectPtr->getYear() == rRHS.projectPtr->getYear();
}
