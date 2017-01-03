#include "Project.h"
#include "Menu.h"

//Project

Project::Project(string &title, string &date, string &body, ProjectType type)
{
    Project::title = title;
    Project::date = Date(date);
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
    return date.getYear();
}

Date Project::getDate() const
{
    return date;
}

ProjectType Project::getType() const
{
    return type;
}

vector<Person*> &Project::getGroup()
{
    return group;
}

vector<Person*> Project::getGroupConst() const
{
    return group;
}

vector<unsigned int> Project::getGrades()
{
    return grades;
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

void Project::addGrade(unsigned int grade)
{
    grades.push_back(grade);
}

bool Project::operator==(const Project &pRHS) const
{
    return title == pRHS.title;
}


/*-------------Research-------------------*/
Research::Research(string &title, string &date, string &body, string &references): Project(title, date, body,
                                                                                           ProjectType::RESEARCH)
{ this->references = references; }

void Research::print() const
{
    cout << this->getTitle() << "\n" << date.getDate() << "\n" << this->body << "\n\nReferences\n\n" << references
         << "\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout << "\n" << *group[i];
    }
    cout << endl;
}


//Analysis
Analysis::Analysis(string &title, string &date, string &body, string &dataRepositoryFile): Project(title, date,
                                                                                                   body,
                                                                                                   ProjectType::ANALYSIS)
{ this->dataRepositoryFile = dataRepositoryFile; }


void Analysis::print() const
{
    cout << this->getTitle() << "\n" << date.getDate() << "\n" << this->body << "\n\nData Repository\n\n" << dataRepositoryFile
         << "\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout << "\n" << *group[i];
    }
    cout << "\n";
}


//Development
Development::Development(string &title, string &date, string &body): Project(title, date, body,
                                                                             ProjectType::DEVELOPMENT)
{ this->body = body; }

void Development::print() const
{
    cout << this->getTitle() << "\n" << date.getDate() << "\n\nCode\n\n" << this->body << "\n\n Done By\n";
    for (unsigned int i = 0; i < group.size(); i++)
    {
        cout << "\n" << *group[i];
    }
    cout << "\n";
}

/*-------------------BST-----------------------------*/
RecentProject::RecentProject(Project* pointer): projectPtr(pointer)
{}

Project* RecentProject::getPointer() const
{
    return projectPtr;
}

void RecentProject::setPointer(Project* pointer)
{
    projectPtr = pointer;
}

bool RecentProject::operator<(const RecentProject &rRHS) const
{
    if (projectPtr->getDate() == rRHS.projectPtr->getDate())
    {
        if (projectPtr->getType() == rRHS.projectPtr->getType())
        {
            return projectPtr->getTitle() < rRHS.projectPtr->getTitle();
        } else
            return projectPtr->getType() < rRHS.projectPtr->getType();
    } else
        return projectPtr->getDate() > rRHS.projectPtr->getDate();
}

bool RecentProject::operator==(const RecentProject &rRHS) const
{
    return this->projectPtr->getTitle() == rRHS.projectPtr->getTitle() &&
           this->projectPtr->getType() == rRHS.projectPtr->getType()
           && this->projectPtr->getDate() == rRHS.projectPtr->getDate();
}

//---------------------PRIORITY-QUEUE---------------------------------

NonGradedProject::NonGradedProject(Project* pointer)
{
    NonGradedProject::projectPtr = pointer;
}

Project* NonGradedProject::getPointer() const
{
    return projectPtr;
}

bool NonGradedProject::operator<(const NonGradedProject &rRHS) const
{
    if (projectPtr->getDate() == rRHS.projectPtr->getDate())
    {
        return projectPtr->getTitle() > rRHS.projectPtr->getTitle();
    } else
        return projectPtr->getDate() < rRHS.projectPtr->getDate();
}

void evaluateProject(Project* project)
{
    if (project == nullptr)
        return;

    while (project->getGrades().size() != project->getGroupConst().size())
        project->addGrade(static_cast<unsigned int> (rand() % 21));
}