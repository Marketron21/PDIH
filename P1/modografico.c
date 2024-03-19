#include <stdio.h>
#include <dos.h>

int ctexto = 15;
int cfondo = 0;

void mi_pausa(){
	union REGS inregs, outregs;
	int caracter;
	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);
}

void clrscr2(){
	union REGS inregs, outregs;
	union REGS inregs2, outregs2;
	inregs.h.ah = 0x0F;
	int86(0x10, &inregs, &outregs);
	
	inregs2.h.ah = 0x00;
	inregs2.h.al = outregs.h.al;
	int86(0x10, &inregs2, &outregs2);
}

void set_video_mode(int mode){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = mode;
	int86(0x10, &inregs, &outregs);
}


void pixel(int x, int y, int C){
	union REGS inregs, outregs;
	inregs.x.cx = x;
	inregs.x.dx = y;
	inregs.h.al = C;
	inregs.h.ah = 0x0C;
	int86(0x10, &inregs, &outregs);
}

int main(){	
	int i = 5;
	int j = 5;
	printf("PULSA UNA TECLA PARA PINTAR UN CUADRADO EN MODO GRAFICO");
	mi_pausa();
	set_video_mode(4);


	while ( i < 30){
		j=5;
		while (j < 30){
			pixel(i,j,2);
			j+=1;		
		}
		i+=1;
	}
	mi_pausa();
	set_video_mode(2);
	return(0);
}