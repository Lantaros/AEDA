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

    //mainMenu.loadAsciiArt();
    mainMenu.loadFiles();
    mainMenu.setUpAYears();

   /* string name = " rui    leixo     ";
    normalizeName(name);
    cout <<name << " " << name.size();
    waitInput();*/
    mainMenu.menu();



    return 0;
}




