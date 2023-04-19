#include "title.h"
#include <ncurses.h>
#include <unistd.h>

const char* title[5] = {" ▄▄▄·      • ▌ ▄ ·.         ▄▄▄▄▄▪  • ▌ ▄ ·. ▄▄▄ .▄▄▄  ", 
		        "▐█ ▄█ ▄█▀▄ ·██ ▐███▪ ▄█▀▄   •██  ██ ·██ ▐███▪▀▄.▀·▀▄ █·", 
		        " ██▀·▐█▌.▐▌▐█ ▌▐▌▐█·▐█▌.▐▌   ▐█.▪▐█·▐█ ▌▐▌▐█·▐▀▀▪▄▐▀▀▄ ",
		        "▐█▪·•▐█▌.▐▌██ ██▌▐█▌▐█▌.▐▌   ▐█▌·▐█▌██ ██▌▐█▌▐█▄▄▌▐█•█▌", 
		        ".▀    ▀█▄▀▪▀▀  █▪▀▀▀ ▀█▄▀▪   ▀▀▀ ▀▀▀▀▀  █▪▀▀▀ ▀▀▀ .▀  ▀"};


void* title_animation()
{
	WINDOW* title_win = newwin(6, 60, (LINES / 2) - 5,(COLS / 2) - 30);
	int x_pos = 2;

	while (1) 
	{
		for(int i = 0; i < 4; i++)
		{
			wclear(title_win);

			//draw title
			for(int j = 0; j < 5; j++)
			{
				if((i == 1) && (j % 2)) //if i==1 and j is odd
				{
					mvwprintw(title_win, j, x_pos + 1, "%s",title[j]);
				}
				else if((i == 3) && ~(j % 2)) //if i==3 and j is even
				{
					mvwprintw(title_win, j, x_pos - 1, "%s",title[j]);
				}
				else
				{
					mvwprintw(title_win, j, x_pos, "%s",title[j]);
				}
			}


			//refresh window and sleep
			wrefresh(title_win);
			if(i > 0)
			{
				usleep(100000);
			}
			else
			{
				sleep(3);
			}
		}
	}
}
