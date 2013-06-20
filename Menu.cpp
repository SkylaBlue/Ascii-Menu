#include <iostream>
#include <string>
#include "Colors.h"

#define MAX_MENU_ITEMS 4
#define NAME 0 
#define COLOR 1
#define ITEM 2
#define MENU 3

int MenuIndex = 0;

# Menu Items
struct Items
{
  const char *name;
	bool Enabled;
};

Items item[MAX_MENU_ITEMS];

void clearScreen(int pos)
{
    HANDLE hOut;
    COORD Position;
 
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
 
    Position.X = 0;
    Position.Y = pos;
    SetConsoleCursorPosition(hOut, Position);
}

# Move to a different menu item
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
		item[MenuIndex].Enabled = !item[MenuIndex].Enabled; 
	 }
			

}

# Initialise our Menu
void SetNames()
{
        item[NAME].name = "Change Name";
        item[COLOR].name = "Single Chat";  
        item[ITEM].name = "Global Chat ";
        item[MENU].name = "Status spam";
}

int main()
{
	SetConsoleTitle("Menu");
	HWND CurWindow;
	SetNames();
	
	for(;;(Sleep(1)))
	{
		
    # We need to make sure it only accepts Enter when we have this window in the foreground
		CurWindow = FindWindow(0, "Menu");
		if (GetForegroundWindow() == CurWindow && GetAsyncKeyState(VK_RETURN))
		{
		    switch(MenuIndex)
			 {
				default: 
					break;
		     }
		 }
				 
		KeyboardInput();
		for(int i=0; i < MAX_MENU_ITEMS; i++)
		{
			if (MenuIndex == i)
			{
				std::cout << "->            " << yellow << item[i].name << std::endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				std::cout << "        " << item[i].name << std::endl;
			}
		}
	
		system("CLS");
	}

		return 0;
}
