/*
 * Servicios.h
 *
 *  Created on: 20 jun. 2022
 *      Author: Silvera Micaela
 */
#include "LinkedList.h"

#ifndef ESERVICIOS_H_
#define ESERVICIOS_H_

#define TAM 50


typedef struct {
	int id_servicios;
	char descripcion[TAM];
	int tipo;
	float precioUnitario;
	int cantidad;
	int totalServicio;
}eServicios;


struct eServicios* cargaServios(int idNuevoServicio);

#endif /* ESERVICIOS_H_ */

int eServicio_getTipo(eServicios* this);
///
int eServicio_getDescripcion(eServicios* this,char* descripcion);
///
void  mostrarListaServicios(LinkedList* listaServicios);
///
int obtenerTipoServicioPorTexto(char* texto);
///
char* obtenerTipoServicioPorEntero(int numero);
///
int eServicio_sortByDescripcion(void* servicioUno, void* servicioDos );
///
int eServicio_FilterByMinorista(void* servicio );
///
int eServicio_FilterByMayorista(void* servicio );
///
int eServicio_FilterByExportar(void* servicio );
///
void eServicio_MapPrecioTotal(eServicios* servicio );

