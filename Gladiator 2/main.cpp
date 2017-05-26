#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Sources/Enemies.h"
#include "Sources/Gladiator.h"
#include "Sources/Obstacles.h"
#include "Sources/VHome.h"
#include "Sources/Peticiones.h"

using namespace std;

const int ANCHO = 1250;
const int ALTO = 675;
const int LADO = 60;
const int INIT = 25;
const int NumEnemigos=3;
const int NumRocks=4;
const int NumGlads = 1;
const int maxFrame = 2;
int curFrame = 0;
int count = 0;
int count2 = 0;
int Framecount = 0;
int FrameDelay = 40;
int FrameW = 55;
int FrameH = 60;
int numGen1=0;
int numGen2=0;
int VicComb1 = 0;
int VicComb2 = 0;

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
ALLEGRO_BITMAP *Fondo                    = NULL;
ALLEGRO_FONT *Roman                      = NULL;
ALLEGRO_FONT *Dalek                      = NULL;


int main() {
    HomeV();
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    srand(73);

    Tower = al_load_bitmap("images/Tower.png");
    Sand = al_load_bitmap("images/Sand.png");
    Coliseo = al_load_bitmap("images/Coliseo.png");
    Camino = al_load_bitmap("images/Camino.png");
    GladIMG = al_load_bitmap("images/soldado.png");
    Fondo = al_load_bitmap("images/Fondo.jpg");
    Rock = al_load_bitmap("images/Rock.png");
    Dalek = al_load_font("Fonts/dalek.ttf",24,0);
    Roman = al_load_font("Fonts/Roman.ttf",12,2);

    Vent = al_create_display(ANCHO,ALTO);
    al_set_window_position(Vent,50,30);
    al_set_window_title(Vent,"Genetic Gladiators");
    Evento = al_create_event_queue();
    FPS = al_create_timer(1.0/60);

    al_register_event_source(Evento,al_get_display_event_source(Vent));
    al_register_event_source(Evento,al_get_timer_event_source(FPS));

    CreaCuadricula(INIT,INIT);
    CreaCuadricula2(INIT,INIT+315);

    Proyectil BalaEnemigo[10];
    Proyectil BalaEnemigo2[10];
    Gladiator Gladiar1[NumGlads];
    Gladiator Gladiar2[NumGlads];
    Enemigo Enemy1[NumEnemigos];
    Enemigo Enemy2[NumEnemigos];
    Enemigo Rocks1[NumRocks];
    Enemigo Rocks2[NumRocks];


    InitEnemigos1(Enemy1,NumEnemigos);
    InitEnemigos2(Enemy2,NumEnemigos);
    InitRocks1(Rocks1,NumRocks);
    InitRocks2(Rocks2,NumRocks);
    InitBalasE(BalaEnemigo,3);
    InitBalasE(BalaEnemigo2,3);
    Genera1(Gladiar1,NumGlads,Stats1,Matriz1);
    numGen1++;
    Genera2(Gladiar2,NumGlads,Stats2,Matriz2);
    numGen2++;
    DibujaMatriz(Matriz1);
    DibujaMatriz(Matriz2);
    TirabalasE(BalaEnemigo,NumEnemigos,Enemy1);
    TirabalasE(BalaEnemigo2,NumEnemigos,Enemy2);
    al_start_timer(FPS);

    while(!Salir){

        if(true){
            al_clear_to_color(al_map_rgb(176,148,7));
            al_draw_bitmap(Fondo,0,0,0);

            al_draw_bitmap(Camino,620,170,0);
            al_draw_bitmap(Camino,620,420,ALLEGRO_FLIP_VERTICAL);
            al_draw_filled_rectangle(930,20,1210,310,al_map_rgb(255,255,255));
            al_draw_rectangle(930,20,1210,310,al_map_rgb(0,0,0),2);
            al_draw_rectangle(930,20,1210,70,al_map_rgb(0,0,0),2);
            al_draw_filled_rectangle(930,340,1210,630,al_map_rgb(255,255,255));
            al_draw_rectangle(930,340,1210,630,al_map_rgb(0,0,0),2);
            al_draw_rectangle(930,340,1210,390,al_map_rgb(0,0,0),2);
            al_draw_text(Dalek, al_map_rgb(0,0,0),1070,22,ALLEGRO_ALIGN_CENTRE,"Poblacion 1:");
            al_draw_text(Dalek, al_map_rgb(0,0,0),1070,342,ALLEGRO_ALIGN_CENTRE,"Poblacion 2:");
            al_draw_textf(Roman,al_map_rgb(0,0,0),940,100,ALLEGRO_ALIGN_LEFT,"Generaciones Transcurridas: %i", numGen1);
            al_draw_textf(Roman,al_map_rgb(0,0,0),940,150,ALLEGRO_ALIGN_LEFT,"Victorias en Combate: %i", VicComb1);
            al_draw_textf(Roman,al_map_rgb(0,0,0),940,200,ALLEGRO_ALIGN_LEFT,"Fitnes de la Generacion: %i", Gladiar1[0].Fitnes);
            al_draw_textf(Roman,al_map_rgb(0,0,0),940,420,ALLEGRO_ALIGN_LEFT,"Generaciones Transcurridas: %i", numGen2);
            al_draw_textf(Roman,al_map_rgb(0,0,0),940,470,ALLEGRO_ALIGN_LEFT,"Victorias en Combate: %i", VicComb2);
            al_draw_textf(Roman,al_map_rgb(0,0,0),940,520,ALLEGRO_ALIGN_LEFT,"Fitnes de la Generacion: %i", Gladiar2[0].Fitnes);
            DibujaMatriz(Matriz1);
            DibujaMatriz(Matriz2);
            DibujaEnemigos(Enemy1,NumEnemigos);
            DibujaEnemigos(Enemy2,NumEnemigos);
            DibujaRocks(Rocks1,NumRocks);
            DibujaRocks(Rocks2,NumRocks);
            DibujaBalasE(BalaEnemigo,3);
            DibujaBalasE(BalaEnemigo2,3);
            al_draw_bitmap(Coliseo,670,260,0);
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
            ActualizaBalasE2(BalaEnemigo2,Enemy2);
            Gladiar1[0].RT = BalaChocaE(BalaEnemigo,Gladiar1);
            if(Gladiar1[0].RT <=0){
                Gladiar1[0].activo =false;
                if (++count == 15) {
                    Matriz1[Gladiar1[0].Fila][Gladiar1[0].Columna].used = false;
                    Matriz1[Gladiar1[0].Fila][Gladiar1[0].Columna].tipo = 0;
                    Gladiar1[0].Fila = 2;
                    Gladiar1[0].Columna = 0;
                    Pos1 = 0;
                    Solicita(Stats1);
                    Regenera(Gladiar1,Stats1);
                    numGen1++;
                    Gladiar1[0].activo = true;
                    count=0;
                }
            }
            Gladiar2[0].RT = BalaChocaE(BalaEnemigo2,Gladiar2);
            if(Gladiar2[0].RT <=0){
                Gladiar2[0].activo =false;
                if (++count2 == 15) {
                    Matriz2[Gladiar2[0].Fila][Gladiar2[0].Columna].used = false;
                    Matriz2[Gladiar2[0].Fila][Gladiar2[0].Columna].tipo = 0;
                    Gladiar2[0].Fila = 2;
                    Gladiar2[0].Columna = 0;
                    Pos2 = 0;
                    Solicita(Stats2);
                    Regenera(Gladiar2,Stats2);
                    numGen2++;
                    Gladiar2[0].activo = true;
                    count2=0;
                }
            }
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
    al_destroy_font(Roman);
    al_destroy_font(Dalek);
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
