#include <stdio.h>
#include <dos.h>

int INVISIBLE = 0;
int NORMAL = 1;
int GRUESO = 2;

int BACKGROUND = 0;
int COLOR = 0;

void gotoxy(int x, int y) {
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dh = x;
    inregs.h.dl = y;
    inregs.h.bh = 0;
    int86(0x10, &inregs, &outregs);
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



void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor){
    case 0: //invisible
	inregs.h.ch = 010;
	inregs.h.cl = 000;
	break;
    case 1: //normal
	inregs.h.ch = 010;
	inregs.h.cl = 010;
	break;
    case 2: //grueso
	inregs.h.ch = 000;
	inregs.h.cl = 010;
	break;
    }
    int86(0x10, &inregs, &outregs);
}

void setvideomode(unsigned char mode) {
   union REGS inregs, outregs;
   inregs.h.al = mode;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}


int getvideomode() {
    union REGS inregs, outregs;
    int86(0x10, &inregs, &outregs);

    return inregs.h.al;
}
int i = 0;
void clrscr() {
    union REGS inregs, outregs;
    int86(0x10, &inregs, &outregs);
    i = 0;
    for (i; i < inregs.h.al; i++) {
        printf("\n");
    }
    gotoxy(0, 0);
}

void textcolor(unsigned char c) {
    COLOR = c;
}

void textbackground(unsigned char c) {
    BACKGROUND = c;
}

void cputchar(unsigned char c) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = c;
    inregs.h.bl = BACKGROUND << 4 | COLOR;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

void pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}

void box(int x_top, int y_top, int x_bot, int y_bot, int color, int bcolor) {
    union REGS inregs, outregs;
    int cols;
    textcolor(color);
    textbackground(bcolor);
    int86(0x10, &inregs, &outregs);
    cols = inregs.h.al;

    for (i=0; i <= x_bot-x_top; i++) {
        gotoxy(x_top+i, y_top);
        cputchar('|');
        gotoxy(x_top+i, y_bot);
        cputchar('|');
    }

    for (i=1; i < y_bot-y_top; i++) {
        gotoxy(x_top, y_top+i);
        cputchar('-');
        gotoxy(x_bot, y_top+i);
        cputchar('-');
    }
    /* for (i = 0; i < cols; i++) { */
    /*     cputchar('|'); */
    /* } */

}

int main() {
    //clrscr();
    setvideomode(3);
    box(0, 0, 10, 10, 1, 2);
    /* setvideomode(4); */
    /* getvideomode(); */
    /* pausa(); */
    /* setvideomode(3); */
    pausa();


    return 0;
}
