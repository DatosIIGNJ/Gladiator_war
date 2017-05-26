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

int CalculaRT(int RGM, int RGP, int RGCC){
    int RT = (RGM*RGP*RGCC)/3;
    return RT;
}
void Genera1(Gladiator Glad[],int tamanho, int Stats[],Data Matriz[FILA][COLUM]){
    for (int i=0; i<tamanho;i++){
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
    for (int i=0; i<tamanho;i++){
        Glad[i].Fila = 2;
        Glad[i].Columna = 0;
        Glad[i].x = Matriz[Glad[i].Fila][Glad[i].Columna].x;
        Glad[i].y = Matriz[Glad[i].Fila][Glad[i].Columna].y;
        Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
        Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
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
    for (int i=0 ; i<tamanho;i++){
        if(Matriz[Glad[i].Fila][Glad[i].Columna+1].used){
            if(Glad[i].Fila>2){
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila -= 1;
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                if(Matriz[Glad[i].Fila][Glad[i].Columna+1].used) {
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila -= 1;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                break;
            }
            else if(Glad[i].Fila<2){
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila += 1;
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                if(Matriz[Glad[i].Fila][Glad[i].Columna+1].used) {
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila += 1;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                break;
            }
            else{
                if(Matriz[Glad[i].Fila-1][Glad[i].Columna].used) {
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila += 1;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                else if(Matriz[Glad[i].Fila+1][Glad[i].Columna].used) {
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila -= 1;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                } else{
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila -= 1;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                break;
            }
        }
        if (Glad[i].Columna==9){
            if(Glad[i].Fila>2){
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila -= 1;
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                break;}
            else if(Glad[i].Fila<2){
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila += 1;
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
                break;}
            else{
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
            }
            /*else{
                Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila =2;
                Glad[i].Columna =0;
                break;
            }*/
        }
        else if(!Matriz[Glad[i].Fila][Glad[i].Columna+1].used){
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Columna+=1;
            Matriz1[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz1[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
    }
}
void ActualizaGlads2(Gladiator Glad[],int tamanho, Data Matriz[FILA][COLUM]){
    for (int i=0 ; i<tamanho;i++){
        if(Matriz[Glad[i].Fila][Glad[i].Columna+1].used){
            if(Glad[i].Fila>2){
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila -= 1;
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                if(Matriz[Glad[i].Fila][Glad[i].Columna+1].used) {
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila -= 1;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                break;
            }
            else if(Glad[i].Fila<2){
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila += 1;
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                if(Matriz[Glad[i].Fila][Glad[i].Columna+1].used) {
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila += 1;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                break;
            }
            else{
                if(Matriz[Glad[i].Fila-1][Glad[i].Columna].used) {
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila += 1;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                else if(Matriz2[Glad[i].Fila+1][Glad[i].Columna].used) {
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila -= 1;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                } else{
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                    Glad[i].Fila -= 1;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                    Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                }
                break;
            }
        }
        if (Glad[i].Columna==9){
            if(Glad[i].Fila>2){
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila -= 1;
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                break;}
            else if(Glad[i].Fila<2){
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila += 1;
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
                break;}
            else{
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
            }
            /*else{
                Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
                Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
                Glad[i].Fila =2;
                Glad[i].Columna =0;
                break;
            }*/
        }
        else if(!Matriz2[Glad[i].Fila][Glad[i].Columna+1].used){
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = false;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =0;
            Glad[i].Columna+=1;
            Matriz2[Glad[i].Fila][Glad[i].Columna].used = true;
            Matriz2[Glad[i].Fila][Glad[i].Columna].tipo =1;
            break;
        }
    }
}
void DibujaGlad(Gladiator Glad[], int tamanho,Data Matriz[FILA][COLUM],int curFrame,int FrameW, int FrameH) {
    for (int i=0; i < tamanho; i++) {
        Glad[i].x = Matriz[Glad[i].Fila][Glad[i].Columna].x;
        Glad[i].y = Matriz[Glad[i].Fila][Glad[i].Columna].y;
        al_draw_bitmap_region(GladIMG,curFrame*FrameW,0,FrameW,FrameH,Glad[i].x+10, Glad[i].y+2,0);
    }
}

#endif //GLADIATOR_GLADIATOR_H
