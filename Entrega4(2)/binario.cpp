/* 5160290 */

#include "../include/binario.h"
#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/info.h"
#include "../include/cadena.h"

#include <stdlib.h>
#include <stdio.h>

struct _rep_binario{
    TInfo bDato;
    TBinario izq;
    TBinario der;
};

//implementacion max
static nat max(nat x, nat y){
    if (x < y){
        return y;
    }else{
        return x;
    }
}

TBinario crearBinario(){
    return NULL;
}

TBinario insertarEnBinario(TInfo i, TBinario b){
    if(b == NULL){
        b = new _rep_binario;
        b->bDato = i;
        b->izq = b->der = NULL;
    }else if (natInfo(i) < natInfo(b->bDato)){
        b->izq = insertarEnBinario(i,b->izq);
    }else{
        b->der = insertarEnBinario(i,b->der);
    }
    return b;
}

TInfo mayor(TBinario b){
    if(b->der == NULL){
        return b->bDato;
    }else{
        return mayor(b->der);
    }  
}

TBinario removerMayor(TBinario b){
    TBinario aux,aux2;	
	aux = b->der;
	aux2 = b;
	while (aux->der != NULL) {
		aux = aux->der;
		aux2 = aux2->der;
	}
	aux2->der = aux->izq;
	delete aux;
	return b;
}

TBinario removerDeBinario(nat elem, TBinario b){
    if (b != NULL) {
		if (elem < natInfo(b->bDato))
			b->izq = removerDeBinario(elem, b->izq);
		else if (elem > natInfo(b->bDato))
			b->der = removerDeBinario(elem, b->der);
		else {
			TBinario aux;
			if (b->izq == NULL) {
				aux = b;
				b = b->der;
				liberarInfo(aux->bDato);
				delete aux;
				return b;
			}else if (b->der == NULL) {
				aux = b;
				b = b->izq;
				liberarInfo(aux->bDato);
				delete aux;
				return b;
			}else {
				liberarInfo(b->bDato);
				b->bDato = copiaInfo(mayor(b->izq));
				b->izq = removerDeBinario(natInfo(mayor(b->izq)), b->izq);
				return b;
			}
		}
	}
	return b;
}

void liberarBinario(TBinario b){
    if (!esVacioBinario(b)) {
		if (!esVacioBinario(b->der))		
			liberarBinario(b->der);
		if (!esVacioBinario(b->izq))
			liberarBinario(b->izq);
		liberarInfo(b->bDato);
		delete b;
	} 
}

//implementacion auxiliardeavl
static int auxiliardeavl(TBinario b, bool &aux) {
	int alturaIzq, alturaDer;
	if (esVacioBinario(b) || !aux){
        return 0;
    }
	alturaIzq = auxiliardeavl(b->izq, aux);
	alturaDer = auxiliardeavl(b->der, aux);
	if (abs(alturaIzq - alturaDer) > 1){
        aux = false;
    }
	return (1 + max(alturaDer, alturaIzq));
}

//esAVL usa auxiliardeavl
bool esAvl(TBinario b){
    bool aux = true;
    auxiliardeavl(b, aux);
    return aux;
}

bool esVacioBinario(TBinario b){
    return (b == NULL);
}

TInfo raiz(TBinario b){
    return b->bDato;
}

TBinario izquierdo(TBinario b){
    return b->izq;
}

TBinario derecho(TBinario b){
    return b->der;
}

/*//implementacion copiaBin
static TBinario copiaBin(TBinario b){
    if(esVacioBinario(b)){
        return NULL;
    }else{
        TBinario copia = crearBinario();
        copia->bDato = b->bDato;
        copia->izq = copiaBin(b->izq);
        copia->der = copiaBin(b->der);
        return copia;
    }
}*/

//implementecion pertenece
static bool pertenece(nat elem, TBinario b){
    bool aux;
    if(esVacioBinario(b)){
        aux = false;
    }else{
        if(natInfo(b->bDato) == elem){
            aux = true;
        }else if(natInfo(b->bDato) > elem){
            aux = pertenece(elem, b->izq);
        }else{
            aux = pertenece(elem, b->der);
        }
    }
    return aux;
}

//buscarSubarbol usa pertenece, copiaBin
TBinario buscarSubarbol(nat elem, TBinario b){
    if(pertenece(elem, b)){
        TBinario res;	
	    if (esVacioBinario(b)) {
		    res = NULL;
	    }else if (elem < natInfo(b->bDato)) {
		    res = buscarSubarbol(elem, b->izq);
	    }else if (elem > natInfo(b->bDato)) {
		    res = buscarSubarbol(elem, b->der);	
	    }else {
		    res = b;
	    } 
	    return res;
    }else{
        return NULL;
    }
}

//alturaBinario usa max
nat alturaBinario(TBinario b){
    if(esVacioBinario(b)){
        return 0;
    }else{
        return (1 + max(alturaBinario(b->izq),alturaBinario(b->der)));
    }
}

nat cantidadBinario(TBinario b){
    if(esVacioBinario(b)){
        return 0;
    }else{
        return (1+cantidadBinario(b->izq)+cantidadBinario(b->der));
    }
    
}

//implementacion sUPaux
static double sUPaux(nat i, TBinario b, nat &contador, double &aux) {
	if (!esVacioBinario(b)) {
		sUPaux(i, b->der, contador, aux);		
		if (contador < i && realInfo(b->bDato) > 0) {			
			aux = aux + realInfo(b->bDato);
			contador=contador+1;
		}
		sUPaux(i, b->izq, contador, aux);
	}
	return aux;
}

//sumaUltimosPositivos usa sUPaux
double sumaUltimosPositivos(nat i, TBinario b){
    double auxd = 0;
    nat auxi = 0;
    sUPaux(i, b, auxi, auxd);
    return auxd;
}

//implementacion insertarABBcad
static TCadena insertarABBcad(TCadena c, TBinario b) {
	if (!esVacioBinario(b)) {
		insertarABBcad(c,b->izq);
		insertarAlFinal(copiaInfo(b->bDato), c);
		insertarABBcad(c,b->der);
	}
	return c;
}

//linalizacion usa insertarABBcad
TCadena linealizacion(TBinario b){
    TCadena aux = crearCadena();
    aux = insertarABBcad(aux, b);
    return aux;
}

TBinario menores(double cota, TBinario b){
    TBinario res;
    if(esVacioBinario(b)){
        res = NULL;
    }else{
        TBinario mizq = menores(cota, b->izq);
        TBinario mder = menores(cota, b->der);
        if(realInfo(b->bDato) < cota){
            res = new _rep_binario;
            res->bDato = copiaInfo(b->bDato);
            res->izq = mizq;
            res->der = mder;
        }else if (mizq == NULL){
            res = mder;
        }else if (mder ==NULL){
            res = mizq;
        }else{
            res = new _rep_binario;
            res->bDato = copiaInfo(mayor(mizq));
            res->izq = mizq;
            res->der = mder;
            removerMayor(mizq);
        }
    }
    return res;
}

//implementacion imprimirNodo
static void imprimirNodo(TBinario b, nat lvl) {
	if (b == NULL) {
		printf("\n");
	} else {	
		imprimirNodo(b->der, lvl + 1);
		for (nat i=0; i < lvl; i++) {
			printf("-");
		}
		printf("(%d,%2.2f)", natInfo(b->bDato), realInfo(b->bDato)); 
		imprimirNodo(b->izq, lvl + 1);
	}
}

//imprimirbinario usa imprimirNodo
void imprimirBinario(TBinario b){
    imprimirNodo(b, 0);
}

//implementacion de binbalanceadoaux
TBinario binbalanceadoaux(ArregloNats elems, int inicio, int fin){
    if(inicio > fin){
        return NULL;
    }else{
        TBinario baux = new _rep_binario;
        int medio = (fin + inicio) / 2;
        TInfo aux = crearInfo(elems[medio], 0.00);
        baux->bDato = aux;
        baux->izq = binbalanceadoaux(elems, inicio, medio - 1);
        baux->der = binbalanceadoaux(elems, medio + 1, fin);
        return baux;
    }
}

//binarioBalanceado usa binbalanceadoaux 
TBinario binarioBalanceado(ArregloNats elems, nat n){
    return binbalanceadoaux(elems, 0, n-1);
}