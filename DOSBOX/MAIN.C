#include <stdio.h>
#include <dos.h>

int mi_getchar() {
		union REGS inregs, outregs;
		int caracter;

		inregs.h.ah = 1;
		int86(0x21, &inregs, &outregs);
		caracter = outregs.h.al;
		return caracter;
}

int main() {
		int tmp;

		printf("\nPulsa una tecla:\n");
		tmp = mi_getchar();
		printf("%d", tmp);

    return 0;
}
