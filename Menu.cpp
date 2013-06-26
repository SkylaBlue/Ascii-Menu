#include "Includes.h"

// Global integer to keep track of current menu selection
int g_iMenuIndex;
std::ofstream myFile;

// Structure to hold Item information. Note: We really only use name.
struct gItems
{
	const char *name;
	bool isEnabled;
};
gItems Item[MAX_MENU_ITEMS];

struct gEmployee
{
	std::string first_name;
	std::string last_name;
	int         age;
	int         id_num;
};

/*
 */
int main()
{
	// Wrap our object with our smartptr class
	// this way we don't have to worry about freeing memory
	smartptr<CMenu> Menu = new CMenu;

	SetConsoleTitle("Menu");
	HWND CurWindow;
	Menu->SetNames();

	for(;;)
	{
		CurWindow = FindWindow(0, "Menu");

		Menu->KeyboardInput();
		for(int i=0; i < MAX_MENU_ITEMS; i++)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				std::cout << cyan;
				Menu->VoidEnter(g_iMenuIndex);
				break;
			}

			if (g_iMenuIndex == i)
			{
				std::cout << yellow << "->\t" << yellow << Item[i].name << std::endl;
			}
			
			else
			{
				std::cout << cyan << Item[i].name << std::endl;
			}	
		}
	
		Sleep(141); // Sleep(141);
		ClearScreen();
	}
	
	return 0;
}

// Return to the main menu, without the "Enter" handler thinking we pressed enter on a selection.
void CMenu::ReturnToMenu()
{
	DOUBLE_ENDL;
	std::cout << "Press Enter to return to the main menu...";
	std::cin.ignore().get();
	if(GetAsyncKeyState(VK_RETURN)&1)
	{
		return;
	}
}

/*
The following functions are purely for debugging purposes.
*/
void CMenu::NewEmployee()
{
	std::string first, last;
	int age, id;

	myFile.open("employee.txt", 'w');
	//if(!myFile.good()) std::cout << "Couldn't open employee.txt!"; exit(1);

	ClearScreen();
	//std::cout << "Menu Item One";
	std::cout << "Enter name: ";
	std::cin  >> first;
	std::cout << "Enter last name: ";
	std::cin  >> last;
	std::cout << "Enter age: ";
	std::cin  >> age;
	std::cout << "Enter employee id: ";
	std::cin  >> id;

	gEmployee newEmp = {first, last, age, id };
	smartptr<gEmployee> wr = &newEmp;

	/*
	std::cout << newEmp.first_name << std::endl;
	std::cout << newEmp.last_name  << std::endl;
	std::cout << newEmp.age        << std::endl;
	std::cout << newEmp.id_num     << std::endl;
	*/
	
	myFile << "Testing";
	/*
	myFile << wr->first_name << std::endl;
	myFile << wr->last_name  << std::endl;
	myFile << wr->age        << std::endl;
	myFile << wr->id_num     << std::endl;
	myFile.close();
	*/
	myFile.close();
	this->ReturnToMenu();
	ClearScreen();
}

void CMenu::Two()
{
	ClearScreen();
	/*
	newEmp->first_name = "Bob";
	newEmp->last_name  = "Jones";
	newEmp->age        = 32;
	newEmp->id_num     = 123456;

	printf("First Name: %s\n"
		   "Last  Name: %s\n"
		   "Age: %i\n"
		   "Employee ID: %i", newEmp->first_name, newEmp->last_name, newEmp->age, newEmp->id_num);
	*/
	this->ReturnToMenu();
	ClearScreen();
}

void CMenu::Three()
{
	ClearScreen();
	std::cout << "Menu Item Three";
	this->ReturnToMenu();
	ClearScreen();
}

void CMenu::Four()
{
	ClearScreen();
	std::cout << "Menu Item Four";
	this->ReturnToMenu();
	ClearScreen();
}
/**********************
End debugging functions
**********************/

// Handle Up and Down Keyboard events
void CMenu::KeyboardInput()
{
	// User pressed up arrow
	if(GetAsyncKeyState(VK_UP)&1)
	 {
		if(g_iMenuIndex > 0)
		 {
			g_iMenuIndex--;
		 }

		// Don't allow the user to go above the first item
		else
		{
			g_iMenuIndex = 0;
		}
	 }
	 
	 // User pressed down arrow
	 if(GetAsyncKeyState(VK_DOWN)&1)
	  {
		  if(g_iMenuIndex < 6)
		  {
			 g_iMenuIndex++;
		  }

		 // Don't allow the user to go below the last item
		 else
		 {
			g_iMenuIndex = 6;
		 }
	  }
}

// Handle Menu selection
void CMenu::VoidEnter(int c)
{
	switch(c)
	{
		case 0:
			NewEmployee();
			break;
		case 1:
			Two();
			break;
		case 2:
			Three();
			break;
		case 3:
			Four();
			break;
		case 6:
			exit(1);
		default:
			break;
	}
}

//Initialise Menu Items
void CMenu::SetNames()
{
    Item[0].name = "New Employee";
    Item[1].name = "Edit Employee";  
    Item[2].name = "Remove Employee";
	Item[3].name = "View All Employees";
	Item[4].name = "Generate Employee ID";
	Item[5].name = "Change Password";
	Item[6].name = "Logout";
}



	
