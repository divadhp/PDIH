#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

void pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}

void modovideo(unsigned char modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

int getch() {
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 0;
    int86(0x16, &inregs, &outregs);
	 
    caracter = outregs.h.al;
    return caracter;
}

int kbhit() {
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 11;
    int86(0x21, &inregs, &outregs);
	 
    caracter = outregs.h.al;
    return caracter;
}


void getche() {
    union REGS inregs, outregs;
    int caracter;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
	 
    caracter = outregs.h.al;
    
    
    inregs.h.ah = 9;
    inregs.h.al = caracter;
    int86(0x10, &inregs, &outregs);    
}

void pixel(int x, int y, unsigned char C) {
   union REGS inregs, outregs;
   inregs.x.cx = x;
   inregs.x.dx = y;
   inregs.h.al = C;
   inregs.h.ah = 0x0C;
   int86(0x10, &inregs, &outregs);
}


void mi_putchar(char c) {
    union REGS inregs, outregs;
    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}

void cputchar(char c) {
    union REGS inregs, outregs;
    inregs.h.ah = 9;
    inregs.h.al = c;
    inregs.h.bl = 1;
    inregs.h.bh = 0;
    inregs.x.cx = 1;
	
    int86(0x10, &inregs, &outregs);
}



#define BOARD_W 320
#define BOARD_H 200

#define S_OK      0
#define S_GAMEOVER 1
#define PLAYERS 2


typedef struct {
    int x, y;
} Point;

typedef enum {UP, DOWN, NONE} direction;

typedef enum {LEFT, RIGHT} ori;

typedef struct {
    Point pos;
     int len, score, id;
    int speed;
    direction dir;
    
} Player;

typedef struct {
    Point pos;
    int d;
    int speed;
    ori o;
    direction dir;
    int pid;
} Ball;

int game = 1; // 1-True 0-False
Player pl[PLAYERS];
Ball b;


void b_init(Ball *b) {
    b->pos.x = BOARD_W / 2;
    b->pos.y = BOARD_H / 2;
    b->speed = 2;
    b->o = RIGHT;
    b->dir = NONE;
}

void b_draw(Ball *b) {
    pixel(b->pos.x, b->pos.y, 1);
}

void b_update(Ball *b) {
    if (b->o == LEFT) {
	b->pos.x -= b->speed * 1;
    } else {
	b->pos.x += b->speed * 1;
    }

    if (b->pos.y <= 1) {
	b->dir = DOWN;
    }
    if (b->pos.y >= BOARD_H -1)
	b->dir = UP;
    
    if (b->dir == UP) {
	b->pos.y -= b->speed * 1;
    } else if (b->dir == DOWN) {
	b->pos.y += b->speed * 1;
    }
}

void score(Ball *b) {
    if (b->pos.x < 0) {
	pl[0].score += 1;
	b_init(b);
	game = 0;
    }
    if (b->pos.x > (BOARD_W-1)) {
	pl[1].score += 1;
	b_init(b);
	game = 0;
    }
    
}

void pl_init(Player *p, int i, int x) {
    p->pos.x = x + 1;
    p->pos.y = BOARD_H / 2;
    p->score = 0;
    p->len = 30;
    p->id = i;
    p->dir = NONE;
    p->speed = 3;
}

void pl_draw(Player *p) {
    
    int i;
    int y = p->pos.y - p->len/2;
    for (i = 0; i < p->len; i++) {
	pixel(p->pos.x, y+i, 3);
    }
}

void b_hit(Ball *b, Player *p) {
    if (b->pos.x >= p->pos.x-1 && b->pos.x <= p->pos.x + 1 && b->pos.y >= p->pos.y - p->len/2 & b->pos.y <= p->pos.y + p->len/2) {
	if (p->id == 2) {
	    b->o = LEFT;	    
	}
	if (p->id == 1) {
	    b->o = RIGHT;
	}

	b->dir = p->dir;
	b->pid = p->id;
    }
}

int main() {
   
    int ch = 0;
    int i;

    textmode(64);
    clrscr();
    textcolor(1);
    textbackground(0);
    gotoxy(20, 27);
    /* textbackground(0); */    

    
    for (i=0; i < PLAYERS; i++) {
	pl_init(&pl[i], i+1, i*(BOARD_W - 1) + -2 * i);	
    }
    cputchar('0' + pl[0].id);
    
    b_init(&b);    
    while (game) {
	modovideo(4);
	for (i=0; i < PLAYERS; i++) {
	    pl_draw(&pl[i]);
	}

	b_draw(&b);

	if(kbhit()) {
	    ch = getch();
	}
	
	switch (ch) {
	case 'a':
	    game = 0;
	    break;
	case 'w':
	    if (pl[0].pos.y - pl[0].len/2 > 0)
		pl[0].pos.y -= pl[0].speed * 1;	    
	    pl[0].dir = UP;
	    break;
	case 's':
	    if (pl[0].pos.y + pl[0].len/2 < BOARD_H)
		pl[0].pos.y += pl[0].speed * 1;
	    pl[0].dir = DOWN;
	    break;
	case 'i':
	    if (pl[1].pos.y - pl[1].len/2 > 0)
		pl[1].pos.y -= pl[1].speed * 1;
	    pl[1].dir = UP;
	    break;	    
	case 'k':
	    if (pl[1].pos.y + pl[1].len/2 < BOARD_H)
		pl[1].pos.y += pl[1].speed * 1;
	    pl[1].dir = DOWN;
	    break;
	}
	

	for (i=0; i < PLAYERS; i++){
	    b_hit(&b, &pl[i]);
	}
	score(&b);
	b_update(&b);
	ch = 0;
	delay(30);
    }

    modovideo(3);
    cprintf("Gana el jugador %d", b.pid);

    
    return 0;
}
