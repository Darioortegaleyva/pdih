#include <stdio.h>
#include "mi_io.h"

int main() {
    BYTE modo;

    /* 1. PRUEBAS DE MODO TEXTO Y LECTURA DE MODO */
    setvideomode(3);    /* Forzamos modo texto 80x25 */
    textbackground(BLACK);
    textcolor(WHITE);
    clrscr();

    /* Comprobamos getvideomode() */
    modo = getvideomode();
    gotoxy(2, 2);
    printf("--- PRUEBA DE FUNCIONES MINIMAS ---");
    gotoxy(2, 3);
    printf("Modo de video actual detectado: %d", (int)modo);

    /* 2. PRUEBAS DE COLOR, POSICIONAMIENTO Y SALIDA */
    textcolor(YELLOW);
    textbackground(BLUE);
    
    gotoxy(10, 5);
    cputchar('H');
    cputchar('o');
    cputchar('l');
    cputchar('a');
    
    /* 3. PRUEBA DE CURSOR */
    gotoxy(10, 7);
    printf("Cambiando cursor a GRUESO...");
    setcursortype(GRUESO);
    
    gotoxy(10, 9);
    printf("Pulsa una tecla para ir al MODO GRAFICO (pixel)...");
    getche();
    
    /* 4. PRUEBA DE MODO GRAFICO (pixel) */
    setvideomode(4);
    /* No hacemos clrscr() aqui porque la BIOS ya limpia al cambiar modo */
    
    pixel(50, 50, 1);    /* Cian */
    pixel(60, 60, 2);    /* Magenta */
    pixel(70, 70, 3);    /* Blanco */
    
    getche();
    
    /* 5. PRUEBA EJERCICIO EXTRA 1 (Recuadros) */
    setvideomode(3);
    clrscr();
    gotoxy(2, 2);
    printf("--- EJERCICIO EXTRA 1: RECUADROS ---");
    
    dibujar_recuadro(10, 5, 70, 20, YELLOW, BLUE);
    dibujar_recuadro(20, 8, 60, 17, LIGHTGREEN, RED);
    dibujar_recuadro(30, 11, 50, 14, LIGHTCYAN, MAGENTA);
    
    gotoxy(2, 22);
    printf("Pulsa una tecla para ver DIBUJOS GRAFICOS complejos...");
    getche();
    
    /* 6. PRUEBA EJERCICIO EXTRA 2 (Dibujos complejos) */
    /* La propia funcion pone el modo 4 y vuelve al 3 al terminar */
    dibujos_graficos();
    
    /* 7. PRUEBA EJERCICIO EXTRA 3 (ASCII Art) */
    /* La propia funcion gestiona su pantalla */
    ascii_art();
    
    /* FINALIZACION */
    setvideomode(3);
    setcursortype(NORMAL);
    clrscr();
    printf("Practica finalizada con exito. Saliendo...");
    
    return 0;
}
