//
// Created by gerardo on 30/04/17.
//

#ifndef GLADIATOR_ENEMIES_H
#define GLADIATOR_ENEMIES_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Objects.h"
using namespace std;


ALLEGRO_BITMAP *Tower                    = NULL;
const int FILA= 5;
const int COLUM = 10;

Data Matriz1[FILA][COLUM];
Data Matriz2[FILA][COLUM];
bool Dir[8];

int Colision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h) {
    if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (b1_y > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
        (b2_y > b1_y + b1_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }

    // collision
    return 1;
}
void Evalua(int Fila, int Columna, Data Matriz[FILA][COLUM]) {
    for(int i=0;i<8;i++)
        Dir[i] = false;
    if(Matriz[Fila][Columna-1].used && Matriz[Fila][Columna-1].tipo==1)
        Dir[0] = true;
    if (Matriz[Fila-1][Columna-1].used && Matriz[Fila-1][Columna-1].tipo==1)
        Dir[1] = true;
    if (Matriz[Fila-1][Columna].used && Matriz[Fila-1][Columna].tipo==1)
        Dir[2] = true;
    if (Matriz[Fila-1][Columna+1].used && Matriz[Fila-1][Columna+1].tipo==1)
        Dir[3] = true;
    if (Matriz[Fila][Columna+1].used && Matriz[Fila][Columna+1].tipo==1)
        Dir[4] = true;
    if (Matriz[Fila+1][Columna+1].used && Matriz[Fila+1][Columna+1].tipo==1)
        Dir[5] = true;
    if (Matriz[Fila+1][Columna].used && Matriz[Fila+1][Columna].tipo==1)
        Dir[6] = true;
    if (Matriz[Fila+1][Columna-1].used && Matriz[Fila+1][Columna-1].tipo==1)
        Dir[7] = true;
}

//--------Func. BalaE.........................................
void InitBalasE(Proyectil BalaE[], int Tamanho){
    for(int i=0;i< Tamanho;i++){
        BalaE[i].velocidad=3;
        BalaE[i].Fila=0;
        BalaE[i].Columna=0;
        BalaE[i].bordeX=5;
        BalaE[i].bordeY=5;
        BalaE[i].activo = false;
    }
}
void TirabalasE(Proyectil BalaE[], int Tamanho, Enemigo Enemy[]){
    for(int i=0;i< Tamanho;i++) {
        for (int j = 0; j < 3; j++) {
            if (!BalaE[j].activo) {
                BalaE[j].Fila = Enemy[i].Fila;
                BalaE[j].Columna = Enemy[i].Columna;
                BalaE[j].x = BalaE[j].IX = Enemy[i].x;
                BalaE[j].y = BalaE[j].IY = Enemy[i].y;
                BalaE[j].activo = true;
                break;
            }
        }
    }
}
void ActualizaBalasE1(Proyectil BalaE[],Enemigo Enemy[]){
    for(int i=0;i< 3;i++) {
        Evalua(Enemy[i].Fila,Enemy[i].Columna,Matriz1);
        if(Dir[0]){
            BalaE[i].x -= BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;}
        else if(Dir[1]){
            BalaE[i].x -= BalaE[i].velocidad;
            BalaE[i].y -= BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else if(Dir[2]){
            BalaE[i].y -= BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else if(Dir[3]){
            BalaE[i].x += BalaE[i].velocidad;
            BalaE[i].y -= BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else if(Dir[4]) {
            BalaE[i].x += BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else if(Dir[5]) {
            BalaE[i].x += BalaE[i].velocidad;
            BalaE[i].y += BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else if(Dir[6]) {
            BalaE[i].y += BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else if(Dir[5]) {
            BalaE[i].x -= BalaE[i].velocidad;
            BalaE[i].y += BalaE[i].velocidad;
            BalaE[i].distancia += BalaE[i].velocidad;
        }
        else{
            BalaE[i].x = BalaE[i].IX;
            BalaE[i].y = BalaE[i].IY;
        }
    }

}
void BalaChocaE(Proyectil BalaE[],Gladiator Glad[]){
    for(int i=0;i< 3;i++) {
        if(Colision(BalaE[i].x,BalaE[i].y,BalaE[i].bordeX,BalaE[i].bordeY,Glad[0].x-15,Glad[0].y,Glad[0].bordeX,Glad[0].bordeY)){
            BalaE[i].x = BalaE[i].IX;
            BalaE[i].y = BalaE[i].IY;
            break;
        }
    }
}
void DibujaBalasE(Proyectil BalaE[], int Tamanho){
    for(int i=0;i< Tamanho;i++) {
        al_draw_filled_circle(BalaE[i].x+30,BalaE[i].y+30,4,al_map_rgb(0,0,0));
    }
}

//---------Func. Enemigos--------------------------------------
void InitEnemigos1(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        Enemy[i].Fila = rand() % 5;
        Enemy[i].Columna = rand() % 10;
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
void InitEnemigos2(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        Enemy[i].Fila = rand() % 5;
        Enemy[i].Columna = rand() % 10;
        if ((Enemy[i].Fila  == 2 && Enemy[i].Columna == 0) ||(Enemy[i].Fila  == 2 && Enemy[i].Columna == 9)){
            Enemy[i].Fila = rand() % 5;
            Enemy[i].Columna = rand() % 10;
        }
        Matriz1[Enemy[i].Fila][Enemy[i].Columna].used =true;
        Matriz1[Enemy[i].Fila][Enemy[i].Columna].tipo = 2;
        Enemy[i].x = Matriz2[Enemy[i].Fila][Enemy[i].Columna].x;
        Enemy[i].y = Matriz2[Enemy[i].Fila][Enemy[i].Columna].y;
        Enemy[i].bordeX = Enemy[i].bordeY = 50;
    }
}
void DibujaEnemigos(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        al_draw_bitmap(Tower,Enemy[i].x+2,Enemy[i].y+2,0);
    }
}

#endif //GLADIATOR_ENEMIES_H
