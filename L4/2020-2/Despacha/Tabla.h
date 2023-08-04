/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tabla.h
 * Author: cueva.r
 *
 * Created on 27 de septiembre de 2022, 08:24 AM
 */

#ifndef TABLA_H
#define TABLA_H

#include "Abb.h"

typedef ArbolBB Tabla;
typedef ElementoArbol ElementoTabla;

void construir_tabla(Tabla *);
void registrar_entrada(Tabla *,ElementoArbol );
void elimina_entrada(Tabla *,int);
void destruir_tabla(Tabla *);
void actualiza_entrada(Tabla *tad,int,double);
#endif /* TABLA_H */
