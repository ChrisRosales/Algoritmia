
/* 
 * File:   StructRegion.h
 * Autor: Gabriel Omar Durán Ruiz 
 * Código: 20203371
 * Created on 22 de abril de 2022, 03:58 PM
 */

#ifndef STRUCTREGION_H
#define STRUCTREGION_H
#define MAXCANTROBOT 20;
struct Region{
    char nombre[20];
    double porcPresup;
    int precioRobot[20];
    int distribucion;
    int cantRobot;
};

#endif /* STRUCTREGION_H */

