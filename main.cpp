#include "Menu.h"

//Prototypes


static MainMenu mainMenu;


/**
 * Main function
 * @return An Integer is returned, evaluating error that can occur,
 * on a working state return 0
 */
int main()
{
    unsigned int choice = 0;

    //mainMenu.loadAsciiArt();
    mainMenu.loadFiles();
    mainMenu.setUpAYears();


    mainMenu.menu();

    //Save if needed
    mainMenu.shutDown();
    return 0;
}