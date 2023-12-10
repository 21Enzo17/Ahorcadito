#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef FILE *parchivo;
typedef char tcad[100];
#include "jugadores.hpp"
#include "palabras.hpp"
#include "juego.hpp"

main(){
    int opc;
    tcad nickname;
    parchivo f;
    do{
        system("cls");
        cout<<"====== MENU GENERAL ======"<<endl;
        cout<<"1. Menu Jugadores"<<endl;
        cout<<"2. Menu Palabras"<<endl;
        cout<<"3. Jugar"<<endl;
        cout<<"4. Ranking de Jugadores"<<endl;
        cout<<"5. Salir"<<endl;
        cin>>opc;
        switch (opc){
            case 1:
                main_jugadores();
            break;
            case 2:
                main_palabras();
            break;
            case 3:
                main_jugar();
            break;
            case 4:
                do{
                    cout<<"Elija una opcion"<<endl;
                    cout<<"1. Ranking por puntos (Maximo puntaje en una partida)"<<endl;
                    cout<<"2. Ranking por victorias"<<endl;
                    cin>>opc;
                    if(opc!=1 && opc!=2){
                        cout<<"Elija una opcion valida"<<endl;
                    }
                }while(opc!=1 && opc!=2);
                cout<<" ****** Ranking ****** "<<endl;
				if(opc==1){
					ranking_jugadores_puntos();
				}else{
					ranking_jugadores_wins();
				}
                system("pause");
            break;
            case 5:
                cout<<"Salir"<<endl;
            break;
            default:
                cout<<"Elija una opcion correcta"<<endl;
            break;
            
        }
        
    }while(opc!=5);
}
