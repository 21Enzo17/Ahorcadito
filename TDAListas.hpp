// Definicion compartida
#include <iostream>
using namespace std;
typedef struct tnodo *pnodo;
typedef struct tnodo{
	tpalabra palabra;
	pnodo sig;
};
void crear_nodo(pnodo &nuevo,tpalabra nueva){
	nuevo=new tnodo;
	if(nuevo!=NULL){
		nuevo->palabra=nueva;
		nuevo->sig=NULL;
	}else{
		cout<<"Memoria Insuficiente"<<endl;
	}
}
// Operacion compartida entre lista simple y circular
void iniciar_lista(pnodo &lista){
	lista=NULL;
}
// Operaciones Listas Simples  /////////////////////////////////////////////////////

bool buscar_nodo(pnodo lista, tpalabra palabra)	
	{ pnodo i;
	bool encontrado=false;
	if (lista!=NULL)
		for(i=lista;i!=NULL && encontrado==false;i=i->sig)
		if (i->palabra.id_palabra==palabra.id_palabra)
			encontrado=true;
	return encontrado;
}
void mostrar(pnodo lista)
{ 	pnodo i;
	if (lista!=NULL)
		for(i=lista;i!=NULL;i=i->sig)
		cout << "Palabra: " << i->palabra.palabra << " ID: "<<i->palabra.id_palabra << endl;
	else
		cout << "LISTA VACIA";
}

pnodo quitar_nodo(pnodo &lista,tpalabra buscada)
	{ pnodo extraido,i;
	if (lista==NULL)
		extraido=NULL;
	else
		if (lista->palabra.id_palabra==buscada.id_palabra)
	{extraido=lista;
	lista=extraido->sig;
	extraido->sig=NULL; 
	}else{
			for(i=lista;i->sig!=NULL && buscada.id_palabra!=(i->sig)->palabra.id_palabra;i=i->sig);
			if (i->sig!=NULL){
				extraido=i->sig;
				i->sig=extraido->sig;
				extraido->sig=NULL; 
			}else
				extraido=NULL; 
		}
	return extraido;
}
pnodo quitar_final(pnodo &lista)
{ 	pnodo extraido,i;
	if (lista==NULL){
		extraido=NULL;
	}else{
		if (lista->sig==NULL){
			extraido=lista;
			lista=NULL; 
		}else{
			for(i=lista;(i->sig)->sig!=NULL;i=i->sig);
			extraido=i->sig;
			i->sig=NULL; 
		}
	}
	return extraido;
}
pnodo quitar_inicio(pnodo &lista){
	pnodo extraido;
	if(lista==NULL){
		extraido=NULL;
	}else{
		extraido=lista;
		lista=extraido->sig;
		extraido->sig=NULL;
	}
	return extraido;
}
void agregar_final(pnodo &lista,pnodo nuevo){
	pnodo i;
	if(lista==NULL){
		lista=nuevo;
	}else{
		for(i=lista;i->sig!=NULL;i=i->sig);
		i->sig=nuevo;
	}
}
	void liberar(pnodo &lista){
		pnodo liberado;
		while(lista!=NULL){
			liberado=quitar_inicio(lista);
			delete(liberado);
		}
		cout<<"Memoria liberada"<<endl;
	}
void agregar_inicio(pnodo &lista,pnodo nuevo){
	nuevo->sig=lista;
	lista=nuevo;
	}
	
// Operaciones Listas Circulares ///////////////////////////////////////////////////////


void mostrar_circ(pnodo lista) // Solo queda como prueba
{ 	
	pnodo i;
	if (lista!=NULL){
		cout << "Palabra: " << lista->palabra.palabra <<" ID: "<< lista->palabra.id_palabra<< endl;
		for(i=lista->sig;i!=lista;i=i->sig)
		cout << "Palabra: " << i->palabra.palabra <<" ID: "<< i->palabra.id_palabra<< endl;
	}else{
		cout << "LISTA VACIA"<<endl;
	}
}

bool buscar_nodo_circ(pnodo lista, int valor)	// el valor a buscar sera la id
	{ pnodo i;
	bool encontrado=false;
	if (lista!=NULL)
		for(i=lista;i!=NULL && encontrado==false;i=i->sig)
		if (i->palabra.id_palabra==valor)
			encontrado=true;
	return encontrado;
}
pnodo quitar_nodo_circ(pnodo &lista,int valor)
{ pnodo extraido,i;
	if (lista==NULL){
		extraido=NULL;
	}else{
		if(lista->palabra.id_palabra==valor && lista->sig==lista){
			extraido=lista;
			lista=NULL;
		}else{
			if (lista->palabra.id_palabra==valor){
				for(i=lista;i->sig!=lista;i=i->sig);
				i->sig=lista->sig;
				extraido=lista;
				lista=extraido->sig;
				extraido->sig=NULL; 
			}else{
				for(i=lista;i->sig!=lista && valor!=(i->sig)->palabra.id_palabra;i=i->sig);
				if ((i->sig)->palabra.id_palabra==valor){
					extraido=i->sig;
					i->sig=extraido->sig;
					extraido->sig=NULL;
				}else
					cout<<"Aca"<<endl;
					extraido=NULL; 
				}
			}
		}

	return extraido;
}
pnodo quitar_final_circ(pnodo &lista)
{ 	pnodo extraido,i;
	if (lista==NULL){
		extraido=NULL;
	}else{
		if (lista->sig==NULL){
			extraido=lista;
			lista=NULL; 
		}else{
			for(i=lista;(i->sig)->sig!=NULL;i=i->sig);
			extraido=i->sig;
			i->sig=NULL; 
		}
	}
	return extraido;
}
pnodo quitar_inicio_circ(pnodo &lista){
	pnodo extraido;
	if(lista==NULL){
		extraido=NULL;
	}else{
		extraido=lista;
		lista=extraido->sig;
		extraido->sig=NULL;
	}
	return extraido;
}
	void liberar_circ(pnodo &lista){
		pnodo liberado;
		while(lista!=NULL){
			liberado=quitar_inicio_circ(lista);
			delete(liberado);
		}
		cout<<"Memoria liberada"<<endl;
	}
void agregar_final_circ(pnodo &lista,pnodo nuevo){
	pnodo i;
	if(lista==NULL){
		lista=nuevo;
		nuevo->sig=lista;
	}else{
		for(i=lista;i->sig!=lista;i=i->sig);
		i->sig=nuevo;
		nuevo->sig=lista;
	}
}
void agregar_inicio_circ(pnodo &lista,pnodo nuevo){
	pnodo i;
	if(lista==NULL){
		lista=nuevo;
		nuevo->sig=lista;
	}else{
		for(i=lista;i->sig!=lista;i=i->sig);
		nuevo->sig=lista;
		i->sig=nuevo;
		lista=nuevo;
		
	}
}
