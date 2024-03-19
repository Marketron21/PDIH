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

void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = x;
	inregs.h.dl = y;
	int86(0x10, &inregs, &outregs);
}

void text_color(int c){
	ctexto = c;
}

void text_background(int c){
	cfondo = c;
}

void cputchar(char c, int repes){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = cfondo << 4 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = repes;
	int86(0x10,&inregs,&outregs);
}

void cuadrado(int x1, int y1, int x2, int y2, int c1, int c2){
	int lon = y2-y1+1;
	int aux = x1+1;
	text_color(c1);
	text_background(c2);

	gotoxy(x1,y1);
	
	cputchar('-',lon);
	
	while (aux < x2){
		gotoxy(aux,y1);
		cputchar('|',1);
		gotoxy(aux,y1+1);
		cputchar(' ',lon-1);
		gotoxy(aux,y2);
		cputchar('|',1);
		aux += 1;
	}

	gotoxy(x2,y1);
	
	cputchar('-',lon);
}

int main(){
	printf("PULSA UNA TECLA PARA PINTAR UN CUADRADO");
	mi_pausa();
	clrscr2();
	cuadrado(5,5,12,26,10,1);
	mi_pausa();
	return 0;
}