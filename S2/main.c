#include <stdio.h>
#include <dos.h>

int getchar() {
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    return caracter;
}

int main() {
    
    printf("\nPulsa una tecla:\n");
    printf(getchar());
    
    return 0;
}
