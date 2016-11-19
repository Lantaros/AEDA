#include "Menu.h"

//Prototypes

/**
 * Main function
 * @return
 */
int main()
{
    unsigned int choice;
    static MainMenu mainMenu("Hello Professor, Welcome\n\n\n\n\n\n"
                                     "What option would you like to choose?\n\n"
                                     "1: View all Students\n"
                                     "2: View all Projects\n"
                                     "3: Add Students\n"
                                     "4: Add Projects\n"
                                     "5: Edit Projects\n"
                                     "6: Remove Students\n"
                                     "7: Remove Projects\n"
                                     "8: Choose the best current Project\n"
                                     "0: Exit Program\n");

    mainMenu.loadAsciiArt();
    //mainMenu.loadFiles();
    cout << mainMenu.asciiArt;
    /*mainMenu.printOptions();*/


    //Test Forward Declaration
    /* Project * pPoint;
     choice = 2;
     string name = "dada", date = "12/3/2015";
     Date date1(date);

     Student student(name,date1, choice);
     //Person *person = new Student(name,date1, choice);

     student.addProject(pPoint);*/


    switch (choice)
    {
        case 1:
            mainMenu.viewStudents();
            break;
        case 2:
            //mainMenu.viewProjects();
            break;
        case 3:
            mainMenu.addStudent();
            break;
        case 4:
            //menu.addProject();
            break;
        case 5:
            //menu.editProject();
            break;
        case 6:
            //menu.removeStudent();
            break;
        case 7:
            //menu.removeProject();
            break;
        case 8:
            break;
        case 0:
            break;
        default:
            break;


    }
    return 0;
}




