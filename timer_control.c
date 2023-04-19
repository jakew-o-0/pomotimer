#include <curses.h>
#include <ncurses.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

#include "timer_control.h"

int hrs, mins, secs, is_countdown_possible;


// properly format time into 60's
void format_time()
{
	if(secs > 60)
	{
	        mins += secs / 60;
		secs %= 60;
	}
	if(mins > 60)
	{
		hrs += mins / 60;
		mins %= 60;
	}
}

void reduce_time()
{

	if( secs == 0 )
	{
		if(mins > 0)
		{
			mins--;
			secs = 60;
			return;
		}
		if(hrs > 0)
		{
			hrs--;
			mins = 60;
			return;
		}

		is_countdown_possible = 0;
		return;
	}
	secs--;
}

void* countdown()
{
	WINDOW* timer_win = newwin(10, 10, (LINES / 2) + 1, (COLS / 2) - 5);
	is_countdown_possible = 1;
	

	while (1) 
	{
		mvwprintw(timer_win, 5, 0, "%d:%d:%d", hrs, mins, secs);
		wrefresh(timer_win);

		sleep(1);
		reduce_time();
		wclear(timer_win);
	}
}
