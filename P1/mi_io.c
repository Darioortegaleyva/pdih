#include <dos.h>
#include "mi_io.h"

/* Coloca el cursor en una posicion determinada (int 10h, ah=2) */
void gotoxy(int x, int y) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    inregs.h.dh = y;    /* Fila */
    inregs.h.dl = x;    /* Columna */
    inregs.h.bh = 0;    /* Pagina de video 0 */
    int86(0x10, &inregs, &outregs);
}

/* Fija el aspecto del cursor (int 10h, ah=1) */
void setcursortype(int tipo_cursor) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor) {
        case INVISIBLE:
            inregs.h.ch = 0x20; /* Bit 5 a 1 hace el cursor invisible */
            inregs.h.cl = 0x00;
            break;
        case NORMAL:
            inregs.h.ch = 0x06;
            inregs.h.cl = 0x07;
            break;
        case GRUESO:
            inregs.h.ch = 0x00;
            inregs.h.cl = 0x07;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

/* Variable global para guardar el color actual (Fondo Negro, Texto Blanco por defecto) */
BYTE color_actual = 0x0F;

/* --- FUNCIONES DE VIDEO --- */
void setvideomode(BYTE modo) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    inregs.h.al = modo;
    int86(0x10, &inregs, &outregs);
}

BYTE getvideomode() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
    return outregs.h.al;
}

/* --- FUNCIONES DE COLOR Y PANTALLA --- */
void textcolor(int color) {
    /* Mantenemos el fondo (los 4 bits altos) y cambiamos el texto (los 4 bits bajos) */
    color_actual = (color_actual & 0xF0) | (color & 0x0F);
}

void textbackground(int color) {
    /* Mantenemos el texto (los 4 bits bajos) y cambiamos el fondo (los 4 bits altos) */
    color_actual = (color_actual & 0x0F) | ((color & 0x0F) << 4);
}

void clrscr() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x06;         /* Scroll hacia arriba / Borrar pantalla */
    inregs.h.al = 0x00;         /* 0 indica borrar toda la region */
    inregs.h.bh = color_actual; /* Rellenar con el color actual */
    inregs.h.ch = 0;            /* Fila inicial (arriba) */
    inregs.h.cl = 0;            /* Columna inicial (izquierda) */
    inregs.h.dh = 24;           /* Fila final (pantalla estandar de 80x25) */
    inregs.h.dl = 79;           /* Columna final */
    int86(0x10, &inregs, &outregs);
    gotoxy(0, 0);               /* Colocamos el cursor arriba a la izquierda */
}

void cputchar(char c) {
    union REGS inregs, outregs;
    
    /* 1. Imprimir el caracter con su color */
    inregs.h.ah = 0x09;         
    inregs.h.al = c;            
    inregs.h.bl = color_actual; 
    inregs.h.bh = 0;            
    inregs.x.cx = 1;            
    int86(0x10, &inregs, &outregs);

    /* 2. Leer la posicion actual del cursor (ah = 0x03) */
    inregs.h.ah = 0x03;
    inregs.h.bh = 0; 
    int86(0x10, &inregs, &outregs);

    /* 3. Mover el cursor 1 posicion a la derecha (DL = Columna, DH = Fila) */
    gotoxy(outregs.h.dl + 1, outregs.h.dh);
}

/* --- FUNCIONES DE ENTRADA --- */
int getche() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;         /* Leer tecla con eco (int 21h) */
    int86(0x21, &inregs, &outregs);
    return outregs.h.al;
}

/* --- FUNCIONES DE GRAFICOS --- */
void pixel(int x, int y, BYTE C) {
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = C;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}


/* --- EJERCICIO EXTRA 1 --- */
void dibujar_recuadro(int x1, int y1, int x2, int y2, int color_texto, int color_fondo) {
    int x, y;
    int color_original = color_actual;
    
    /* Guardamos los colores y establecemos los del recuadro */
    textcolor(color_texto);
    textbackground(color_fondo);
    
    /* Esquinas */
    gotoxy(x1, y1);
    cputchar(201);  
    
    gotoxy(x2, y1);
    cputchar(187); 
    
    gotoxy(x1, y2);
    cputchar(200); 
    
    gotoxy(x2, y2);
    cputchar(188); 
    
    /* Línea horizontal */
    for(x = x1 + 1; x < x2; x++) {
        gotoxy(x, y1);
        cputchar(205);  
        gotoxy(x, y2);
        cputchar(205);  
    }
    
    /* Líneas verticales */
    for(y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        cputchar(186);  
        gotoxy(x2, y);
        cputchar(186);  
    }
    
    /* color original */
    textcolor(color_original & 0x0F);
    textbackground((color_original >> 4) & 0x0F);
}

/* --- EJERCICIO EXTRA 2 --- */
void dibujos_graficos(void) {
    int i;
    

    setvideomode(4);
    //clrscr();  
    
    /* Dibujar una línea horizontal */
    for(i = 10; i < 300; i++) {
        pixel(i, 50, 1);  
    }
    
    /* Dibujar una línea vertical */
    for(i = 10; i < 150; i++) {
        pixel(160, i, 2);  
    }
    
    /* Dibujar un rectángulo */
    for(i = 50; i < 120; i++) {
        pixel(i, 80, 3);   /* Borde superior */
        pixel(i, 120, 3);  /* Borde inferior */
    }
    for(i = 80; i < 120; i++) {
        pixel(50, i, 3);   /* Borde izquierdo */
        pixel(119, i, 3);  /* Borde derecho */
    }
    
    /* Dibujar una X */
    for(i = 0; i < 50; i++) {
        pixel(200 + i, 140 + i, 1);
        pixel(250 - i, 140 + i, 1);
    }
    
    getche();
    setvideomode(3);

}

/* --- EJERCICIO EXTRA 3 --- */
void ascii_art(void) {
    int color_original = color_actual;
    
    setvideomode(3);
    clrscr();
    
    /* Dibujo de un gato */
    textcolor(YELLOW);
    gotoxy(35, 5);
    cputchar('/');
    cputchar('\\');
    cputchar('_');
    cputchar('/');
    cputchar('\\');
    
    gotoxy(34, 6);
    cputchar('(');
    cputchar(' ');
    cputchar('o');
    cputchar(' ');
    cputchar('o');
    cputchar(' ');
    cputchar(')');
    
    gotoxy(35, 7);
    cputchar('(');
    cputchar(' ');
    cputchar('"');
    cputchar(' ');
    cputchar('"');
    cputchar(' ');
    cputchar(')');
    
    gotoxy(34, 8);
    cputchar(' ');
    cputchar('(');
    cputchar('_');
    cputchar('_');
    cputchar('_');
    cputchar(')');
    cputchar(' '); 
     
    getche();
   
}
