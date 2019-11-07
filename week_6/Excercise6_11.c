/* triangle.c */
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#define ITERMAX 10000
int main(void)
{
	long iter;
	int yi, xi;
	int y[3], x[3];
	int index;
	int maxlines, maxcols;

	/* initialize curses */
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	clear();

	/* initialize triangle */
	 maxlines = LINES - 1;
	maxcols = COLS - 1;

	y[0] = maxlines;
	x[0] = 0;

	y[1] = 0;
	x[1] = maxcols / 2;

	y[2] = maxlines;
	x[2] = maxcols;

	mvaddch(y[0], x[0], '0');
	mvaddch(y[1], x[1], '1');
	mvaddch(y[2], x[2], '2');

	/* initialize yi,xi with random values */
	yi = random()% maxlines;
	xi = random()% maxcols;
	mvaddch(yi, xi, '@');

	/* iterate the triangle */
	for (iter = 0; iter < ITERMAX; iter++)
		{
			/*sleep(1)*/;
			index = random() % 3;
			yi = (yi + y[index]) / 2;
			xi = (xi + x[index]) / 2;
			mvaddch(yi, xi, '*');
			refresh();
			/* sleep(1); */
		}
	/* done */
	mvaddstr(maxlines, maxcols / 2, "Press any key to quit");
	refresh();
	getch();

	endwin();
	return 0;
}

