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

    mainMenu.menu();



    return 0;
}




