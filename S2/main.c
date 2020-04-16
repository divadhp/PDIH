#include <stdio.h>
#include <dos.h>

void getchar() {
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    inregs.h.ah = 9;
    inregs.h.al = caracter;
    int86(0x10, &inregs, &outregs);

}

void setvideomode(unsigned char mode) {
   union REGS inregs, outregs;
   inregs.h.al = mode;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}


int main() {
    
    printf("\nPulsa una tecla:\n");
    getchar()
    
    return 0;
}
