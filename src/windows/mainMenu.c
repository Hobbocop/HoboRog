#include "rog.h"
#include "mainMenu.h"


void closeMenu(int numberItems, MENU* menu, ITEM** items)
{
	int i;

	//Clean up menu and pointers
	unpost_menu(menu);
	free_menu(menu);

	for(i=0; i<numberItems; i++)
	{
		free_item(items[i]);
	}
}

int mainMenu(int numberItems, char * choices[])
{
	int i;
	int value;
	int c;

	MENU* menu;
	ITEM** items = malloc(sizeof(**items)*numberItems+1);
	ITEM* current;

	for(i=0; i<numberItems; i++)
	{
		items[i] = new_item(choices[i], "");
	}

	items[numberItems] = (ITEM*) NULL;

	menu = new_menu((ITEM**)items);

	post_menu(menu);
	refresh();

	//Menu Loop
	while(true)
	{
		c=getch();
		switch(c)
		{
			case KEY_DOWN:
				menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case 10:
				current = current_item(menu);
				value = item_index(current);
				closeMenu(numberItems, menu, items);
				return value;

		}
	}
}
