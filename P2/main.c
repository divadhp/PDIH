#include <stdio.h>
#include <dos.h>

int INVISIBLE = 0;
int NORMAL = 1;
int GRUESO = 2;

void gotoxy(int x, int y) {
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dh = x;
    inregs.h.dl = y;
    inregs.h.bh = 0;
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

void pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}


int main() {
    int i = 0;
    int n = 200;
    for (i; i < n; i++) {
        printf("\n");
    }
   
    setvideomode(4);
    getvideomode();
    pausa();
    setvideomode(3);
    gotoxy(10, 0);
    printf("Prueba gotoxy");
    pausa();


    return 0;
}
