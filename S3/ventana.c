#include <stdlib.h>
#include <curses.h>

int main(void) {
    int rows, cols;
    initscr();
    noecho();
    cbreak();
    
    
    if (has_colors() == 0) {
	endwin();
	printf("El terminal no tiene soporte decolor\n");
	exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    clear();
    
    refresh();
    getmaxyx(stdscr, rows, cols);
    
    WINDOW *window = newwin(rows,cols,0,0);
    /* wbkgd(window, COLOR_PAIR(3)); */
    box(window, '|', '-');
    mvwprintw(window, 10, 10, "una cadena");	
    wrefresh(window);
    
    getch();
    endwin();
    return 0;
}
