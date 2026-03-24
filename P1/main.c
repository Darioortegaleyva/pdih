#include "mi_io.h"

int main(){
	setvideomode(3);
	clrscr();
	
	textcolor(YELLOW);
	textbackground(BLUE);
	
	gotoxy(10, 5);
	cputchar('H');
	cputchar('o');
	cputchar('l');
	cputchar('a');
	
	gotoxy(10, 7);
	setcursortype(GRUESO);
	
	getche();
	
	setvideomode(4);
	
	pixel(50,50,1);
	pixel(60,60,2);
	pixel(70,70,3);
	
	getche();
	
	
	setvideomode(3);
	clrscr();
	/* ejercicio 1 extra */
        dibujar_recuadro(10, 5, 70, 20, YELLOW, BLUE);
        dibujar_recuadro(20, 8, 60, 17, LIGHTGREEN, RED);
        dibujar_recuadro(30, 11, 50, 14, LIGHTCYAN, MAGENTA);
        
        getche();
        
        /*ejercicio 2 extra*/
        dibujos_graficos();
        
        /*ejercicio 3 extra*/
        ascii_art();
	
	setvideomode(3);
	clrscr();
	
	return 0;
}
