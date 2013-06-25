#include "Includes.h"
#include "Menu.h"
#include "SmartPtr.h"

// Global integer to keep track of current menu selection
int g_iMenuIndex;


// Structure to hold Item information. Note: We really only use name.
struct gItems
{
	const char *name;
	bool isEnabled;
};
gItems Item[MAX_MENU_ITEMS];

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
				Menu->VoidEnter(g_iMenuIndex);
					break;
			}

			if (g_iMenuIndex == i)
			{
				std::cout << "->\t\t" << yellow << Item[i].name << std::endl;
			}
			
			else
			{
				std::cout << "\t" << cyan << Item[i].name << std::endl;
			}	
		}
	
		Sleep(141);
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
void CMenu::ChangeName()
{
	std::string name;
	ClearScreen();
	//std::cout << "Menu Item One";
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cout << "Name is: " << name;
	this->ReturnToMenu();
	ClearScreen();
}

void CMenu::Two()
{
	ClearScreen();
	std::cout << "Menu Item Two";
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
		 if(g_iMenuIndex < 2)
		  {
			 g_iMenuIndex++;
		  }

		 // Don't allow the user to go below the last item
		 else
		 {
			g_iMenuIndex=3;
		 }
	  }
}

// Handle Menu selection
void CMenu::VoidEnter(int c)
{
	switch(c)
	{
		case 0:
			ChangeName();
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
		default:
			break;
	}
}

//Initialise Menu Items
void CMenu::SetNames()
{
        Item[0].name = "Change Name";
        Item[1].name = "Two";  
        Item[2].name = "Three";
		Item[3].name = "Four";
}
