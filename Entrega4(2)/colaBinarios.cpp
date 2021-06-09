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

struct nodoCBinario{
    TBinario bin;
    nodoCBinario * sig;
};

struct _rep_colaBinarios{
    nodoCBinario *primero, *ultimo;
};

TColaBinarios crearColaBinarios(){
    TColaBinarios aux = new _rep_colaBinarios;
    aux->primero = aux->ultimo = NULL;
    return aux;
}

TColaBinarios encolar(TBinario b, TColaBinarios c){
    nodoCBinario *newnodo = new nodoCBinario;
    newnodo->bin = b;
    newnodo->sig = NULL;
    if(c->primero == NULL){
        c->primero = newnodo;
    }else{
        c->ultimo->sig = newnodo;
    }
    c->ultimo = newnodo;
    return c;
}

TColaBinarios desencolar(TColaBinarios c){
    nodoCBinario *aux = c->primero;
    c->primero = c->primero->sig;
    if(c->primero == NULL){
        c->ultimo = NULL;
    }
    delete aux;
    return c;
}

void liberarColaBinarios(TColaBinarios c){
    while (c->primero != NULL){
        desencolar(c);
        c->primero = c->primero->sig;
    }
    delete c;
}

bool estaVaciaColaBinarios(TColaBinarios c){
    return (c->primero == NULL && c->ultimo == NULL);
}

TBinario frente(TColaBinarios c){
    return c->primero->bin;
}