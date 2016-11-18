#include "Menu.h"

//Prototypes
void mainmenu();

/**
 * Main function
 * @return
 */
int main()
{
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
	//mainmenu();
	return 0;


}

void mainmenu()
{
	int choice = 0;

	cout << "Hello Professor, Welcome\n\n\n\n\n\n";
	cout << "What option would you like to choose?\n\n";
	cout << "1: View all Students\n";
	cout << "2: View all Projects\n";
	cout << "3: Add Students\n";
	cout << "4: Add Projects\n";
	cout << "5: Edit Projects\n";
	cout << "6: Remove Students\n";
	cout << "7: Remove Projects\n";
	cout << "8: Choose the best current Project\n";
	cout << "0: Exit Program\n";

	switch (choice)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
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
		return;

	}
}


