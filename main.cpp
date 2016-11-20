#include "Menu.h"

//Prototypes


static MainMenu mainMenu;


/**
 * Main function
 * @return
 */
int main()
{
    unsigned int choice = 0;

    mainMenu.loadAsciiArt();
    mainMenu.loadFiles();
    mainMenu.setUpAYears();

    //Test Forward Declaration
    /* Project * pPoint;
     choice = 2;
     string name = "dada", date = "12/3/2015";
     Date date1(date);

     Student student(name,date1, choice);
     //Person *person = new Student(name,date1, choice);

     student.addProject(pPoint);*/



    return 0;
}




