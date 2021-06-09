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



bool pertenece(nat elem, TCadena cad){
    TLocalizador aux;
    aux = inicioCadena(cad);
    while((aux != NULL) && (natInfo(infoCadena(aux,cad))!= elem)){
        aux = siguiente(aux,cad);
    }
    if (aux != NULL){
        return true;
    }else{
        return NULL;
    }
}


nat longitud(TCadena cad){
    TLocalizador aux;
    nat cont = 0;
    aux = inicioCadena(cad);
    while(aux != NULL){
        cont = cont + 1;
        aux = siguiente(aux,cad);
    }
    return cont;
}


bool estaOrdenadaPorNaturales(TCadena cad){
    bool ordenado;
    ordenado = false;
    if(esVaciaCadena(cad)){
        ordenado = true;
    }else{
        TLocalizador aux;
        aux = siguiente(inicioCadena(cad),cad);
        ordenado = true;
        while((aux != NULL) && (ordenado == true)){
            if((natInfo(infoCadena(anterior(aux,cad),cad)) <= natInfo(infoCadena(aux,cad)))){
                ordenado = true;
            }else{
                ordenado = false;
            }
            aux = siguiente(aux,cad);
        }
    }
    return ordenado;
}

bool hayNatsRepetidos(TCadena cad){
    TLocalizador aux;
    aux = inicioCadena(cad);
    while(aux != NULL && siguienteClave(natInfo(infoCadena(aux,cad)),siguiente(aux,cad),cad) == NULL){
        aux = siguiente(aux,cad);
    }
    return aux != NULL;
}


bool sonIgualesCadena(TCadena c1, TCadena c2){
    TLocalizador aux,aux2;
    bool iguales;
    aux = inicioCadena(c1);
    aux2 = inicioCadena(c2);
    if(longitud(c1) != longitud(c2)){
        iguales = false;
    }else if (esVaciaCadena(c1) && esVaciaCadena(c2)){
        iguales = true;
    }else{
        iguales = (sonIgualesInfo(infoCadena(aux,c1),infoCadena(aux2,c2)));
        while((aux != NULL) && (aux2 != NULL) && (iguales == true)){
            if((sonIgualesInfo(infoCadena(aux,c1),infoCadena(aux2,c2)))){
                iguales = true;
            }else{
                iguales = false;
            }
            aux = siguiente(aux,c1);
            aux2 = siguiente(aux2,c2);
        }
    }
    return iguales;   
}


TCadena concatenar(TCadena c1, TCadena c2){
    TCadena aux;
    aux = copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
    aux = insertarSegmentoDespues(copiarSegmento(inicioCadena(c2),finalCadena(c2),c2),finalCadena(aux),aux);   
    return aux;
}


TCadena ordenar(TCadena cad){
    TLocalizador aux;
    aux = inicioCadena(cad);
    while(aux != NULL){
        intercambiar(menorEnCadena(aux,cad),aux,cad);
        aux = siguiente(aux,cad);
    }
    return cad;
}


TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
    TLocalizador aux;
    TInfo aux2;
    aux = inicioCadena(cad);
    while (aux != NULL){
        if (natInfo(infoCadena(aux,cad)) == original){
            aux2 = crearInfo(nuevo,realInfo(infoCadena(aux,cad)));
            insertarAlFinal(aux2,cad);
            intercambiar(aux,finalCadena(cad),cad);
            removerDeCadena(finalCadena(cad),cad);
        }
        aux = siguiente(aux,cad);
    }
    return cad;
}


TCadena subCadena(nat menor, nat mayor, TCadena cad){
    TCadena aux2 = crearCadena();
    TLocalizador aux;
    aux = inicioCadena(cad);
    while(aux != NULL){
        if(menor <= (natInfo(infoCadena(aux,cad))) && (natInfo(infoCadena(aux,cad))) <= mayor){
            insertarAlFinal(copiaInfo(infoCadena(aux,cad)),aux2);
        }
        aux = siguiente(aux,cad);
    }
    return aux2;
}

//implementacion creadorcad
static TCadena creadorcad(nat l, TBinario b, TCadena c, nat aux) {
	if (l > 0 && !esVacioBinario(b)) {	
		if (aux == l) {
			insertarAlFinal(copiaInfo(raiz(b)), c);
		}else {
            creadorcad(l, izquierdo(b), c,  aux + 1);
			creadorcad(l, derecho(b), c, aux + 1);
		}
	}
	return c;
}

//nivelEnBinario usa creadorcad
TCadena nivelEnBinario(nat l, TBinario b){
    TCadena cad = crearCadena();	
	nat aux = 1;
	return creadorcad(l, b, cad, aux);
}

//implementacion hoja
static bool hoja(TBinario b){
    return (izquierdo(b) == NULL && derecho(b) == NULL);
}

//implementacion auxiliarcamino, usa igualesnatinfo y hoja
static bool auxiliarcamino(TLocalizador loc,TCadena c, TBinario b){
    if(esVacioBinario(b) || loc == NULL){
        return false;
    }else if((natInfo(infoCadena(loc, c)) == natInfo(raiz(b))) && hoja(b) && siguiente(loc, c) == NULL){
        return true;
    }else{
        return ((natInfo(infoCadena(loc, c)) == natInfo(raiz(b))) && (auxiliarcamino(siguiente(loc, c), c, derecho(b)) || auxiliarcamino(siguiente(loc, c), c, izquierdo(b))));
    }
}

// esCamino usa auxiliarcamino
bool esCamino(TCadena c, TBinario b){
    if(esVaciaCadena(c) && esVacioBinario(b)){
        return true;
    }else{
        return auxiliarcamino(inicioCadena(c), c, b);
    }
}

nat cantidadEnIterador(TIterador it){
    nat aux = 0;
    reiniciarIterador(it);
    while (estaDefinidaActual(it)){
        aux = aux + 1;
        avanzarIterador(it);
    }
    return aux;
}

TIterador enAlguno(TIterador a, TIterador b){
    TIterador aux = crearIterador();
    reiniciarIterador(a);
    reiniciarIterador(b);
    while(estaDefinidaActual(a) && estaDefinidaActual(b)){
        if(actualEnIterador(a) < actualEnIterador(b)){
            agregarAIterador(actualEnIterador(a), aux);
            avanzarIterador(a);
        }else if (actualEnIterador(a) > actualEnIterador(b)){
            agregarAIterador(actualEnIterador(b), aux);
            avanzarIterador(b);
        }else{
            agregarAIterador(actualEnIterador(a), aux);
            avanzarIterador(a);
            avanzarIterador(b);
        }
    }
    if (estaDefinidaActual(a)){
        while(estaDefinidaActual(a)){
            agregarAIterador(actualEnIterador(a), aux);
            avanzarIterador(a);
        }
    }else if(estaDefinidaActual(b)){
        while(estaDefinidaActual(b)){
            agregarAIterador(actualEnIterador(b), aux);
            avanzarIterador(b);
        }
    }
    return aux;
}

TIterador soloEnA(TIterador a, TIterador b){
    TIterador aux = crearIterador();
    reiniciarIterador(a);
    reiniciarIterador(b);
    while(estaDefinidaActual(a) && estaDefinidaActual(b)){
        if(actualEnIterador(a) < actualEnIterador(b)){
            agregarAIterador(actualEnIterador(a), aux);
            avanzarIterador(a);
        }else if(actualEnIterador(a) > actualEnIterador(b)){
            avanzarIterador(b);
        }else{
            avanzarIterador(a);
            avanzarIterador(b);
        }
    }
    if (estaDefinidaActual(a)){
        while(estaDefinidaActual(a)){
            agregarAIterador(actualEnIterador(a), aux);
            avanzarIterador(a);
        }
    }
    return aux;
}

TIterador recorridaPorNiveles(TBinario b){
    TIterador itaux = crearIterador();
    if(b != NULL){
        TPila aux  = crearPila(alturaBinario(b) + cantidadBinario(b));
        TColaBinarios cbaux = crearColaBinarios();
        cbaux = encolar(b, cbaux);
        cbaux = encolar(NULL, cbaux);
        while(!estaVaciaColaBinarios(cbaux)){
            b = frente(cbaux);
            cbaux = desencolar(cbaux);
            if(b == NULL && !estaVaciaColaBinarios(cbaux)){
                aux = apilar(UINT_MAX, aux);
                cbaux = encolar(NULL, cbaux);
            }else{
                if (b != NULL){
                    aux = apilar(natInfo(raiz(b)), aux);
                    if(derecho(b) != NULL){
                        cbaux = encolar(derecho(b), cbaux);
                    }
                    if(izquierdo(b) != NULL){
                        cbaux = encolar(izquierdo(b), cbaux);
                    }
                }
            }
        }
        liberarColaBinarios(cbaux);
        while(!estaVaciaPila(aux)){
            itaux = agregarAIterador(cima(aux), itaux);
            aux = desapilar(aux);
        }
        liberarPila(aux);
    }
    return itaux;
}