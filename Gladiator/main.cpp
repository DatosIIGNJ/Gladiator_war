#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <time.h>
#include "Sources/Enemies.h"
#include "Sources/Gladiator.h"
#include "Sources/Obstacles.h"

using namespace std;

const int ANCHO = 1000;
const int ALTO = 675;
const int LADO = 60;
const int INIT = 25;
const int NumEnemigos=3;
const int NumRocks=5;
const int NumGlads = 1;
const int maxFrame = 2;
int curFrame = 0;
int Framecount = 0;
int FrameDelay = 20;
int count1=0;
int FrameW = 55;
int FrameH = 60;

void CreaCuadricula(int PosX,int PosY);
void CreaCuadricula2(int PosX,int PosY);
void DibujaMatriz(Data Matriz[FILA][COLUM]);

bool Salir = false;


ALLEGRO_DISPLAY *Vent                    = NULL;
ALLEGRO_EVENT_QUEUE *Evento              = NULL;
ALLEGRO_TIMER *FPS                       = NULL;
ALLEGRO_BITMAP *Sand                     = NULL;
ALLEGRO_BITMAP *Coliseo                  = NULL;
ALLEGRO_BITMAP *Camino                   = NULL;


int main() {
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    srand(time(NULL));

    Tower = al_load_bitmap("images/Tower.png");
    Sand = al_load_bitmap("images/Sand.png");
    Coliseo = al_load_bitmap("images/Coliseo.png");
    Camino = al_load_bitmap("images/Camino.png");
    GladIMG = al_load_bitmap("images/soldado.png");
    Rock = al_load_bitmap("images/Rock.png");

    Vent = al_create_display(ANCHO,ALTO);
    al_set_window_position(Vent,175,60);
    al_set_window_title(Vent,"Genetic Gladiators");
    Evento = al_create_event_queue();
    FPS = al_create_timer(1.0/60);

    al_register_event_source(Evento,al_get_display_event_source(Vent));
    al_register_event_source(Evento,al_get_timer_event_source(FPS));

    CreaCuadricula(INIT+100,INIT);
    CreaCuadricula2(INIT+100,INIT+315);

    Proyectil BalaEnemigo[10];
    Gladiator Gladiar1[NumGlads];
    Gladiator Gladiar2[NumGlads];
    Enemigo Enemy1[NumEnemigos];
    Enemigo Enemy2[NumEnemigos];
    Enemigo Rocks1[NumRocks];
    Enemigo Rocks2[NumRocks];

    int Stats[6] = {20,20,20,20,20,20};

    InitEnemigos1(Enemy1,NumEnemigos);
    InitEnemigos2(Enemy2,NumEnemigos);
    InitRocks1(Rocks1,NumRocks);
    InitRocks2(Rocks2,NumRocks);
    InitBalasE(BalaEnemigo,9);
    Genera1(Gladiar1,NumGlads,Stats,Matriz1);
    Genera2(Gladiar2,NumGlads,Stats,Matriz2);
    DibujaMatriz(Matriz1);
    DibujaMatriz(Matriz2);
    TirabalasE(BalaEnemigo,NumEnemigos,Enemy1);
    al_start_timer(FPS);

    while(!Salir){

        if(1){
            al_clear_to_color(al_map_rgb(255,255,255));

            al_draw_bitmap(Camino,740,170,0);
            al_draw_bitmap(Camino,740,420,ALLEGRO_FLIP_VERTICAL);
            DibujaMatriz(Matriz1);
            DibujaMatriz(Matriz2);
            DibujaEnemigos(Enemy1,NumEnemigos);
            DibujaEnemigos(Enemy2,NumEnemigos);
            DibujaRocks(Rocks1,NumRocks);
            DibujaRocks(Rocks2,NumRocks);
            DibujaBalasE(BalaEnemigo,3);
            al_draw_bitmap(Coliseo,790,260,0);
            DibujaGlad(Gladiar1,NumGlads,Matriz1,curFrame,FrameW,FrameH);
            DibujaGlad(Gladiar2,NumGlads,Matriz2,curFrame,FrameW,FrameH);
            al_flip_display();
        }

        ALLEGRO_EVENT event;
        al_wait_for_event(Evento, &event);



        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            Salir = true;
        if (event.type == ALLEGRO_EVENT_TIMER) {
            ActualizaBalasE1(BalaEnemigo,Enemy1);
            BalaChocaE(BalaEnemigo,Gladiar1);
            if(++Framecount >= FrameDelay){
                ActualizaGlads1(Gladiar1,NumGlads,Matriz1);
                ActualizaGlads2 (Gladiar2,NumGlads,Matriz2);
                if(++curFrame >= maxFrame)
                    curFrame=0;
                Framecount=0;
            }
        }
    }


    al_destroy_bitmap(GladIMG );
    al_destroy_event_queue(Evento);
    al_destroy_bitmap(Tower);
    al_destroy_bitmap(Rock);
    al_destroy_bitmap(Sand);
    al_destroy_bitmap(Camino);
    al_destroy_bitmap(Coliseo);
    al_destroy_timer(FPS);
    al_destroy_display(Vent);

    return 0;
}


void CreaCuadricula(int PosX,int PosY){
    int temp=PosX;
    Data Cords;
    for(int i=0; i<FILA;i++){
        for(int j=0; j<COLUM;j++){
            Cords.x = PosX;
            Cords.y = PosY;
            Cords.used = false;
            Matriz1[i][j] = Cords;
            PosX += LADO;
        }
        PosX = temp;
        PosY += LADO;
    }
}
void CreaCuadricula2(int PosX,int PosY) {
    int temp=PosX;
    Data Cords;
    for(int p=0; p<FILA;p++){
        for(int k=0; k<COLUM;k++){
            Cords.x = PosX;
            Cords.y = PosY;
            Cords.used = false;
            Matriz2[p][k] = Cords;
            PosX += LADO;
        }
        PosX = temp;
        PosY += LADO;
    }
}
void DibujaMatriz(Data Matriz[FILA][COLUM]){
    for(int i=0; i<FILA;i++) {
        for (int j = 0; j < COLUM; j++) {
            al_draw_bitmap(Sand,Matriz[i][j].x,Matriz[i][j].y,0);
        }
    }
    al_draw_rectangle(Matriz[0][0].x,Matriz[0][0].y,Matriz[4][9].x+LADO,Matriz[4][9].y+LADO,al_map_rgb(0,0,0),3);
}
