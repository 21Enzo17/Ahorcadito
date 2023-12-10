#include <iostream>
#include <stdlib.h>
using namespace std;
typedef struct tarbol *parbol;
typedef struct tarbol{
                    tjugador jugador;
                    parbol izq;
                    parbol der;
                    };
void iniciar_a(parbol &arbol){
    arbol=NULL;
}
void crear_nodoA(parbol &nuevo,tjugador j){
    nuevo=new tarbol;
    if(nuevo!=NULL){
        nuevo->jugador=j;
        nuevo->izq=NULL;
        nuevo->der=NULL;
    }else{ 
        cout<<"Espacio de memoria insuficiente"<<endl;
    }
}
void insertar_puntos(parbol &a, parbol nuevo){
    if(a==NULL){
        a=nuevo;
    }else{
        if(nuevo->jugador.id_jugador!=a->jugador.id_jugador){
            if(nuevo->jugador.puntaje < a->jugador.puntaje){
                insertar_puntos(a->izq,nuevo);
            }else{
                insertar_puntos(a->der,nuevo);
            }
        }else{
            cout<<"Dato repetido, el nodo ha sido liberado"<<endl;
            delete(nuevo);
        }
    }
}
void insertar_wins(parbol &a, parbol nuevo){
    if(a==NULL){
        a=nuevo;
    }else{
        if(nuevo->jugador.id_jugador!=a->jugador.id_jugador){
            if(nuevo->jugador.wins < a->jugador.wins){
                insertar_puntos(a->izq,nuevo);
            }else{
                insertar_puntos(a->der,nuevo);
            }
        }else{
            cout<<"Dato repetido, el nodo ha sido liberado"<<endl;
            delete(nuevo);
        }
    }
}
void may_men(parbol a){
    if(a!=NULL){
        may_men(a->der);
        cout<<a->jugador.puntaje<<"     | "<<a->jugador.wins<<" | "<<a->jugador.nickname<<endl;
        may_men(a->izq);
    }
}
void liberarA(parbol &a){
    if(a!=NULL){
        liberarA(a->izq);
        liberarA(a->der);
        delete(a);
    }
}
