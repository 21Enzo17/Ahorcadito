#include <iostream> // Cola con entrada restringida
using namespace std;
const int MAX=50;
typedef struct tletra *pletra;
typedef struct tletra{
                    char dato;
                    pletra sig;
                    pletra ant;
                    };
typedef struct tcola{
                    pletra inicio;
                    pletra final;
                    int contador;
                    };
void iniciar_bicola(tcola &cola){
    cola.inicio=NULL;
    cola.final=NULL;
    cola.contador=0;
}
void crear_b(pletra &nuevo, char dato){
    nuevo=new tletra;
    if(nuevo==NULL){
        cout<<"Memoria Insuficiente"<<endl;
    }else{
        nuevo->dato=dato;
        nuevo->sig=NULL;
        nuevo->ant=NULL;
    }
}
bool cola_llena(tcola cola){
    return cola.contador==MAX;
}
bool cola_vacia(tcola cola){
    return cola.contador==0;
}
void agregar_bicola(tcola &cola, char dato){
    pletra nuevo;
    if(cola_llena(cola)){
        cout<<"Cola llena"<<endl;
    }else{
        crear_b(nuevo,dato);
        if(cola_vacia(cola)){
            cola.inicio=nuevo;
            cola.final=nuevo;
        }else{
            nuevo->ant=cola.final;
            cola.final->sig=nuevo;
            cola.final=nuevo;
        }
        cola.contador++;
    }
}
char quitar_bicola(tcola &cola,char op){
    char extraido;
    pletra aux,i;
    if(cola_vacia(cola)){
        extraido=-999;
    }else{
        if(op=='n'){
            extraido=cola.inicio->dato;
            aux=cola.inicio;
            cola.inicio=aux->sig;
            aux->sig=NULL;
        }else{
            if(cola.inicio==cola.final){
                extraido=cola.inicio->dato;
                aux=cola.inicio;
                cola.inicio=NULL;
                cola.final=NULL;
            }else{
                extraido=cola.final->dato;
                aux=cola.final;
                cola.final=aux->ant;
                cola.final->sig=NULL;
                aux->sig=NULL;
                aux->ant=NULL;
            }
            
        }
        delete(aux);
        cola.contador--;
    }
    return extraido;
}
bool palindromo(tcad palabra){
    tcola cola;
    pletra nuevo;
    tcad inverso;
    int i;
    iniciar_bicola(cola);
    for(i=0;i<strlen(palabra);i++){ // creo la cola
        agregar_bicola(cola,palabra[i]);
    }
    for(i=0;!cola_vacia(cola);i++){
        inverso[i]=quitar_bicola(cola,'s'); // quito desde el final asi invierto
    }
    inverso[i+1]='\0';
    return strcmp(palabra,inverso)==0; // Comparo la palabra con su inverso
}