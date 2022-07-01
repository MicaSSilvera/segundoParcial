/*
 * LinkedList.c
 *
 *  Created on: 21 jun. 2022
 *      Author: Silvera Micaela
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

static Node* getNode(LinkedList *this, int nodeIndex);
static int addNode(LinkedList *this, int nodeIndex, void *pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void) {
	LinkedList *this;
	this = (LinkedList*) malloc(sizeof(LinkedList));

	if (this != NULL) {
		this->size = 0;
		this->pFirstNode = NULL;

	}
	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList *this) {
	int returnAux = -1;

	if (this != NULL) {
		returnAux = this->size;
	}

	return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList *this, int nodeIndex) {
	Node *nodo = NULL;
	int length;
	int i;
	if (this != NULL) {
		length = ll_len(this);
		if (nodeIndex >= 0 && nodeIndex < length) {
			nodo = this->pFirstNode;
			if (nodeIndex != 0) {
				for (i = 1; i < length; i++) {
					nodo = nodo->pNextNode;
					if (i == nodeIndex) {
						break;
					}
				}
			}
		}
	}
	return nodo;

}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList *this, int nodeIndex) {
	return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList *this, int nodeIndex, void *pElement) {
	int returnAux = -1;
	Node *nodoNuevo;

	if (this != NULL) {
		int length = ll_len(this);

		if (nodeIndex >= 0 && nodeIndex <= length) {
			nodoNuevo = (Node*) malloc(sizeof(Node));
			nodoNuevo->pElement = pElement;
			nodoNuevo->pNextNode = NULL;
			if (nodoNuevo != NULL) {
				if (nodeIndex == 0) {
					nodoNuevo->pNextNode = this->pFirstNode;
					this->pFirstNode = nodoNuevo;
				} else {
					Node *nodoAnterior = getNode(this, nodeIndex - 1);
					nodoNuevo->pNextNode = nodoAnterior->pNextNode;
					nodoAnterior->pNextNode = nodoNuevo;
				}
				this->size = length + 1;
				returnAux = 0;
			}
		}
	}
	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList *this, int nodeIndex, void *pElement) {
	return addNode(this, nodeIndex, pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList *this, void *pElement) {
	int length;
	int returnAux = -1;

	if (this != NULL) {
		length = ll_len(this);
		addNode(this, length, pElement);
		returnAux = 0;
	}

	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList *this, int index) {
	Node *nodo;
	int length;
	void *returnAux = NULL;
	if (this != NULL) {
		length = ll_len(this);
		if (index >= 0 && index < length) {
			nodo = getNode(this, index);
			if (nodo != NULL) {
				returnAux = nodo->pElement;
			}
		}
	}
	return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList *this, int index, void *pElement) {
	Node *nodoModificado;
	int length;
	int returnAux = -1;
	if (this != NULL) {
		length = ll_len(this);
		if (index >= 0 && index < length) {
			nodoModificado = getNode(this, index);
			if (nodoModificado != NULL) {
				nodoModificado->pElement = pElement;
				returnAux = 0;
			}
		}
	}
	return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList *this, int index) {
	Node *nodoActual;
	Node *nodoAnterior;
	Node *nodoProximo;
	int length;
	int returnAux = -1;

	if (this != NULL) {
		length = ll_len(this);
		if (index >= 0 && index < length) {
			nodoActual = getNode(this, index);
			if (nodoActual != NULL) {
				nodoProximo = getNode(this, index + 1);
				if (index == 0) {
					this->pFirstNode = nodoProximo;
				} else {
					nodoAnterior = getNode(this, index - 1);
					if (nodoAnterior != NULL) {
						nodoAnterior->pNextNode = nodoProximo;
					}
				}
				this->size = length - 1;
				free(nodoActual);
				returnAux = 0;
			}

		}
	}
	return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList *this) {
	int i;
	int length;
	int retornoRemove;
	int returnAux = -1;

	if (this != NULL) {
		length = ll_len(this);

		for (i = 0; i < length; i++) {
			retornoRemove = ll_remove(this, i);

			if (retornoRemove == -1) {
				returnAux = -1;
				break;
			}
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList *this) {
	int returnAux = -1;

	if (this != NULL) {
		ll_clear(this);
		this->pFirstNode = NULL;
		free(this);
		returnAux = 0;

	}

	return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList *this, void *pElement) {
	Node *nodos;
	int length;
	int i;
	int returnAux = -1;

	if (this != NULL) {
		length = ll_len(this);
		nodos = this->pFirstNode;
		for (i = 0; i < length; i++) {
			if (nodos->pElement == pElement) {
				returnAux = i;
				break;
			}
			nodos = nodos->pNextNode;

		}

	}
	return returnAux;

}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si la lista NO esta vacia
 ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList *this) {
	int length;
	int returnAux = -1;
	if (this != NULL) {
		length = ll_len(this);
		if (length == 0) {
			returnAux = 1;
		} else {
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList *this, int index, void *pElement) {
	int returnAux = -1;
	Node *nodoNuevo;
	int length;
	if (this != NULL) {
		length = ll_len(this);

		if (index >= 0 && index <= length) {
			nodoNuevo = (Node*) malloc(sizeof(Node));
			nodoNuevo->pElement = pElement;
			nodoNuevo->pNextNode = NULL;
			if (nodoNuevo != NULL) {
				if (index == 0) {
					nodoNuevo->pNextNode = this->pFirstNode;
					this->pFirstNode = nodoNuevo;
				} else {
					Node *nodoAnterior = getNode(this, index - 1);
					nodoNuevo->pNextNode = nodoAnterior->pNextNode;
					nodoAnterior->pNextNode = nodoNuevo;
				}
				this->size = length + 1;
				returnAux = 0;
			}
		}
	}
	return returnAux;

}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList *this, int index) {
	void *nodoPop;
	int length;
	void *returnAux = NULL;

	if (this != NULL) {
		length = ll_len(this);
		if (index >= 0 && index <= length) {
			nodoPop = ll_get(this, index);
			ll_remove(this, index);
			returnAux = nodoPop;
		}
	}
	return returnAux;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 1) Si contiene el elemento
 ( 0) si No contiene el elemento
 */
int ll_contains(LinkedList *this, void *pElement) {
	int indice;
	int returnAux = -1;

	if (this != NULL) {
		indice = ll_indexOf(this, pElement);
		if (indice != -1) {
			returnAux = 1;
		} else {
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
 estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
 ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
 ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
 */
int ll_containsAll(LinkedList *this, LinkedList *this2) {
	void *indice;
	int indiceComparado;
	int length;
	int flagIndice = 0;
	int i;
	int returnAux = -1;
	if (this != NULL && this2 != NULL) {
		returnAux = 1;
		length = ll_len(this2);
		for (i = 0; i < length; i++) {
			indice = ll_get(this2, i);
			indiceComparado = ll_contains(this, indice);
			if (indiceComparado == 0) {
				flagIndice = 1;
			}
		}
		if (flagIndice == 1) {
			returnAux = 0;

		}
	}
	return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 o (si el indice from es menor a 0 o mayor al len de la lista)
 o (si el indice to es menor o igual a from o mayor al len de la lista)
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_subList(LinkedList *this, int from, int to) {
	LinkedList *cloneArray = NULL;
	int length;
	void *sublist;
	if (this != NULL) {
		length = ll_len(this);
		if (from >= 0 && from < length && to > from && to <= length) {
			cloneArray = ll_newLinkedList();
			for (; from < to; from++) {

				sublist = ll_get(this, from);
				ll_add(cloneArray, sublist);

			}

		}
	}

	return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_clone(LinkedList *this) {
	LinkedList *cloneArray = NULL;
	int length;

	if (this != NULL) {
		length = ll_len(this);
//		for (i = 0; i < length; i++) {
//			listaAClonar = ll_get(this, i);
//			ll_add(cloneArray, listaAClonar);
//		}

		cloneArray = ll_subList(this, 0, length);

	}

	return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 ( 0) Si ok
 */
int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order) {
	int i;
	int j;
	void *elementoDeI;
	void *elementoDeJ;
	int length;
	int returnAux = -1;

	if (this != NULL) {
		length = ll_len(this);
		if (pFunc != NULL && (order == 1 || order == 0)) {
			for (i = 0; i < length - 1; i++) {
				for (j = i + 1; j < length; j++) {
					elementoDeI = ll_get(this, i);
					elementoDeJ = ll_get(this, j);
					if (order == 1) {
						if (pFunc(elementoDeI, elementoDeJ) > 0) {
							ll_set(this, i, elementoDeJ);
							ll_set(this, j, elementoDeI);
						}
					} else {
						if (pFunc(elementoDeI, elementoDeJ) < 0) {
							ll_set(this, i, elementoDeJ);
							ll_set(this, j, elementoDeI);
						}
					}
				}
			}
			returnAux = 0;
		}
	}

	return returnAux;

}

/** \brief Genera la nueva lista resultado, agregará a la misma los ítems correspondientes y la devolverá
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  una nueva lista con los criterios filtrados.
 */
LinkedList* ll_filter(LinkedList *this, int (*pFunc) (void* element)) {
	LinkedList *cloneArray = NULL;
	int i;
	void *elementoDeI;

	int length;

	if (this != NULL) {
		length = ll_len(this);
		if (pFunc != NULL) {
			cloneArray = ll_newLinkedList();
			for (i = 0; i < length; i++) {

				elementoDeI = ll_get(this, i);

				if (pFunc(elementoDeI) > 0) {
					ll_add(cloneArray, elementoDeI);
				}

			}

		}
	}

	return cloneArray;

}

/** \brief Genera la nueva lista resultado, agregará a la misma los ítems correspondientes y la devolverá
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna una nueva lista con el atributo totalServicio calculado
 */
LinkedList* ll_map(LinkedList* this, void* (*pFunc) (void* element)) {
	LinkedList *cloneArray = NULL;
	int i;
	void *elementoDeI;

	int length;

	if (this != NULL) {
		length = ll_len(this);
		if (pFunc != NULL) {
			//llamo a la funcion ll_newLinkedList() para crear la nueva linkedlist que voy a retornar en memoria.
			cloneArray = ll_newLinkedList();
			for (i = 0; i < length; i++) {

				elementoDeI = ll_get(this, i);
				pFunc(elementoDeI);
				ll_add(cloneArray, elementoDeI);

			}

		}
	}

	return cloneArray;

}
