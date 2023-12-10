#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef FILE *parchivo;
typedef char tcad[100];
typedef struct tpalabra
{
    int id_palabra, cant_caracteres;
    tcad palabra, definicion;
};
#include "TDAListas.hpp"
void menu_palabras()
{
    cout<<"***** MENU PALABRAS *****"<<endl;
    cout<<"1- Agregar Palabra"<<endl;
    cout<<"2- Consultar una palabra"<<endl;   
    cout<<"3- Listar palabras"<<endl;
    cout<<"4- Salir"<<endl;
    cout<<"Su eleccion: ";
}
void crear_palabra(tpalabra &palabra){
    cout<<"Ingrese la palabra: ";
    fflush(stdin);
    gets(palabra.palabra);
    cout<<"Ingrese la definicion: ";
    fflush(stdin);
    gets(palabra.definicion);
    palabra.cant_caracteres=strlen(palabra.palabra);

}
void cargar_palabra(parchivo f)
{ 
    tpalabra nueva, aux;
    aux.id_palabra=0;   // Aca le asigno un valor inicial, en el caso de que no haya nada en el archivo el valor se quedara en 0 y en caso de que si haya algo tomara el valor +1
    bool existe = false,entre=false;
    crear_palabra(nueva);
    f = fopen("Palabras.txt", "ab+");
    if (f != NULL)
    {
        while (!feof(f))
        {   entre=true;
            fread(&aux, sizeof(aux), 1, f);
            if (strcmp(aux.palabra,nueva.palabra)==0)
                existe = true;
        }
        if (!existe)
        { 
            nueva.id_palabra=aux.id_palabra+1;
            fwrite(&nueva, sizeof(nueva), 1, f);
        }
        else
        {
            cout << "-ERROR- Ya existe esta palabra "<< endl;
        }
        fclose(f);
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
}
void mostrar_palabras(parchivo f)
{
    tpalabra n;
    cout<<"MOSTRANDO DATOS" << endl;
    f = fopen("Palabras.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f))
        {
            fread(&n, sizeof(n), 1, f);
            if (!feof(f))
            {
                cout << "==========================" << endl;
                cout << "ID                       |" << n.id_palabra << endl;
                cout << "Palabra                  |" << n.palabra << endl;
                cout << "Definicion               |" << n.definicion <<endl;
                cout << "Cantidad de letras       |" << n.cant_caracteres << endl;
                cout << "==========================" << endl;
            }
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    fclose(f);
}
void consulta_palabra(parchivo f, tcad palabra)
{
    tpalabra n;
    bool encontrado = false;
    f = fopen("Palabras.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f) && !encontrado)
        {
            fread(&n, sizeof(n), 1, f);
            if (strcmp(n.palabra,palabra)== 0 && !feof(f))
            {
                cout << "==========================" << endl;
                cout << "ID                       |" << n.id_palabra << endl;
                cout << "Palabra                  |" << n.palabra << endl;
                cout << "Definicion               |" << n.definicion <<endl;
                cout << "Cantidad de letras       |" << n.cant_caracteres << endl;
                cout << "==========================" << endl;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se encontro la palabra" << endl;
        }
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
    fclose(f);
}

void main_palabras(){
    int opc;
    tcad palabra;
    parchivo f;
    do{
        system("cls");
        menu_palabras();
        cin>>opc;
        switch (opc){
            case 1:
                cout<<"***** CARGAR PALABRA *****"<<endl;
                cargar_palabra(f);
            break;
            case 2: 
                cout<<"***** CONSULTAR JUGADOR *****"<<endl;
                cout<<"Ingrese la palabra a buscar: ";
                fflush(stdin);
                gets(palabra);
                consulta_palabra(f,palabra);
            break;
            case 3:
                cout<<"***** LISTAR JUGADORES *****"<<endl;
                mostrar_palabras(f);
            break;
            case 4:
                cout<<"***** SALIENDO PALABRAS *****"<<endl;
            break;
            
        }
        system("pause");
    }while(opc!=4);
}
// Cargar palabras

void cargar_palabras(pnodo &jug1,pnodo &jug2,int nivel){
    pnodo listaC,nuevo,aux; // Lista circular, estructura auxiliar para almacenar todas las palabras del nivel elegido
    iniciar_lista(listaC);
    iniciar_lista(jug1);
    iniciar_lista(jug2);
    srand(time(NULL));
    parchivo f;
    tpalabra p;
    int random,i,j;
    f=fopen("Palabras.txt","rb");
    if(f!=NULL){    // Primero cargamos las palabras segun el nivel en una lista circ
        while(!feof(f)){
            fread(&p, sizeof(p), 1, f);
            if(!feof(f)){
                if(nivel==1){
                    if(p.cant_caracteres==4){
                        crear_nodo(nuevo,p);
                        agregar_final_circ(listaC,nuevo);
                    }
                }else{
                    if(nivel==2){
                        if(p.cant_caracteres==6){
                            crear_nodo(nuevo,p);
                            agregar_final_circ(listaC,nuevo);
                        }
                    }else{
                        if(p.cant_caracteres>=8){
                            crear_nodo(nuevo,p);
                            agregar_final_circ(listaC,nuevo);
                        }
                    }
                }
            }
        }
        fclose(f);
        // Luego cargamos las palabras en su lista eliminandola de la primera lista para no repetirlas
        for(i=0;i<3;i++){
            if(listaC!=NULL){ // esto es para controlar que tenga la cantidad de palabras necesarias, si no las tiene retorna las listas vacias
                aux=listaC;
                random=rand()%150+1;
                for(j=0;j<random;j++){
                    aux=aux->sig;
                }
                crear_nodo(nuevo,aux->palabra);
                agregar_final(jug1,nuevo);
                aux=quitar_nodo_circ(listaC,aux->palabra.id_palabra);
                delete(aux);
                random=rand()%150+1;
                aux=listaC;
                for(j=0;j<rand()%150+1;j++){
                    aux=aux->sig;
                }
                crear_nodo(nuevo,aux->palabra);
                agregar_final(jug2,nuevo);
                aux=quitar_nodo_circ(listaC,aux->palabra.id_palabra);
                delete(aux);
            }else{
                liberar(jug1);
                liberar(jug2);
            }

        }
        if(jug1!=NULL){
            cout<<"Listas generadas con exito"<<endl;
        }

        system("pause");
    }

}
