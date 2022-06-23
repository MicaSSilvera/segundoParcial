/*
 * Servicios.c
 *
 *  Created on: 20 jun. 2022
 *      Author: Silvera Micaela
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "eServicios.h"

#define TAM 50

void  mostrarListaServicios(LinkedList* listaServicios){
	int size = 0;

	//llamo a la funcion ll_len() para que retorne el tamaño del LinkedList.
	 size = ll_len(listaServicios);

	 eServicios* servicioLista;

	 servicioLista = (eServicios*) malloc(sizeof(eServicios)); // declaro memoria dinámica

	 for(int i = 0; i<size ;i++){

		//llamo a la funcion ll_get() que le paso un lista para que retorne el indice de un pasajero
		servicioLista = ll_get(listaServicios, i);

		printf("\n *************************");

		printf("\n ID : %d", servicioLista->id_servicios);

		printf("\n DESCRIPCION : %s",servicioLista->descripcion );

		printf("\n TIPO DE SERVICIO : %d [ %s ]",servicioLista->tipo, obtenerTipoServicioPorEntero(servicioLista->tipo) );

		printf("\n PRECIO UNITARIO : %.2f",servicioLista->precioUnitario);

		printf("\n CANTIDAD : %d",servicioLista->cantidad );

		printf("\n TOTAL : %d",servicioLista->totalServicio );

		printf("\n *************************");

	 }//fin for


}//fin funcion mostrarListaServicios
///
char* obtenerTipoServicioPorEntero(int numero){

	char *tipoServicio = malloc(14);

	if(numero == 1){
		strcpy(tipoServicio, "MINORISTA");
	}else if (numero == 2){
		strcpy(tipoServicio, "MAYORISTA");
	}else if (numero == 3){
		strcpy(tipoServicio, "EXPORTAR");
	}//FIN IF

	return tipoServicio;
}// FIN obtenerTipoPasajero*/
///
int obtenerTipoServicioPorTexto(char* texto){

	const char* str1 = "MINORISTA";
	const char* str2 = "MAYORISTA";
	const char* str3 = "EXPORTAR";

	int tipoServicio = 0;

	if(strcmp(texto, str1) == 0){
		tipoServicio = 1;
	}else if (strcmp(texto, str2) == 0){
		tipoServicio = 2;
	}else if (strcmp(texto, str3) == 0){
		tipoServicio = 3;
	}//FIN IF

	return tipoServicio;
}// FIN obtenerTipoPasajero
///
int eServicio_sortByDescripcion(void* servicioUno, void* servicioDos ){

	int retorno = -1;
	char descripcionAuxUno[TAM];
	char descripcionAuxDos[TAM];

	if(servicioUno != NULL && servicioDos != NULL){

		if(eServicio_getDescripcion(servicioUno, descripcionAuxUno) == 1){

			if(eServicio_getDescripcion(servicioDos, descripcionAuxDos) == 1){

				retorno = strcmp(descripcionAuxUno, descripcionAuxDos );

			}//fin if

		}//fin if

	}//fin if

	return retorno;

}//fin eServicio_sortByDescripcion

int eServicio_getDescripcion(eServicios* this,char* descripcion){

	strcpy(descripcion, this->descripcion);

	return 1;
}// fin eServicio_getDescripcion

int eServicio_getTipo(eServicios* this){

	int tipo = 0;

	tipo = this->tipo;

	return tipo;
}// fin eServicio_getDescripcion

int eServicio_FilterByMinorista(void* servicio ){

	int retorno = -1;
	int tipoAux;
	int tipoMinorista;
	const char* str1 = "MINORISTA";

	if(servicio != NULL){

		tipoAux = eServicio_getTipo(servicio);

		tipoMinorista = obtenerTipoServicioPorTexto(str1);

		if(tipoAux == tipoMinorista){
			retorno = 1;
		}else{
			retorno = 0;
		}//FIN if

	}//fin if

	return retorno;

}//fin eServicio_FilterByMinorista

int eServicio_FilterByMayorista(void* servicio ){

	int retorno = -1;
	int tipoAux;
	int tipoMayorista;
	const char* str1 = "MAYORISTA";

	if(servicio != NULL){

		tipoAux = eServicio_getTipo(servicio);

		tipoMayorista = obtenerTipoServicioPorTexto(str1);

		if(tipoAux == tipoMayorista){
			retorno = 1;
		}else{
			retorno = 0;
		}//FIN if

	}//fin if

	return retorno;

}//fin eServicio_FilterByMayorista

int eServicio_FilterByExportar(void* servicio ){

	int retorno = -1;
	int tipoAux;
	int tipoExportar;
	const char* str1 = "EXPORTAR";

	if(servicio != NULL){

		tipoAux = eServicio_getTipo(servicio);

		tipoExportar = obtenerTipoServicioPorTexto(str1);

		if(tipoAux == tipoExportar){
			retorno = 1;
		}else{
			retorno = 0;
		}//FIN if

	}//fin if

	return retorno;

}//fin eServicio_FilterByExportar
///
void eServicio_MapPrecioTotal(eServicios* servicio ){

	if(servicio != NULL){

		servicio->totalServicio = servicio->precioUnitario * servicio->cantidad;

	}//fin if

	return;

}//fin eServicio_MapPrecioTotal
