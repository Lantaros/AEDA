#include "Menu.h"

//Prototypes

/**
 * Main function
 * @return
 */
int main()
{
    unsigned int choice;
    MainMenu menu("Hello Professor, Welcome\n\n\n\n\n\n"
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

    menu.loadAsciiArt();
    menu.loadFiles();
    cout << menu.asciiArt;
    menu.printOptions();


    switch (choice)
    {
        case 1:
            menu.viewStudents();
            break;
        case 2:
            menu.viewProjects();
            break;
        case 3:
            menu.addStudent();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 0:
            break;


    }
    return 0;
}



