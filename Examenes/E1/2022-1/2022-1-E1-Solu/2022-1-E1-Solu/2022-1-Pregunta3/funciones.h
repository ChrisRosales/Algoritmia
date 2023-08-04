/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   funciones.h
 * Autor:  Joham Manuel Elias Ruiz
 * Código: 20191626
 *
 * Created on 21 de mayo de 2022, 12:01 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "lse.h"


ElementoLista crearProceso(int tiempo,int numero);

void volverEnlistar(ElementoLista *procesoActual,Lista *procesos,int T);

#endif /* FUNCIONES_H */

