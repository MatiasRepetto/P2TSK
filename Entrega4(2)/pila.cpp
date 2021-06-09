/* 5160290 */

#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/binario.h"
#include "../include/iterador.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/limits.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_pila{
    int* arraypil;
    int tope;
    int cota;
};

TPila crearPila(nat tamanio){
    TPila newpil = new _rep_pila;
    newpil->tope = 0;
    newpil->arraypil = new int [tamanio];
    newpil->cota = tamanio;
    return newpil;
}

TPila apilar(nat num, TPila p){
    if(!estaLlenaPila(p)){
        p->arraypil[p->tope] = num;
        p->tope = p->tope + 1;
    }
    return p;
}

TPila desapilar(TPila p){
    p->tope = p->tope - 1;
    return p;
}

void liberarPila(TPila p){
    delete [] p->arraypil;
    delete p;
}

bool estaVaciaPila(TPila p){
    return (p->tope == 0);
}

bool estaLlenaPila(TPila p){
    return (p->tope == p->cota);
}

nat cima(TPila p){
    return p->arraypil[p->tope - 1];
}