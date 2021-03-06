#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 30000


typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x, y;
    int dir_x;
    int dir_y;
    int player;
} Ball;

typedef struct {
    int x, y;
    int id;
    int dir_y;
    int len;
} Player;



int rows, cols;
int game_over = 0;


void init_player(Player *p, int x, int len, int id) {
    p->x = x;
    p->dir_y = 0;
    p->y = rows / 2;
    p->id = id;
    p->len = len;
}

void draw_player(Player *p) {
    int y_ini = p->y - p->len/2;
    int i;
    for (i = 0; i < p->len; i++){
        mvprintw(y_ini+i, p->x, "I");
    }
}

void update_player(Player *p) {
    p->y += p->dir_y;
    p->dir_y = 0;
}

void init_ball(Ball *b, int x, int y) {
    b->x = x;
    b->y = y;
    b->dir_x = 1;
    b->dir_y = 1;
    b->player = 0;
}

void update_ball(Ball *b) {
    if (b->y <= 0 || b->y >= rows) {
        b->dir_y *= -1;
    }

    if (b->x <= 0 || b->x >= cols) {
        game_over = 1;
    }

    b->x += b->dir_x;
    b->y += b->dir_y;
}

void hit(Ball *b, Player *p) {
    if (b->x == p->x && b->y >= p->y-p->len/2 && b->y <= p->y+p->len/2) {
        b->dir_x *= -1;
        b->dir_y *= -1;
        b->player = p->id;
    }
}


int main() {

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    clear();

    refresh();
    getmaxyx(stdscr, rows, cols);

    /* wbkgd(window, COLOR_PAIR(1)); *\/ */
    Ball b;

    init_ball(&b, cols/2, rows/2);

    Player p1, p2;
    init_player(&p1, 2, 6, 1);
    init_player(&p2, cols-2, 6, 2);

    int ch = 0;
    while (!game_over) {
        clear();

        mvprintw(b.y, b.x, "o");
        draw_player(&p1);
        draw_player(&p2);
        refresh();
        update_ball(&b);
        hit(&b, &p1);
        hit(&b, &p2);
        update_player(&p1);
        update_player(&p2);
        ch = getch();
        if (ch == 'w') {
            p1.dir_y = -1;
        } else if (ch == 's')
            p1.dir_y = 1;
        if (ch == 'i')
            p2.dir_y = -1;
        else if (ch == 'k')
            p2.dir_y = 1;

        usleep(DELAY);


    }
    clear();
    mvprintw(5, cols/2, "Ha ganado el jugador %d", b.player);
    refresh();
    int score = 1;
    while (score) {
        if (getch() == 'q') {
            score = 0;
        }
    }


    endwin();
    return 0;
}
