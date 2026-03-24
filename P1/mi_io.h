#ifndef MI_IO_H
#define MI_IO_H

#define BYTE unsigned char

/* Constantes de colores de Fondo y Texto */
#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTBLUE     9
#define LIGHTGREEN    10
#define LIGHTCYAN     11
#define LIGHTRED      12
#define LIGHTMAGENTA  13
#define YELLOW        14
#define WHITE         15

/* Tipos de cursor */
#define INVISIBLE 0
#define NORMAL    1
#define GRUESO    2

/* Declaracion de funciones */
void gotoxy(int x, int y);
void setcursortype(int tipo_cursor);
void setvideomode(BYTE modo);
BYTE getvideomode();
void textcolor(int color);
void textbackground(int color);
void clrscr();
void cputchar(char c);
int getche();
void pixel(int x, int y, BYTE C);

void dibujar_recuadro(int x1, int y1, int x2, int y2, int color_texto, int color_fondo);
void dibujos_graficos(void);
void ascii_art(void);

#endif
