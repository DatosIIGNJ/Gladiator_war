//
// Created by gerardo on 25/05/17.
//

#ifndef GLADIATOR_PELEA_H
#define GLADIATOR_PELEA_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

ALLEGRO_DISPLAY *PeleaS            = NULL;
ALLEGRO_EVENT_QUEUE *eventos       = NULL;
ALLEGRO_TIMER *FPS                 = NULL;
ALLEGRO_FONT *Roman                = NULL;
ALLEGRO_FONT *Dalek                = NULL;
ALLEGRO_BITMAP *Pelea              = NULL;
ALLEGRO_BITMAP *Glad1              = NULL;
ALLEGRO_BITMAP *Glad2              = NULL;
ALLEGRO_BITMAP *GladiatorF         = NULL;
ALLEGRO_BITMAP *Casco              = NULL;
ALLEGRO_BITMAP *Espada             = NULL;
ALLEGRO_SAMPLE *GolpeP             = NULL;
ALLEGRO_SAMPLE *GolpeM             = NULL;
ALLEGRO_SAMPLE *GolpeC             = NULL;


int curFrame1 = 0;
int curFrame2 = 0;
int Framecount1 = 0;
int Framecount2= 10;
int FrameW = 265;
int FrameW2 = 240;
int FrameH = 198;
int numGen1=0;
int numGen2=0;

int GolpePie(int RT){
    RT -= 15;
    al_play_sample(GolpeP,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    return RT;
}

int GolpeMano(int RT){
    RT -= 15;
    al_play_sample(GolpeM,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    return RT;
}
int GolpeCuerpo(int RT){
    RT -= 15;
    al_play_sample(GolpeC,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    return RT;
}

void PeleaV(Gladiator Gladi1[], Gladiator Gladi2[]){
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);

    bool Salir =true;

    srand(time(NULL));

    int repaint = 1;

    Pelea = al_load_bitmap("images/Fondo2.png");
    Glad1 = al_load_bitmap("images/gladiators1.png");
    Glad2 = al_load_bitmap("images/gladiators2.png");
    Dalek = al_load_font("Fonts/dalek.ttf",24,0);
    Roman = al_load_font("Fonts/Roman.ttf",20,7);
    GolpeP = al_load_sample("Sonidos/GolpeP.wav");
    GolpeM = al_load_sample("Sonidos/GolpeM.wav");
    GolpeC = al_load_sample("Sonidos/GolpeC.wav");
    GladiatorF = al_load_bitmap("images/GladiatorF.png");
    Casco = al_load_bitmap("images/Casco.png");
    Espada = al_load_bitmap("images/Espada.png");

    PeleaS = al_create_display(900, 500);
    al_set_window_position(PeleaS,175,60);
    al_set_window_title(PeleaS,"Genetic Gladiators");
    eventos = al_create_event_queue();
    FPS = al_create_timer(1.0/60);

    al_register_event_source(eventos, al_get_display_event_source(PeleaS));
    al_register_event_source(eventos,al_get_timer_event_source(FPS));

    al_start_timer(FPS);
    while (Salir){
        if (Gladi2[0].RT <0 ) {
            Gladi2[0].RT = 0;
            al_rest(2);
            cout << "Fin del juego, Gano 1" << endl;
            repaint =0;
            al_draw_bitmap(Pelea, 0, 0, 0);
            al_draw_filled_rectangle(260,40,640,150,al_map_rgb(241,250,121));
            al_draw_text(Roman,al_map_rgb(0,0,0),450,60,ALLEGRO_ALIGN_CENTER,"El Gladiador 1 Gano");
            al_draw_textf(Roman, al_map_rgb(0,0,0),450,90,ALLEGRO_ALIGN_CENTER,"Generacion Numero: %i", numGen1);
            al_draw_textf(Roman, al_map_rgb(0,0,0),450,120,ALLEGRO_ALIGN_CENTER,"Fitnes del gladiador: %i", Gladi1[0].Fitnes);
            al_draw_bitmap(GladiatorF,420,180,0);
            al_draw_bitmap(Casco,150,200,0);
            al_draw_bitmap(Espada,130,280,0);
            al_flip_display();
            al_rest(10);
            Salir = false;
            break;

        }
        if (Gladi1[0].RT <0 ) {
            Gladi1[0].RT = 0;
            al_rest(2);
            cout << "Fin del juego, Gano 2" << endl;
            repaint =0;
            al_draw_bitmap(Pelea, 0, 0, 0);
            al_draw_filled_rectangle(260,40,640,150,al_map_rgb(241,250,121));
            al_draw_text(Roman,al_map_rgb(0,0,0),270,60,ALLEGRO_ALIGN_LEFT,"El Gladiador 2 Gano");
            al_draw_textf(Roman, al_map_rgb(0,0,0),450,90,ALLEGRO_ALIGN_CENTER,"Generacion Numero: %i", numGen2);
            al_draw_textf(Roman, al_map_rgb(0,0,0),450,120,ALLEGRO_ALIGN_CENTER,"Fitnes del gladiador: %i", Gladi2[0].Fitnes);
            al_draw_bitmap(GladiatorF,420,180,0);
            al_draw_bitmap(Casco,150,200,0);
            al_draw_bitmap(Espada,130,280,0);
            al_flip_display();
            al_rest(10);
            Salir = false;
            break;
        }
        if (repaint) {
            al_draw_bitmap(Pelea, 0, 0, 0);
            al_draw_filled_rectangle(200,40,400,100,al_map_rgb(241,250,121));
            al_draw_rectangle(200,40,400,100,al_map_rgb(0,0,0),2);
            al_draw_textf(Roman,al_map_rgb(0,0,0),300,60,ALLEGRO_ALIGN_CENTRE,"Res. Total: %i",Gladi1[0].RT);
            al_draw_filled_rectangle(500,40,700,100,al_map_rgb(241,250,121));
            al_draw_rectangle(500,40,700,100,al_map_rgb(0,0,0),2);
            al_draw_textf(Roman,al_map_rgb(0,0,0),600,60,ALLEGRO_ALIGN_CENTRE,"Res. Total: %i",Gladi2[0].RT);
            al_draw_bitmap_region(Glad1, curFrame1 * FrameW, 0, FrameW, FrameH, 200, 200, 0);
            al_draw_bitmap_region(Glad2, (curFrame2 * FrameW)-30, 0, FrameW2, FrameH, 450, 200, 0);
            al_flip_display();
        }
        ALLEGRO_EVENT event;
        al_wait_for_event(eventos, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        if (event.type == ALLEGRO_EVENT_TIMER) {
            if(++Framecount1 >= 60){
                curFrame1=rand()%5;
                if(curFrame1 != 1){
                    if(curFrame1==0)
                        Gladi2[0].RT = GolpePie(Gladi2[0].RT);
                    else if (curFrame1 == 2)
                        Gladi2[0].RT = GolpeMano(Gladi2[0].RT);
                    else if (curFrame1 == 4)
                        Gladi2[0].RT = GolpeCuerpo(Gladi2[0].RT);
                }
                Framecount1=0;
            }
            if(++Framecount2 >= 60){
                curFrame2=rand()%5;
                if(curFrame2 != 3){
                    if(curFrame2==1)
                        Gladi1[0].RT = GolpeCuerpo(Gladi1[0].RT);
                    else if (curFrame2 == 2)
                        Gladi1[0].RT = GolpeMano(Gladi1[0].RT);
                    else if (curFrame2 == 5)
                        Gladi1[0].RT = GolpePie(Gladi1[0].RT);
                }
                Framecount2=0;
            }

        }

    }
    al_destroy_event_queue(eventos);
    al_destroy_timer(FPS);
    al_destroy_font(Roman);
    al_destroy_font(Dalek);
    al_destroy_bitmap(Glad1);
    al_destroy_bitmap(Glad2);
    al_destroy_bitmap(GladiatorF);
    al_destroy_bitmap(Casco);
    al_destroy_bitmap(Espada);
    al_destroy_display(PeleaS);
    al_destroy_bitmap(Pelea);
    al_destroy_sample(GolpeM);
    al_destroy_sample(GolpeP);
    al_destroy_sample(GolpeC);
}
#endif //GLADIATOR_PELEA_H
