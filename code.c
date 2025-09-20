#include <ncurses.h>
#include <time.h>	// For time function.
#include <stdlib.h>	// For rand() and srand()
#include <string.h>	// For strlen()

#define TOTAL_RAIN 150

typedef struct s_drop
{
	char	character;
	int	y, x;
	int	color;
	int	speed;
}	t_drop;


int	main(void)
{
	t_drop	rain[TOTAL_RAIN];
	char	*charset;
	int	index, exit;
	int	rows, cols;

	charset = "0123456789abcdefjhigklmnopqrstuvwxyz!?@%#^&*$";

	initscr();	// Inisial the standard screen
	noecho();	// Hide the character (noechoing)
	start_color();	// Enable the colors
	nodelay(stdscr, TRUE);	// Disable the character lisening
	curs_set(0);	// Disable cursor


	// A bunch of colors for random character paint
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

	// Change behavior of rand(), make it actually random.
	srand(time(NULL));

	getmaxyx(stdscr, rows, cols);	// Get max rows & coumns of screen
	
	// Inisialize the rains
	for (int i = 0; i < TOTAL_RAIN; i++)
	{
		rain[i].y = rand() % rows;
		rain[i].x = rand() % cols;
		rain[i].character = charset[rand() % strlen(charset)];
		rain[i].color = rand() % 7 + 1;
		rain[i].speed = rand() % 3 + 1;
	}
	while (1)
	{
		if ((exit = getch()) == 'q')
			break;
		index = 0;
		while (index < TOTAL_RAIN)
		{
			attron(A_BOLD | COLOR_PAIR(rain[index].color));
			mvaddch(rain[index].y, rain[index].x, ' ');
			rain[index].y += rain[index].speed;
			if (rain[index].y >= rows)
			{
				rain[index].y = 0;
				rain[index].x = rand() % cols;
			}
			mvaddch(rain[index].y, rain[index].x, rain[index].character);
			attroff(A_BOLD | COLOR_PAIR(rain[index].color));
			index++;
		}
		refresh();
		// Apply a delay of milliseconds each frame
		napms(40);
	}
	endwin();
	return 0;	
}
