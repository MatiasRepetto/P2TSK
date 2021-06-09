/* 5160290 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad) {
  TLocalizador aux;
  while (cad->inicio != NULL){
    aux = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(aux->dato);
    delete aux;
  }
  cad->inicio = NULL;
  cad->final = NULL;
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
  return ((cad->inicio == NULL) && (cad->final == NULL));
}

TLocalizador inicioCadena(TCadena cad) {
  /*
  // versión que sigue la especificación
    TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad->inicio;
    }
    return res;
  */
  
  // versión conociendo la implementación:
  // esVaciaCadena(cad) => cad->inicio == NUL
  assert(!esVaciaCadena(cad) || cad->inicio == NULL);
  return cad->inicio;
}

TLocalizador finalCadena(TCadena cad) {
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else {
    res = cad->final;
  }
  return res;
  delete res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  if(localizadorEnCadena(loc,cad)){}
  return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
  TLocalizador aux;
  if(esVaciaCadena(cad) && esFinalCadena(loc,cad)){
    aux = NULL;
  }else {
    aux = loc->siguiente;
  }
  return aux;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  TLocalizador aux;
  if(esVaciaCadena(cad) && esInicioCadena(loc,cad)){
    aux = NULL;
  }else {
    aux = loc->anterior;
  }
  return aux;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  bool res;
  if((!esVaciaCadena(cad)) && (loc == finalCadena(cad))){
    res = true;
  }else{
    res = false;
  }
  return res;
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
  bool aux;
  if(esVaciaCadena(cad)){
    aux = false;
  }else {
    aux = (loc == inicioCadena(cad));
  }
  return aux;
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  TLocalizador aux = new nodoCadena;
  aux->dato = i;
  aux->siguiente = NULL;
  if(esVaciaCadena(cad)){
    cad->inicio = aux;
    cad->final = aux;
    aux->anterior = NULL;
  }else{
    cad->final->siguiente = aux;
    aux->anterior = cad->final;
    cad->final = aux;
  }
  return cad;
}


TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  if(cad->inicio == loc){
    TLocalizador aux = new nodoCadena;
    aux->dato = i;
    aux->anterior = NULL;
    cad->inicio = aux;
    aux->anterior = loc->anterior;
    aux->siguiente = loc;
    loc->anterior = aux;
  }else{
    TLocalizador aux = new nodoCadena;
    aux->dato = i;
    aux->anterior = loc->anterior;
    aux->siguiente = loc;
    loc->anterior = aux;
    aux->anterior->siguiente = aux;
  }
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  if(!esVaciaCadena(cad)){
    if (cad->inicio == cad->final){
      cad->inicio = NULL;
      cad->final = NULL;
      liberarInfo(loc->dato);
      delete loc;
    }else if (loc == cad->inicio){
      loc->siguiente->anterior = NULL;
      cad->inicio = loc->siguiente;
      liberarInfo(loc->dato);
      delete loc;
    }else if(loc == cad->final){
      cad->final = loc->anterior;
      loc->anterior->siguiente = NULL;
      liberarInfo(loc->dato);
      delete loc;
    }else{
      loc->anterior->siguiente = loc->siguiente;
      loc->siguiente->anterior = loc->anterior;
      liberarInfo(loc->dato);
      delete loc;
    }
  }
  return cad;
}

void imprimirCadena(TCadena cad) {
  TLocalizador aux;
  aux = cad->inicio;
  if(esVaciaCadena(cad)){
    printf("\n");
  }else {
    while (aux != NULL ){
      printf("(%d,%4.2f)", natInfo(aux->dato), realInfo(aux->dato));
      aux = aux->siguiente;
    }
    printf("\n");
  }
}

TLocalizador kesimo(nat k, TCadena cad) {
  TLocalizador aux;
  nat cont, cont2;
  aux = cad->inicio;
  if(!esVaciaCadena(cad)){
    cont = 0;
    while (aux != NULL){
      aux = aux->siguiente;
      cont = cont + 1;
    }
    if (k <= 0 || k > cont){
      aux = NULL;
    }else{
      aux = cad->inicio;
      cont2 = 1;
      while (aux != NULL && k != cont2){
        cont2 = cont2 + 1;
        aux = aux->siguiente;
      }
    }
  }
  return aux;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  if (!esVaciaCadena(sgm)){
    if (esVaciaCadena(cad)){
      cad->inicio = sgm->inicio;
      cad->final = sgm->final;
    }else if(esFinalCadena(loc,cad)){
      sgm->inicio->anterior = loc;
      loc->siguiente = sgm->inicio;
      cad->final = sgm->final;
    }else if(esInicioCadena(loc,cad)){
      sgm->final->siguiente = loc->siguiente;
      loc->siguiente->anterior = sgm->final;
      loc->siguiente = sgm->inicio;
    }else{
      sgm->final->siguiente = loc->siguiente;
      loc->siguiente->anterior = sgm->final;
      sgm->inicio->anterior = loc;
      loc->siguiente = sgm->inicio;
    }
  }
  delete sgm;
  return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TCadena aux = crearCadena();
  if (!esVaciaCadena(cad)){
    while (desde != hasta->siguiente){
      insertarAlFinal(copiaInfo(desde->dato),aux);
      desde = desde->siguiente;
    }
  }
  return aux;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TLocalizador aux;
  aux = desde;
  if (cad->inicio == NULL && cad->final == NULL){
    return cad;
  }else if (desde == hasta && !esVaciaCadena(cad)){
    removerDeCadena(desde,cad);
  }else{  
    while(aux != hasta){
      aux = aux->siguiente;
      removerDeCadena(aux->anterior,cad);
    }
    removerDeCadena(hasta,cad);
  }
  if(desde == cad->inicio){
    cad->inicio = hasta->siguiente;
  }
  if(hasta == cad->final){
    cad->final = desde->anterior;
  }
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  loc->dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  TInfo aux;
  aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador aux;
  aux = cad->inicio;
  if(esVaciaCadena(cad)){
    return false;
  }else{
    while ((aux != NULL) && (aux != loc)){
      aux = aux->siguiente;
    }
    if (aux == NULL){
      return false;
    }else{
      return true;
    }
  }
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  bool aux;
  if(esVaciaCadena(cad)){
    aux = false;
  }else if((loc1 == loc2)){
    aux = true;
  }else if (loc2 == cad->inicio){
    aux = false;
  }else if (loc2 == cad->final->siguiente){
    aux = false;
  }else{
    aux = (loc2->anterior == loc1);
  }
  return aux;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return NULL;
  }else {
    while (loc != NULL && natInfo(loc->dato) != clave ){
      loc = loc->siguiente;
    }
    if(loc != NULL){
      return loc;
    }else{
      return NULL;
    }
  }
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return NULL;
  }else {
    while (loc != NULL && natInfo(loc->dato) != clave ){
      loc = loc->anterior;
    }
    if(loc != NULL){
      return loc;
    }else{
      return NULL;
    }
  }
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador auxl;
  auxl = loc;
  if (!esVaciaCadena(cad)){
    nat aux;
    aux = natInfo(loc->dato);
    while (loc != NULL){
      if((natInfo(loc->dato)) < aux){
        aux = natInfo(loc->dato);
      }
      loc = loc->siguiente;
    }
    return siguienteClave(aux,auxl,cad);
  }else{
    return NULL;
  }
}
