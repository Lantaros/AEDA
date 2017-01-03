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

    /*string name = "Joaquim da Silva";
    normalizeName(name);*/
    mainMenu.loadFiles();
    mainMenu.setUpAYears();

    /*  if(Date("13/02/2019") < Date("1/1/2014"))
          cout << "TRUE";
      else
          cout <<"False";*/

    mainMenu.menu();

    //Save if needed
    mainMenu.shutDown();
    return 0;
}