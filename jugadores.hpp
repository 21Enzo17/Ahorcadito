#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
typedef FILE *parchivo;
typedef char tcad[100];
typedef struct tjugador
{
    int id_jugador, puntaje, wins;
    tcad apellido, nombre, nickname;
};
#include "TDA Arbol.hpp"
void menu_jugadores()
{
    cout<<"***** MENU JUGADORES *****"<<endl;
    cout<<"1- Agregar Jugador"<<endl;
    cout<<"2- Consultar un jugador"<<endl;   // Deberia consultar por nickname, o por ID, creo que por nickname
    cout<<"3- Modificar un jugador"<<endl;
    cout<<"4- Listar jugadores"<<endl;
    cout<<"5- Eliminar un jugador"<<endl;
    cout<<"6- Salir"<<endl;
    cout<<"Su eleccion: ";
}
void crear_jugador(tjugador &jugador){
    cout<<"Ingrese el nombre del jugador: ";
    fflush(stdin);
    gets(jugador.nombre);
    cout<<"Ingrese el apellido del jugador: ";
    fflush(stdin);
    gets(jugador.apellido);
    cout<<"Ingrese el nickname: ";
    fflush(stdin);
    gets(jugador.nickname);
    jugador.puntaje=0;
    jugador.wins=0;

}
void Cargar_Jugador(parchivo f)
{ 
    tjugador nuevo, aux;
    bool existe = false,id;
    crear_jugador(nuevo);
    f = fopen("Jugadores.txt", "ab+");
    if (f != NULL)
    {
        while (!feof(f))
        {
            fread(&aux, sizeof(aux), 1, f);
            if (strcmp(aux.nickname,nuevo.nickname)==0)
                existe = true;
            id=true;
        }
        if (!existe)
        {
            nuevo.id_jugador=aux.id_jugador+1;  // En el caso de que si haya valores se le asigna el anterior mas 1  
            fwrite(&nuevo, sizeof(nuevo), 1, f);
        }
        else
        {
            cout << "-ERROR- Ya existe un jugador con ese nickname" << endl;
        }
        fclose(f);
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
}
void mostrar_jugadores(parchivo f)
{
    tjugador n;
    cout<<"MOSTRANDO DATOS" << endl;
    f = fopen("Jugadores.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f))
        {
            fread(&n, sizeof(n), 1, f);
            if (!feof(f))
            {
                cout << "==========================" << endl;
                cout << "ID                       |" << n.id_jugador << endl;
                cout << "Apellido y Nombre        |" << n.apellido << " " << n.nombre << endl;
                cout << "Nickname                 |" << n.nickname << endl;
                cout << "Puntaje                  |" << n.puntaje << endl;
                cout << "Wins                     |" << n.wins << endl;
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
void consulta(parchivo f, tcad nickname)
{
    tjugador n;
    bool encontrado = false;
    f = fopen("Jugadores.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f) && !encontrado)
        {
            fread(&n, sizeof(n), 1, f);
            if (strcmp(n.nickname,nickname)== 0 && !feof(f))
            {
                cout << "==========================" << endl;
                cout << "ID                       |" << n.id_jugador << endl;
                cout << "Apellido y Nombre        |" << n.apellido << " " << n.nombre << endl;
                cout << "Nickname                 |" << n.nickname << endl;
                cout << "Puntaje                  |" << n.puntaje << endl;
                cout << "Wins                     |" << n.puntaje << endl;
                cout << "==========================" << endl;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se encontro el nickname" << endl;
        }
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
    fclose(f);
}
bool jugador_repetido(tjugador jugador){
	parchivo f;
    tjugador aux;
    bool existe = false,id;
	f = fopen("Jugadores.txt", "rb");
	if (f != NULL)
	{
		while (!feof(f))
		{
			fread(&aux, sizeof(aux), 1, f);
			if (strcmp(aux.nickname,jugador.nickname)== 0 && aux.id_jugador != jugador.id_jugador)  // Aqui analizo si algun jugador tiene un nickname igual, y en caso de tenerlo, que tenga distinto id
				existe = true;
		}
	}
    fclose(f);
	return existe;
}
void modificacion_jugador(tjugador &n)
{   int opc;
    bool encontrado = false;
    do
    {
        cout << "Que campos desea modificar? (Una a la vez)" << endl;
        cout << "1- Apellido y Nombre" << endl;
        cout << "2- Nickname" << endl;
        cout << "3- Salir..."<<endl;
        // En este caso no permito modificar el id ni las wins ni puntos por obvias razones, ademas modificar el id podria generar jugadores con mismos id
        cin >> opc;
        switch (opc)
        {
        case 1:
            cout << "Introduzca el Apellido: ";
            fflush(stdin);
            gets(n.apellido);
            cout << "Introduzca el Nombre: ";
            fflush(stdin);
            gets(n.nombre);
            break;
        case 2:
            cout << "Introduzca el nickname: ";
            fflush(stdin);
            gets(n.nickname);
            break;
        case 3:
                cout << "==========================" << endl;
                cout << "ID                       |" << n.id_jugador << endl;
                cout << "Apellido y Nombre        |" << n.apellido << " " << n.nombre << endl;
                cout << "Nickname                 |" << n.nickname << endl;
                cout << "Puntaje                  |" << n.puntaje << endl;
                cout << "Wins                     |" << n.wins << endl;
                cout << "==========================" << endl;
                encontrado=jugador_repetido(n);
                if(encontrado==true){
                    cout<<"Este nickname ya existe, ingrese otro nuevo"<<endl;
                }
            break;
        default:
            cout << "Ingrese una opcion correcta" << endl;
            break;
        }
    } while (opc != 3 && encontrado == false);
}
void modificar_jugador(parchivo f,tcad nickname){ 
    tjugador n;
    bool encontrado = false;
    f = fopen("Jugadores.txt", "rb+");
    if (f != NULL)
    {
        while (!feof(f) && !encontrado)
        {
            fread(&n, sizeof(n), 1, f);
            if (strcmp(n.nickname,nickname)==0 && !feof(f))
            {
                modificacion_jugador(n);
                fseek(f,-sizeof(n),1);
                fwrite(&n,sizeof(n),1,f);
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se encontro el nickname "<< endl;
        }
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
    fclose(f);
}
void modificar_pjugador(tcad nickname,int puntaje){ // algoritmo para modificar puntaje y wins
    parchivo f;
    tjugador n;
    bool encontrado = false;
    f = fopen("Jugadores.txt", "rb+");
    if (f != NULL)
    {
        while (!feof(f) && !encontrado)
        {
            fread(&n, sizeof(n), 1, f);
            if (strcmp(n.nickname,nickname)==0 && !feof(f))
            {
                n.puntaje=puntaje;
                n.wins++;
                fseek(f,-sizeof(n),1);
                fwrite(&n,sizeof(n),1,f);
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se encontro el nickname "<< endl;
        }
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
    fclose(f);
}
void baja_jugador(parchivo f,tcad nickname){
    tjugador n;
    parchivo aux;
    bool encontrado = false;
    f = fopen("Jugadores.txt", "rb+");
    aux= fopen("aux.txt","wb");
    if (f != NULL){
        while(!feof(f)){
            fread(&n,sizeof(n),1,f);
            if(strcmp(n.nickname,nickname)!=0 && !feof(f)){
                fwrite(&n,sizeof(n),1,aux);
            }
        }
    }else
    {
        cout << "Error al abrir el archivo" << endl;
    }
    fclose(aux);
    fclose(f);
    if(remove("Jugadores.txt")==0){
        cout<<"Eliminado correctamente"<<endl;
        if(rename("aux.txt","Jugadores.txt")){
            cout<<"Renombrado exitosamente"<<endl;
        }
    }else{
        cout<<"Error al Eliminar"<<endl;
    }

}
void main_jugadores(){
    int opc;
    tcad nickname;
    parchivo f;
    do{
        system("cls");
        menu_jugadores();
        cin>>opc;
        switch (opc){
            case 1:
                cout<<"***** CARGAR JUGADOR *****"<<endl;
                Cargar_Jugador(f);
            break;
            case 2:
                cout<<"***** CONSULTAR JUGADOR *****"<<endl;
                cout<<"Ingrese el nickname a buscar: ";
                fflush(stdin);
                gets(nickname);
                consulta(f,nickname);
            break;
            case 3:
                cout<<"***** MODIFICAR JUGADOR *****"<<endl;
                cout<<"Ingrese el nickname a modificar: ";
                fflush(stdin);
                gets(nickname);
                modificar_jugador(f,nickname);
            break;
            case 4:
                cout<<"***** LISTAR JUGADORES *****"<<endl;
                mostrar_jugadores(f);
            break;
            case 5:
                cout<<"***** ELIMINAR JUGADOR *****"<<endl;
                cout<<"Ingrese el nickname a eliminar: ";
                fflush(stdin);
                gets(nickname);
                baja_jugador(f,nickname);
            break;
            case 6:
                cout<<"***** SALIENDO JUGADORES *****"<<endl;
            break;
            
        }
        system("pause");
    }while(opc!=6);
}


// Elegir Jugador

tjugador elegir_jugador(tcad nickname)
{
    parchivo f;
    tjugador n,jugador;
    jugador.id_jugador=0;  // Inicializo en 0 en el caso de que el usuario no exista, tener un control
    bool encontrado = false;
    f = fopen("Jugadores.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f) && !encontrado)
        {
            fread(&n, sizeof(n), 1, f);
            if (strcmp(n.nickname,nickname)== 0 && !feof(f))
            {
                jugador=n;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se encontro el nickname" << endl;
        }
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
    fclose(f);
    return jugador;
}
void ranking_jugadores_puntos()
{
    parchivo f;
    parbol ranking,nuevo;
    iniciar_a(ranking);
    tjugador n;
    f = fopen("Jugadores.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f))
        {
            fread(&n, sizeof(n), 1, f);
            if (!feof(f) && n.puntaje>0)
            {
                crear_nodoA(nuevo,n);
                insertar_puntos(ranking,nuevo);
            }
        }
        cout<<"Puntos  | W | Jugador"<<endl;
        cout<<"----------------------"<<endl;
        may_men(ranking);
        cout<<endl;
        liberarA(ranking); // libero el arbol
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    fclose(f);
}
void ranking_jugadores_wins()
{
    parchivo f;
    parbol ranking,nuevo;
    iniciar_a(ranking);
    tjugador n;
    f = fopen("Jugadores.txt", "rb");
    if (f != NULL)
    {
        while (!feof(f))
        {
            fread(&n, sizeof(n), 1, f);
            if (!feof(f) && n.puntaje>0)
            {
                crear_nodoA(nuevo,n);
                insertar_wins(ranking,nuevo);
            }
        }
        cout<<"Puntos  | W | Jugador"<<endl;
        cout<<"----------------------"<<endl;
        may_men(ranking);
        cout<<endl;
        liberarA(ranking); // libero el arbol
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    fclose(f);
}