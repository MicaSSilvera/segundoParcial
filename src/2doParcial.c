/*
 ============================================================================
 Name        : SegundoParcial.c
 Author      : Silvera Micaela
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

#include "eServicios.h"
#include "LinkedList.h"
#include "Controller.h"

#define MENSAJES 100

int main(void) {
	setbuf(stdout,NULL);

	int opcion = 0;
	int size;
	int sizeFilter;
	int opcionServicio = 0;

	LinkedList* listaServicios = ll_newLinkedList();

	while(opcion != 9  ){

		mostrarMenu();

		char mensaje[MENSAJES];
		memcpy(&mensaje, "\nIngrese una opcion [ 1-2-3-4-5-6-7 ]: ", MENSAJES);
		opcion = validarEntero(mensaje);

		clearConsole();

		switch(opcion){

			case 1:// CARGAR ARCHIVOS
				//
				 if(controller_loadFromText("serviciosPrecioTotal.csv", listaServicios) == 1){

					 //llamo a la funcion ll_len() para que retorne el tamaño del LinkedList.
					 size = ll_len(listaServicios);

					 printf("SE CARGO LA LISTA DE SERVICIOS EXITOSAMENTE :D");
				 }else{
					 printf("SURGIO UN ERROR AL INTENTAR CARGAR LA LISTA DE SERVICIOS  :/");
				 }
				 clearConsole();
				break;

			case 2:// IMPRIMIR LISTA

				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

					//llamo a la funcion mostrarListaServicios() para que muestre todos los datos de los servicios ingresados
					mostrarListaServicios(listaServicios);
				}else{
					printf("NO HAY NINGUN SERVICIO CARGADO EN LA LISTA  :(");
				}
				clearConsole();
				break;

			case 3://ASIGNAR TOTALES

				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

					//llamo a la funcion ll_map() que recibirá una lista y una función y le calculará el totalServicio
					listaServicios = ll_map(listaServicios, eServicio_MapPrecioTotal);

					//llamo a la funcion mostrarListaServicios() para que muestre todos los datos de los servicios ingresados.
					mostrarListaServicios(listaServicios);
				}//fin if
				 clearConsole();
				break;

			case 4:// FILTRAR POR TIPO
				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

					char mensaje[MENSAJES];
					memcpy(&mensaje, "SELECCIONE POR QUE TIPO DESEA FILTRAR:\n 1. MINORISTA \n 2. MAYORISTA \n 3. EXPORTAR \n: ", MENSAJES);
					opcionServicio = validarEntero(mensaje);

					LinkedList* listaServiciosFiltrada;
					char* nombreArchivo;

					switch (opcionServicio){

						case 1://MINORISTA
							//llamo a la funcion ll_filter() para que me permita filtar los elementos de la opcion seleccionada.
							listaServiciosFiltrada = ll_filter(listaServicios, eServicio_FilterByMinorista);
							strcpy(nombreArchivo, "serviciosMinoristas.csv");
							break;
						case 2://MAYORISTA
							//llamo a la funcion ll_filter() para que me permita filtar los elementos de la opcion seleccionada
							listaServiciosFiltrada = ll_filter(listaServicios, eServicio_FilterByMayorista);
							strcpy(nombreArchivo, "serviciosMayoristas.csv");
							break;
						case 3://EXPORTAR
							//llamo a la funcion ll_filter() para que me permita filtar los elementos de la opcion seleccionada
							listaServiciosFiltrada = ll_filter(listaServicios, eServicio_FilterByExportar);
							strcpy(nombreArchivo, "serviciosExportar.csv");
							break;
						default:
							printf("LA OPCION INGRESADA ES INCORRECTA  :/");
							break;
					}//fin switch

					//llamo a la funcion ll_len() para que retorne el tamaño del LinkedList.
					sizeFilter = ll_len(listaServiciosFiltrada);

					//si la lista esta cargada la muestro por consola y la guardo en un archivo de texto.
					if(sizeFilter > 0 ){
						//llamo a la funcion mostrarListaServicios() para que muestre todos los datos de los servicios ingresados.
						mostrarListaServicios(listaServiciosFiltrada);

						//llamo a la funcion que me guarde el archivo de texto con los servicios filtrados.
						controller_saveAsText(nombreArchivo, listaServiciosFiltrada);
						printf("\nSE GUARDO LA LISTA DE SERVICIOS EXITOSAMENTE :D");

					}//fin if
				}else{
					printf("NO HAY NINGUN SERVICIO CARGADO EN LA LISTA  :(");
				}
				clearConsole();
				break;

			case 5://MOSTRAR SERVICIOS ORDENADOS
				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

					//llamo a la funcion ll_sort() para que se genere el ordenamiento ascendente (1).
					if(ll_sort(listaServicios, eServicio_sortByDescripcion, 1) > -1){

						//llamo a la funcion mostrarListaServicios() para que muestre todos los datos de los servicios ingresados.
						mostrarListaServicios(listaServicios);
					}else {
						printf("OCURRIO UN ERROR AL INTENTAR ORDENAR LA LISTA :(");
					}

				}else{
					printf("NO HAY NINGUN SERVICIO CARGADO EN LA LISTA  :(");
				}
				clearConsole();
				break;

			case 6:// GUARDAR SERVICIOS
				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

					controller_saveAsText("listaServicios.csv", listaServicios);
					printf("SE GUARDO LA LISTA DE SERVICIOS EXITOSAMENTE :D");
				}else{
					printf("NO HAY NINGUN SERVICIO CARGADO EN LA LISTA  :(");
				}
				clearConsole();
				break;

			case 7:

				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

				LinkedList* listaServiciosFiltradaPrecioTotal;

					listaServiciosFiltradaPrecioTotal = ll_filter(listaServicios, eServicio_FilterByPrecioTotal);

					controller_saveAsText("serviciosPrecioTotal.csv", listaServiciosFiltradaPrecioTotal);
					printf("SE GUARDO LA LISTA DE SERVICIOS EXITOSAMENTE :D");
				}else{
					printf("NO HAY NINGUN SERVICIO CARGADO EN LA LISTA  :(");
				}
				clearConsole();


				break;
			case 8:
				//llamo a la funcion ll_isEmpty() para que me indique si la LinkedList esta vacia o no.
				//si la lista esta vacia. muestra un mensaje de error.
				if(ll_isEmpty(listaServicios) == 0){

					//llamo a la funcion ll_map() que recibirá una lista y una función y le calculará el totalServicio
					listaServicios = ll_map(listaServicios, eServicio_MapDescuento);

					//llamo a la funcion mostrarListaServicios() para que muestre todos los datos de los servicios ingresados.
					mostrarListaServicios(listaServicios);
				}//fin if
				 clearConsole();
				break;

			case 9://salir
				printf("SALIENDO ;)");
				clearConsole();
				break;

			default:
				printf("LA OPCION INGRESADA ES INCORRECTA  :/");
				clearConsole();
				break;

		}// fin switch

	}//fin while

	return EXIT_SUCCESS;
}// fin main



