//
// Created by gerardo on 01/05/17.
//

#ifndef GLADIATOR_GLADIATOR_H
#define GLADIATOR_GLADIATOR_H


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Enemies.h"
#include "Objects.h"
using namespace std;

ALLEGRO_BITMAP *GladIMG                  = NULL;

//PathFindiing para Matriz1
int Ruta1[50];
int Pos1=0;
void CaminoR1(){
    int Fila = 2;
    int Columna = 0;
    for(int i=0; i<50; i++)
        Ruta1[i] = 0;
    for(int i=0; i<50; i++) {
        Ruta1[i] = 0;
        if (Columna==9 && Fila ==2){
            Ruta1[i] = 0;
        }
        else if (Columna==9 && Fila > 2){
            Ruta1[i] = 2;
            Fila--;
        }
        else if (Columna==9 && Fila < 2){
            Ruta1[i] = 3;
            Fila++;
        }
        else if (!Matriz1[Fila][Columna+1].used) {
            Ruta1[i] = 1;
            Columna++;
        }
         else {
            if(Fila>=2 && !Matriz1[Fila+1][Columna].used){
                Ruta1[i] = 3;
                Fila++;
            }
            else{
                Ruta1[i] = 2;
                Fila--;
            }
        }
    }
}

//PathFindiing para Matriz2
int Ruta2[50];
int Pos2=0;

int Stats1[6] = {20,20,20,20,20,20};
int Stats2[6] = {20,20,20,20,20,20};
void CaminoR2(){
    int Fila = 2;
    int Columna = 0;

    for(int i=0; i<50; i++) {
        Ruta2[i] = 0;
        if (Columna==9 && Fila ==2){
            Ruta2[i] = 0;
        }
        else if (Columna==9 && Fila > 2){
            Ruta2[i] = 2;
            Fila--;
        }
        else if (Columna==9 && Fila < 2){
            Ruta2[i] = 3;
            Fila++;
        }
        else if (!Matriz2[Fila][Columna+1].used) {
            Ruta2[i] = 1;
            Columna++;
        }
        else {
            if(Fila>=2 && !Matriz2[Fila+1][Columna].used){
                Ruta2[i] = 3;
                Fila++;
            }
            else{
                Ruta2[i] = 2;
                Fila--;
            }
        }
    }
}

int CalculaRT(int RGM, int RGP, int RGCC){
    int RT = 2*(RGM+RGP+RGCC)/3;
    return RT;
}
void Genera1(Gladiator Glad[],int tamanho, int Stats[],Data Matriz[FILA][COLUM]){
    CaminoR1();
    for (int i=0; i<tamanho;i++){
        Pos1=0;
        Glad[i].Fila = 2;
        Glad[i].Columna = 0;
        Glad[i].x = Matriz[Glad[i].Fila][Glad[i].Columna].x;
        Glad[i].y = Matriz[Glad[i].Fila][Glad[i].Columna].y;
        Glad[i].bordeX = Glad[i].bordeY = 50;
        Glad[i].MGM = Stats[0];
        Glad[i].MGP = Stats[1];
        Glad[i].MGCC = Stats[2];
        Glad[i].RGM = Stats[3];
        Glad[i].RGP = Stats[4];
        Glad[i].RGCC = Stats[5];
        Glad[i].RT = CalculaRT(Glad[i].RGM, Glad[i].RGP, Glad[i].RGCC);
        Glad[i].activo = true;

    }
}
void Genera2(Gladiator Glad[],int tamanho, int Stats[],Data Matriz[FILA][COLUM]){
    CaminoR2();
    for (int i=0; i<tamanho;i++){
        Pos1=0;
        Glad[i].Fila = 2;
        Glad[i].Columna = 0;
        Glad[i].x = Matriz[Glad[i].Fila][Glad[i].Columna].x;
        Glad[i].y = Matriz[Glad[i].Fila][Glad[i].Columna].y;
        Glad[i].bordeX = Glad[i].bordeY = 50;
        Glad[i].MGM = Stats[0];
        Glad[i].MGP = Stats[1];
        Glad[i].MGCC = Stats[2];
        Glad[i].RGM = Stats[3];
        Glad[i].RGP = Stats[4];
        Glad[i].RGCC = Stats[5];
        Glad[i].RT = CalculaRT(Glad[i].RGM, Glad[i].RGP, Glad[i].RGCC);
        Glad[i].activo = true;

    }
}
void ActualizaGlads1(Gladiator Glad[],int tamanho, Data Matriz[FILA][COLUM]){
    for(int i=0;i<tamanho;i++) {
        if(Glad[i].Fila==2 && Glad[i].Columna==9){
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
        }
        if(Ruta1[Pos1]==0){
            break;
        }
        else if (Ruta1[Pos1] == 1) {
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Columna++;
            Pos1++;
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
        else if (Ruta1[Pos1] == 2) {
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Fila--;
            Pos1++;
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
        else if (Ruta1[Pos1] == 3) {
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Fila++;
            Pos1++;
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
    }
}
void ActualizaGlads2(Gladiator Glad[],int tamanho, Data Matriz[FILA][COLUM]){
    for(int i=0;i<tamanho;i++) {
        if(Glad[i].Fila==2 && Glad[i].Columna==9){
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
        }
        if(Ruta2[Pos2]==0){
            break;
        }
        else if (Ruta2[Pos2] == 1) {
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Columna++;
            Pos2++;
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
        else if (Ruta2[Pos2] == 2) {
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Fila--;
            Pos2++;
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
        else if (Ruta2[Pos2] == 3) {
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Fila++;
            Pos2++;
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
    }
}
void Regenera(Gladiator Glad[], int Stats[]){
    for (int i = 0; i < 1; ++i) {
        Glad[i].MGM = Stats[0];
        Glad[i].MGP = Stats[1];
        Glad[i].MGCC = Stats[2];
        Glad[i].RGM = Stats[3];
        Glad[i].RGP = Stats[4];
        Glad[i].RGCC = Stats[5];
        Glad[i].RT = CalculaRT(Glad[i].RGM, Glad[i].RGP,Glad[i].RGCC);

    }
}
void DibujaGlad(Gladiator Glad[], int tamanho,Data Matriz[FILA][COLUM],int curFrame,int FrameW, int FrameH) {
    for (int i=0; i < tamanho; i++) {
        if (Glad[0].activo) {
            Glad[0].x = Matriz[Glad[i].Fila][Glad[i].Columna].x;
            Glad[0].y = Matriz[Glad[i].Fila][Glad[i].Columna].y;
            al_draw_bitmap_region(GladIMG, curFrame * FrameW, 0, FrameW, FrameH, Glad[i].x + 10, Glad[i].y + 2, 0);

        }
    }
}

#endif //GLADIATOR_GLADIATOR_H
