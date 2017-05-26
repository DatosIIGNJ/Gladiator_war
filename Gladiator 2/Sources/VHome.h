//
// Created by gerardo on 20/05/17.
//

#ifndef GLADIATOR_VHOME_H
#define GLADIATOR_VHOME_H

ALLEGRO_DISPLAY *HomeS            = NULL;
ALLEGRO_EVENT_QUEUE *evento       = NULL;
ALLEGRO_BITMAP *Home              = NULL;
ALLEGRO_BITMAP *Home2             = NULL;

ALLEGRO_MOUSE_STATE mousepos;

void HomeV(){
    al_init();
    al_init_image_addon();
    al_install_mouse();

    int repaint=1;
    bool Salir =true;

    HomeS = al_create_display(1000, 675);
    al_set_window_position(HomeS,175,60);
    evento = al_create_event_queue();

    al_register_event_source(evento, al_get_display_event_source(HomeS));
    al_register_event_source(evento,al_get_mouse_event_source());

    Home = al_load_bitmap("images/Home.png");
    Home2 = al_load_bitmap("images/Home2.png");

    while (Salir){
        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);
        al_get_mouse_state(&mousepos);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(HomeS);
            al_destroy_bitmap(Home);
            al_destroy_bitmap(Home2);
            break;
        }
        if (mousepos.x>61 && mousepos.x<310 && mousepos.y >545 && mousepos.y <632){
            al_draw_bitmap(Home2, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
                al_destroy_display(HomeS);
                al_destroy_bitmap(Home);
                al_destroy_bitmap(Home2);
                break;
            }
        }else if (repaint) {
            al_draw_bitmap(Home, 0, 0, 0);
            al_flip_display();
        }

    }
}

#endif //GLADIATOR_VHOME_H
