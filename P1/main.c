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
	
	return 0;
}
