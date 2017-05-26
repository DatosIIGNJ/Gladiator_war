//
// Created by gerardo on 30/04/17.
//

#ifndef GLADIATOR_OBJECTS_H
#define GLADIATOR_OBJECTS_H

struct Proyectil{
    int Fila,Columna;
    int IX,IY;
    int espera;
    int x;
    int y;
    int distancia;
    int bordeX;
    int bordeY;
    int velocidad;
    bool activo;
};

struct Enemigo{
    int Fila,Columna;
    int x;
    int y;
    int bordeX;
    int bordeY;
};

struct Gladiator{
    int Fila,Columna;
    int x;
    int y;
    int bordeX;
    int bordeY;
    int MGM;
    int MGP;
    int MGCC;
    int RGM;
    int RGP;
    int RGCC;
    int RT;
    int Fitnes=0;

    int ID;
    bool activo;
};
struct Data{
    int x,y;
    int  tipo;
    bool used;
};

#endif //GLADIATOR_OBJECTS_H
