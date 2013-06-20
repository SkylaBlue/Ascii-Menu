#include <iostream>
#include <string>
#include "Colors.h"
#include "ClearScreen.h"

#define MAX_MENU_ITEMS 4
#define NAME 0 
#define COLOR 1
#define ITEM 2
#define MENU 3

int MenuIndex = 0;



void test()
{
	std::string name;
	std::cout << "Enter your name: ";
	std::cin.ignore();
	getline(std::cin, name);
	std::cout << "Name is now: " << name << std::endl;
	getchar();
}

void Hello()
{
	std::cout << "Hello World!";
	getchar();
}

// Menu Items
struct Items
{
    const char *name;
	bool Enabled;
};

Items item[MAX_MENU_ITEMS];

// Move to a different menu item
void KeyboardInput()
 { 
	if(GetAsyncKeyState(VK_UP)&1)
	 {
		if(MenuIndex > 0)
		 {
			MenuIndex--;
		 }

		// Don't allow the user to go above the first item
		else
		{
			MenuIndex = 0;
		}
	 }

	 if(GetAsyncKeyState(VK_DOWN)&1)
	  {
		 if(MenuIndex < 2)
		  {
			 MenuIndex++;
		  }

		 // Don't allow the user to go below the last item
		 else
		 {
			 MenuIndex=3;
		 }
	  }


	if(GetAsyncKeyState(VK_END)&1)
	 {
		item[MenuIndex].Enabled = false; 
	 }
	
}

void Enter(int c)
{
	switch(c)
	{
		case 0:
			ClearScreen();
			test();
			ClearScreen();
			break;
		case 1:
			ClearScreen();
			Hello();
			ClearScreen();
			break;
		default:
			break;
	}
}
// Initialise our Menu
void SetNames()
{
        item[0].name = "Change Name";
        item[1].name = "Single Chat";  
        item[2].name = "Global Chat ";
        item[3].name = "Status spam";
}


int main()
{
	SetConsoleTitle("Menu");
	HWND CurWindow;
	SetNames();
	
	for(;;)
	{
        // We need to make sure it only accepts Enter when we have this window in the foreground
	    CurWindow = FindWindow(0, "Menu");

		KeyboardInput();
		for(int i=0; i < MAX_MENU_ITEMS; i++)
		{
			if (GetAsyncKeyState(VK_RETURN)&1 && item[i].Enabled == true)
			{
					Enter(i);
			}

			if (MenuIndex == i)
			{
				item[i].Enabled = true;
				std::cout << "->\t\t" << yellow << item[i].name << std::endl;
			}
			
			else
			{
				item[i].Enabled = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				std::cout << "\t" << item[i].name << std::endl;
			}	
		}
	
		Sleep(141);
		ClearScreen();
	}

		return 0;
}
