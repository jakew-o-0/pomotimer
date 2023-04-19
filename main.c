#include <curses.h>
#include <ncurses.h>
#include <locale.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "title.h"
#include "timer_control.h"


void create_window();
extern int hrs, mins, secs, is_countdown_possible;




int main(int argc, char** argv)
{
        for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-s") == 0)
		{
			secs = atoi(argv[i+1]);
			break;
		}

		if(strcmp(argv[i], "-m") == 0)
		{
			mins = atoi(argv[i+1]);
			break;
		}

		if(strcmp(argv[i], "-h") == 0)
		{
			hrs = atoi(argv[i+1]);
			break;
		}

		if(i == (argc - 1))
		{
			printf("incorrect argument(s)\n");
			printf("use -t to set a time\n");
			return 0;
		}
	}

	
	format_time();
	is_countdown_possible = 1;
	create_window();
}






void create_window()
{
	//set up ncurses window
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	
	//create worker threads
	pthread_t t0, t1;
	pthread_create(&t0, NULL, title_animation, NULL);
	pthread_create(&t1, NULL, countdown, NULL);


	// wait for userinput to end program
	wgetch(stdscr);

	endwin();
	pthread_cancel(t0);
	pthread_cancel(t1);
	system("clear");
	return;

}
