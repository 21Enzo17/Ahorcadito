#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
const int MAX_CONJUNTOS=50;
typedef char telementos[MAX_CONJUNTOS];
typedef struct tconjunto{
                        telementos valores;
                        int ocupado;
                        };

void iniciar_conjunto(tconjunto &conjunto){
    conjunto.ocupado=-1;
}
bool pertenece(tconjunto &conjunto, char letra){
    int i;
    bool existe=false;
    for(i=0;i<=conjunto.ocupado && conjunto.valores[i]!=letra;i++);
    if(i<=conjunto.ocupado)
        existe=true;
    return existe;
}
void cargar_conjunto(tconjunto &conjunto,tcad palabra){
    int i,j=0,lenght;
    lenght=strlen(palabra);
    for(i=0;i<lenght;i++){
        if(!pertenece(conjunto,palabra[i])){
            conjunto.valores[j]=palabra[i];
            conjunto.ocupado++;
        }
    }
}
bool car_distintos(tcad palabra){
    tconjunto aux;
    iniciar_conjunto(aux);
    cargar_conjunto(aux,palabra);
    return strlen(palabra)==aux.ocupado+1;
}