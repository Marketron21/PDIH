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

void mi_exit(){
	union REGS inregs, outregs;
	inregs.x.ax = 0x4C00;
	int86(0x21, &inregs, &outregs);
}

void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = x;
	inregs.h.dl = y;
	int86(0x10, &inregs, &outregs);
}

void set_cursor_type(int tipo_cursor){
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

void set_video_mode(int mode){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = mode;
	int86(0x10, &inregs, &outregs);
}

void get_video_mode(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x0F;
	int86(0x10, &inregs, &outregs);

	printf("\nModo de video actual: %d", outregs.h.al);
	printf("\nNumero de columnas: %d", outregs.h.ah);
}

void text_color(int c){
	ctexto = c;
}

void text_background(int c){
	cfondo = c;
}

void cputchar(char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = cfondo << 4 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
}

void clrscr(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x07;
	inregs.h.al = 0;
	inregs.h.ch = 0;
	inregs.h.cl = 0;
	inregs.h.dh = 24;
	inregs.h.dl = 79;
	inregs.h.bh = 0;
	int86(0x10,&inregs,&outregs);
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

int main(){
	//GOTOXY
	printf("\nFuncion gotoxy.\nPulsa una tecla: ");
	mi_pausa();
	gotoxy(17,4);
	printf("CURSOR MOVIDO AQUÏ\nPulsa una tecla para continuar");
	mi_pausa();
	gotoxy(25,0);

	//SETCURSORTYPE
	printf("\nFuncion set_cursor_type.\nPulsa una tecla: ");
	mi_pausa();
	set_cursor_type(0);
	printf("\nCursor invisible\nPulsa una tecla para continuar");
	mi_pausa();
	set_cursor_type(1);
	printf("\nCursor normal\nPulsa una tecla para continuar");
	mi_pausa();
	set_cursor_type(2);
	printf("\nCursor grueso\nPulsa una tecla para continuar");
	mi_pausa();

	//SETVIDEOMODE Y GETVIDEOMODE
	printf("\nFuncion set_video_mode y get_video_mode.\nPulsa una tecla: ");
	mi_pausa();
	set_video_mode(0);
	get_video_mode();
	printf("\nPulsa una tecla para continuar");
	mi_pausa();
	set_video_mode(3);
	get_video_mode();
	printf("\nPulsa una tecla para continuar");
	mi_pausa();

	//TEXTCOLOR, TEXTBACKGROUND y CPUTCHAR
	printf("\nFuncion text_color, text_background y c_put_char.\nPulsa una tecla: ");
	mi_pausa();
	text_color(3);
	printf("\nColor de texto cyan\t");
	cputchar('c');
	printf("\nPulsa una tecla para continuar");
	mi_pausa();
	text_color(13);
	text_background(4);
	printf("\nColor de fondo rojo y de texto violeta\t");
	cputchar('c');
	printf("\nPulsa una tecla para continuar");
	mi_pausa();

	//CLEARSCREEN
	printf("\nFuncion clrscr. Pulsa una tecla para borrar la pantalla");
	mi_pausa();
	clrscr2();
	printf("\nPulsa una tecla para continuar");
	mi_pausa();

	//GETCHE
	printf("\nFuncion getche. Pulsa una tecla para que se vea en pantalla\t");
	mi_pausa();
	printf("\nPulsa una tecla para continuar");
	mi_pausa();
	return 0;
}
