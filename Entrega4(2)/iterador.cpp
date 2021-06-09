/* 5160290 */

#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/info.h"
#include "../include/cadena.h"

#include <stdlib.h>
typedef struct nodoIter *nodoIterador;
struct nodoIter {
    nat elem;
    nodoIterador sig;
};

struct _rep_iterador{
    nodoIterador inicio, final, actual;
    bool bloqueado;
};

TIterador crearIterador(){
    TIterador newIter = new _rep_iterador;
    newIter->actual = NULL;
    newIter->inicio = NULL;
    newIter->final = NULL;
    newIter->bloqueado = false;
    return newIter;
}

TIterador agregarAIterador(nat elem, TIterador iter){
    nodoIterador aux = new nodoIter;
    aux->elem = elem;
    aux->sig = NULL;
    if (iter->bloqueado == false){
        if(iter->inicio == NULL && iter->final == NULL){
            iter->inicio = aux;
            iter->final = aux;
        }else{
            iter->final->sig = aux;
            iter->final = aux;
        }
    }
    return iter;
}

TIterador reiniciarIterador(TIterador iter){
    if(iter->inicio != NULL){
        iter->actual = iter->inicio;
    }
    iter->bloqueado = true;
    return iter;
}

TIterador avanzarIterador(TIterador iter){
    if (estaDefinidaActual(iter)){
        iter->actual = iter->actual->sig;
    }
    return iter;
}

nat actualEnIterador(TIterador iter){
    return iter->actual->elem;
}

bool estaDefinidaActual(TIterador iter){
    return (iter->actual != NULL);
}

void liberarIterador(TIterador iter){
    nodoIterador aux = iter->inicio;
    nodoIterador aux2;
    while (aux != NULL){
        aux2 = aux;
        aux = aux->sig;
        delete aux2;
    }
    iter->inicio = NULL;
    iter->final = NULL;
    delete iter;
}