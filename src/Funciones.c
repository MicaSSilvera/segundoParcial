/*
 * Funciones.c
 *
 *  Created on: 20 jun. 2022
 *      Author: Silvera Micaela
 */


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#include "Funciones.h"

void mostrarMenu (){

	printf("\n 1) CARGAR SERVICIOS");
	printf("\n 2) IMPRIMIR LISTADO DE SERVICIOS");
	printf("\n 3) ASIGNAR TOTALES");
	printf("\n 4) FILTRAR SERVICIOS POR TIPO");
	printf("\n 5) MOSTRAR SERVICIOS ORDENADOS ALFABETICAMENTE");
	printf("\n 6) GUARDAR SERVICIOS");
	printf("\n 7) FILTRAR EL PRECIO TOTAL");
	printf("\n 8) APLICAR DESCUENTO");
	printf("\n 9) SALIR");

	return;
}//fin mostrarMenu
///
void clearConsole(){
	printf("\n");
	printf("\n");

	return;
}//FIN clearConsole()
///
int esEntero(char linea[]) {
	int esEntero = 1;
	int longitud = strlen(linea);

	if (longitud == 0) {
		esEntero = 0;
	} else if (longitud == 1 && !isdigit(linea[0])) {
		esEntero = 0;
	} else {
		int indice = 0;

		if (linea[0] == '+' || linea[0] == '-') {
			indice = 1;
		} else {
			indice = 0;
		}//FIN IF

		while (indice < longitud) {

			if (!isdigit(linea[indice])) {
				esEntero = 0;
				break;
			}//FIN IF

			indice++;
		}//FIN WHILE
	}//FIN IF

	return esEntero;
}//FIN esEntero()
///
int validarEntero(char mensaje[]){
	int numero = 0;

	char linea[50];
	int repite = 1;

	do {
		printf("\n %s ", mensaje);
		scanf ("%s", &linea);
		fflush(stdin);

		if (esEntero(linea)) {
			repite = 0;
		} else {
			printf("\nNo has ingresado un valor entero. Intentalo nuevamente\n");
		}
		fflush(stdin);
	} while (repite);

	numero = atoi(linea);

	return numero;
}//FIN validarEntero()
///

