#include "Person.h"
#include "Date.h"
#include "Form.h"

//Prototypes
void mainmenu();



int main()
{
	vector<Person *> people;
	vector<Form *> subjects;
	mainmenu();
	return 0;


}

void mainmenu()
{
	int choice;

	cout << "Hello Professor, Welcome\n\n\n\n\n\n";
	cout << "What option would you like to choose?\n\n";
	cout << "1: View all Students\n";
	cout << "2: View all Projects\n";
	cout << "3: Add Students\n";
	cout << "4: Add Projects\n";
	cout << "5: Edit Students\n";
	cout << "6: Edit Projects\n";
	cout << "7: Remove Students\n";
	cout << "8: Remove Projects\n";
	cout << "9: Choose the best current Project\n";
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
	case 9:
		break;
	case 0:
		return;

	}
}
