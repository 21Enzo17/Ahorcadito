#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "TDA Conjuntos.hpp"
#include "TDA Bicolas.hpp"
void menu_jugar(){

    cout<<"A. Elegir jugadores"<<endl;
    cout<<"B. Seleccionar nivel de juego"<<endl;
    cout<<"C. Iniciar Partida"<<endl;
    cout<<"D. Salir Menu Partida"<<endl;
}
void elegir_jugadores(tjugador &jug1,tjugador &jug2){
    tcad nickname;
    bool salir=false,iguales=false;
    int op;
    do{
        cout<<"Ingrese el nickname del usuario 1: ";
        fflush(stdin);
        gets(nickname);
        jug1=elegir_jugador(nickname);
        if(jug1.id_jugador==0){
            cout<<"Desea salir o seguir intentado 1/2"<<endl;
            cin>>op;
            if(op==1){
                salir=true;
            }
        }
    }while(jug1.id_jugador==0 && salir==false);
    if(salir!=true){
        do{
            cout<<"Ingrese el nickname del usuario 2: ";
            fflush(stdin);
            gets(nickname);
            jug2=elegir_jugador(nickname);
            if(jug2.id_jugador==0 ){
                cout<<"Desea salir o seguir intentado 1/2"<<endl;
                cin>>op;
                if(op==1){
                    salir=true;
                    strcpy(jug2.nickname,""); // Solvento un bug en el que se mostraba dos veces el jugador 1 sin haber elegido el jug 2
                }
            }
            if(jug1.id_jugador==jug2.id_jugador){
                cout<<"No puede elegir el mismo jugador dos veces"<<endl;
                cout<<"id1: "<<jug1.id_jugador<<"  jug2: "<<jug2.id_jugador<<endl;
                system("pause");
            }
        }while((jug2.id_jugador==0 && salir==false ) || jug1.id_jugador==jug2.id_jugador);
    }
}
void opciones_jugar(){
        cout<<"1. Probar letra"<<endl;
        cout<<"2. Solicitar Pista"<<endl;
        cout<<"3. Arriesgar"<<endl;
}
int puntaje_palabra(tcad palabra){ // Esto asigna el valor de la palabra
    int puntaje;
    if(car_distintos(palabra)){
        puntaje=9;
    }else{
        if(palindromo(palabra)){
            puntaje=6;
        }else{
            puntaje=3;
        }
    }
    return puntaje; 
}
void gen_renglon(tcad palabra,tcad &renglones){ // Genera renglones
    int i;
    for(i=0;i<strlen(palabra);i++){
        renglones[i]='_';
    }
    renglones[i]='\0';
}
void mostrar_renglon(tcad renglon){ // Muestra la palabra con espacios para mejor comprension
    int i;
    for(i=0;i<strlen(renglon);i++){
        cout<<renglon[i]<<" ";
    }
}
void probar_letra(tcad palabra,char letra,tcad &renglon,int &adiv){
    int i,a=0;
    for(i=0;i<strlen(palabra);i++){
        if(tolower(letra)==tolower(palabra[i])){
            adiv++;
            renglon[i]=palabra[i];
            a++;
        }
    }
    if(a>0){
        cout<<"Si contenia la letra buscada!"<<endl;
        system("pause");
    }
    
}
bool arriesgar_palabra(tcad palabra, tcad intento){
    int i;
    for(i=0;i<strlen(palabra);i++){
        palabra[i]=tolower(palabra[i]);
    }
    for(i=0;i<strlen(intento);i++){
        intento[i]=tolower(intento[i]);
    }
    return strcmp(palabra,intento)==0;
}
void turno(tpalabra p,tjugador jugador,int &puntos,bool &adivinado){
    adivinado=false; 
    char op,letra,corazon=03;
    int intentos,j,ppletra,letrasadiv=0,puntosaux,pnegativo=0;
    tcad intento,renglon;
    intentos=strlen(p.palabra)/2;        // Calculo los intentos con n/2
    gen_renglon(p.palabra,renglon);      // Genero los guiones
    ppletra=puntaje_palabra(p.palabra);  // Calculo los puntos por letra 
    puntosaux=puntos; // genero puntos aux para poder controlar la suma de letras y no sumar dos veces alguna palabra
    while (adivinado != true && intentos > 0){
        cout << "Intentos: ";
        for (j = 0; j < intentos; j++){
            cout << corazon;
        }
        cout << " - Jugador: " << jugador.nickname << " - Palabra: " ;
        mostrar_renglon(renglon);
        cout<<" - Puntos: "<<((letrasadiv*ppletra)+puntosaux-pnegativo)<<endl;
        if (intentos > 1){
            opciones_jugar();
            cin >> op;
        }else{
            do{
                cout<<"Solo le queda un intento, desea adivinar la palabra o pedir una pista"<<endl;
                cout<<"1. Pedir Pista"<<endl;
                cout<<"2. Adivinar la palabra"<<endl;
                cin>>op;
                if(op=='1'){
                    op='2';
                }else{
                    if(op=='2'){
                        op='3';
                    }else{
                        op='?'; // asi detecta error
                        cout<<"Ingrese una opcion valida"<<endl;
                    }
                }
            }while(op!='2' && op!='3');
        }
        switch (op){
        case '1':
            cout << "Ingrese la letra: ";
            cin >> letra;
            probar_letra(p.palabra, letra,renglon,letrasadiv);
            if(letrasadiv==strlen(p.palabra)){
                strcpy(renglon,p.palabra);
                puntos=puntos-pnegativo+ppletra*strlen(p.palabra);  // en el caso de adivinar se le suma toda la palabra y se le restan las pistas
                adivinado=true;
            }
            intentos--;
            break;
        case '2':
            do{
                cout << "Que pista desea elegir?" << endl;
                cout << "1. Primera letra de la palabra -5pts" << endl;
                cout << "2. Definicion de la palabra -10pts" << endl;
                cin >> op;
                if (op != '1' && op != '2'){
                    cout << "Ingrese una opcion valida" << endl;
                }
            } while (op != '1' && op != '2');
            if (op == '1'){
                renglon[0]=p.palabra[0];
                pnegativo = pnegativo + 5;
            }else{
                cout<<p.definicion<<endl;
                pnegativo = pnegativo + 10;
                system("pause");
            }
            break;
        case '3':
            cout << "Introduzca la palabra: ";
            fflush(stdin);
            gets(intento);
            adivinado = arriesgar_palabra(p.palabra, intento);
            if (adivinado == true){
                strcpy(renglon,p.palabra);
                puntos=puntos-pnegativo+ppletra*strlen(p.palabra); // en el caso de adivinar se le suma toda la palabra y se le restan las pistas
            }else{
                cout<<"No es la palabra buscada"<<endl;
            }
            intentos--;
            break;
        default:
            cout<<"Ingrese una opcion correcta"<<endl;
            break;
        } 
        system("cls");
    }
    if(adivinado){
        cout<<"Si!!, la palabra era: "<<p.palabra<<endl;
        cout<<"Termina palabra con: "<<puntos<<" puntos"<<endl;
    }else{
        puntos=(letrasadiv*ppletra)+puntosaux-pnegativo;  // en el caso de no adivinar, solo se suman las letras y se le resta el valor de las pistas
        cout<<"Termina palabra con: "<<puntos<<" puntos"<<endl;
        cout<<"Lo siento no logro adivinar la palabra, la palabra era: "<<p.palabra<<endl;
    }
    system("pause");system("cls");
}
void submenu_jugar(pnodo p1,pnodo p2,tjugador jug1,tjugador jug2){
    int i=0,puntos1=0,puntos2=0,cantadiv1=0,cantadiv2=0;
    bool adivinado;
    pnodo aux;
    tcad intento;
    do{
        system("cls");
        adivinado=false;
        turno(p1->palabra,jug1,puntos1,adivinado); // juega jug1
        if(adivinado){
            cantadiv1++; // Esto es para controlar si adivino la palabra
        }
        aux=quitar_inicio(p1);
        delete(aux);
        system("cls");
        adivinado=false;
        turno(p2->palabra,jug2,puntos2,adivinado); // juega jug2
        if(adivinado){
            cantadiv2++;
        }
        aux=quitar_inicio(p2);
        delete(aux);
        i++;
    }while(i<3);
    if(cantadiv1>0 || cantadiv2>0){
        if(cantadiv1==3){
            puntos1=puntos1+15;
        }
        if(cantadiv2==3){
            puntos2=puntos2+15;
        }
        if(puntos1>puntos2){
            cout<<"GANO EL JUGADOR 1 !!!"<<endl;
            if(jug1.puntaje<puntos1){
                modificar_pjugador(jug1.nickname,puntos1); // aca añadimos una win y ademas cargamos el nuevo puntaje maximo
            }else{
                modificar_pjugador(jug1.nickname,jug1.puntaje); // aca solo añadimos una win y dejamos el anterior puntaje maximo
            }
        }else{
            if(puntos1<puntos2){
                cout<<"GANO EL JUGADOR 2 !!!"<<endl;
                if(jug2.puntaje<puntos2){
                    modificar_pjugador(jug2.nickname,puntos2); // aca añadimos una win y ademas cargamos el nuevo puntaje maximo
                }else{
                    modificar_pjugador(jug2.nickname,jug2.puntaje); // aca solo añadimos una win y dejamos el anterior puntaje maximo
                }
            }else{
                cout<<"EMPATE!"<<endl;
            }
        }
    }else{
        cout<<"No hubo ganadores, ninguno adivino una palabra"<<endl;
    }
    
    system("pause");
}
void main_jugar(){
    int nivel=0; // Con esto controlo que se pueda jugar
    char op;
    tcad vacio="";
    tjugador jug1,jug2;
    pnodo p1,p2;
    jug1.id_jugador=0;  // Inicializado para controlarlo
    jug2.id_jugador=0;  // Inicializado para controlarlo
	strcpy(jug1.nickname,""); // Utilizo la funcion strcpy para asignar un valor vacio
	strcpy(jug2.nickname,""); // Utilizo la funcion strcpy para asignar un valor vacio
    do{
        system("cls");
		cout<<"====== MENU PARTIDA ======"<<endl;
		cout<<"Jugador 1: "<<jug1.nickname << " - Jugador 2: "<<jug2.nickname<<"  Nivel:"<<nivel<<endl;
        menu_jugar();
        cin>>op;
        op=tolower(op);
        switch(op){
            case 'a':
                elegir_jugadores(jug1,jug2);
            break;
            case 'b':
                do{
                    cout<<"Que nivel desea elegir?"<<endl;
                    cout<<"1. 4 Caracteres"<<endl;
                    cout<<"2. 6 Caracteres"<<endl;
                    cout<<"3. 8 o mas Caracteres"<<endl;
                    cin>>nivel;
                    if(nivel!=1 && nivel !=2 && nivel !=3){
                        cout<<"Introduzca un nivel valido"<<endl;
                    }
                }while(nivel!=1 && nivel !=2 && nivel !=3);
                cargar_palabras(p1,p2,nivel);
                if(p1==NULL){
                    cout<<"ERROR"<<endl;
                    nivel=0;
                    system("pause");
                }
            break;
            case 'c':
                if(nivel!=0 && jug1.id_jugador!=0 && jug2.id_jugador!=0){
                    submenu_jugar(p1,p2,jug1,jug2);
                }else{
                    if(nivel==0 && (jug1.id_jugador==0 || jug2.id_jugador==0)){
                        cout<<"Debe elegir el nivel y elegir los jugadores antes de iniciar"<<endl;
                    }else{
                        if(nivel==0){
                            cout<<"Debe elegir el nivel antes de iniciar"<<endl;
                        }else{
                            cout<<"Debe elegir ambos jugadores antes de iniciar"<<endl;
                        }
                    }
                    system("pause");
                }
            break;
            case 'd':
                cout<<"Saliendo de Jugar"<<endl;
            break;

        }

    }while(op!='d');
}
