//
// Created by gerardo on 11/05/17.
//

#ifndef GLADIATOR_OBSTACLES_H
#define GLADIATOR_OBSTACLES_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Objects.h"
#include "Enemies.h"

ALLEGRO_BITMAP *Rock                    = NULL;

void InitRocks1(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        Enemy[i].Fila = rand() % 5;
        Enemy[i].Columna = rand() % 10;
        if(Matriz1[Enemy[i].Fila][Enemy[i].Columna].used){
            Enemy[i].Fila = rand() % 5;
            Enemy[i].Columna = rand() % 10;
        }
        if ((Enemy[i].Fila  == 2 && Enemy[i].Columna == 0) ||(Enemy[i].Fila  == 2 && Enemy[i].Columna == 9)){
            Enemy[i].Fila = rand() % 5;
            Enemy[i].Columna = rand() % 10;
        }
        Matriz1[Enemy[i].Fila][Enemy[i].Columna].used =true;
        Matriz1[Enemy[i].Fila][Enemy[i].Columna].tipo = 2;
        Enemy[i].x = Matriz1[Enemy[i].Fila][Enemy[i].Columna].x;
        Enemy[i].y = Matriz1[Enemy[i].Fila][Enemy[i].Columna].y;
        Enemy[i].bordeX = Enemy[i].bordeY = 50;
    }
}
void InitRocks2(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        Enemy[i].Fila = rand() % 5;
        Enemy[i].Columna = rand() % 10;
        if(Matriz2[Enemy[i].Fila][Enemy[i].Columna].used){
            Enemy[i].Fila = rand() % 5;
            Enemy[i].Columna = rand() % 10;
        }
        if ((Enemy[i].Fila  == 2 && Enemy[i].Columna == 0) ||(Enemy[i].Fila  == 2 && Enemy[i].Columna == 9)){
            Enemy[i].Fila = rand() % 5;
            Enemy[i].Columna = rand() % 10;
        }
        Matriz2[Enemy[i].Fila][Enemy[i].Columna].used =true;
        Matriz2[Enemy[i].Fila][Enemy[i].Columna].tipo = 2;
        Enemy[i].x = Matriz2[Enemy[i].Fila][Enemy[i].Columna].x;
        Enemy[i].y = Matriz2[Enemy[i].Fila][Enemy[i].Columna].y;
        Enemy[i].bordeX = Enemy[i].bordeY = 50;
    }
}
void DibujaRocks(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        al_draw_bitmap(Rock,Enemy[i].x+2,Enemy[i].y+2,0);
    }
}

#endif //GLADIATOR_OBSTACLES_H
