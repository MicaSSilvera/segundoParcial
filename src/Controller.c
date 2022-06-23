/*
 * Controller.c
 *
 *  Created on: 21 jun. 2022
 *      Author: Silvera Micaela
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "eServicios.h"

/** \brief Carga los datos de los servicios desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListServicios LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListServicios)
{
	FILE* pArchivo;
	char *texto = NULL,
	delimitador[] = ",";
	size_t len = 0;

	int countLinea = 0;
	int countAtributos = 0;

	pArchivo = fopen(path, "r");

	if(pArchivo != NULL){

		while (getline(&texto, &len, pArchivo) != -1){

			char* token = strtok(texto, delimitador);
			//printf("LINEA: %s \n", token);
			if(countLinea > 0 ){

				eServicios* servicioNuevo;

				servicioNuevo = (eServicios*) malloc(sizeof(eServicios)); // declaro memoria dinámica

				if(token != NULL){
					//printf("TOKEN: %s \n", token);
					while(token != NULL){
						// Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL

						switch(countAtributos){
							case 0:
								servicioNuevo->id_servicios = atoi(token);
								break;
							case 1:
								strcpy(servicioNuevo->descripcion, token);
								break;
							case 2:
								servicioNuevo->tipo = atoi(token);
								break;
							case 3:
								servicioNuevo->precioUnitario = atoi(token);
								break;
							case 4:
								servicioNuevo->cantidad = atoi(token);
								break;
							case 5:
								servicioNuevo->totalServicio = atoi(token);
								break;
						}//FIN SWITCH

						countAtributos++;

						token = strtok(NULL, delimitador);
					}//FIN WHILE

					//llamo a la funcion ll_add() para agregar un elemento al final de LinkedList
					ll_add(pArrayListServicios, servicioNuevo);

					countAtributos = 0;
				}//FIN IF

			}//FIN IF
			countLinea++;

		}//FIN WHILE

	}else{
		return 0;
	}//FIN IF


	fclose(pArchivo);
	free(texto);

    return 1;
}

/** \brief Guarda los datos de los servicios en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListServicios LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListServicios)
{

	int size = 0;

	FILE* pArchivo;

	pArchivo = fopen(path, "w" );
	/*
	if(pArchivo == NULL){

		printf("\n Error de apertura :s");

		exit(1);

	}//fin if*/

	//llamo a la funcion ll_len() para que retorne el tamaño del LinkedList.
	 size = ll_len(pArrayListServicios);

	 eServicios* servicioLista;

	 servicioLista = (eServicios*) malloc(sizeof(eServicios)); // declaro memoria dinámica

	 fprintf(pArchivo, "id_servicios,descripcion,tipo,precioUnitario,cantidad,totalServicio\n");

	 for(int i = 0; i<size ;i++){

		//llamo a la funcion ll_get() que le paso un lista para que retorne el indice de un pasajero
		servicioLista = ll_get(pArrayListServicios, i);

		fprintf(pArchivo, "%d,", servicioLista->id_servicios);

		fprintf(pArchivo, "%s,", servicioLista->descripcion);

		fprintf(pArchivo, "%d,", servicioLista->tipo);

		fprintf(pArchivo, "%.2f,", servicioLista->precioUnitario);

		fprintf(pArchivo, "%d,", servicioLista->cantidad);

		fprintf(pArchivo, "%d\n", servicioLista->totalServicio);

	 }//fin for

	fclose(pArchivo);

    return 1;
}
