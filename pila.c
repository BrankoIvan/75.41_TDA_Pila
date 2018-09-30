#include "pila.h"
#include <stdlib.h>

/******************************************************************************/

#define INITIAL_SIZE ((size_t) 8) //Tamaño inicial
#define SIZE_INDEX ((size_t) 2) //Indice que indica cuanto crece o decrece el tamaño
#define SIZE_RATE ((size_t) 4) //Tasa de redimension

/******************************************************************************/

struct pila {
   void** datos;
   size_t cantidad;
   size_t capacidad;
};

/******************************************************************************/

bool expandir(pila_t* pila){
   void** nuevos_datos = realloc(pila->datos, (pila->capacidad * SIZE_INDEX) * sizeof(void*));
   if(nuevos_datos == NULL) return false;

   pila->datos = nuevos_datos;
   pila->capacidad *= SIZE_INDEX;

   return true;
}

bool reducir(pila_t* pila){
   if(pila->capacidad == INITIAL_SIZE) return true;

   void** nuevos_datos = realloc(pila->datos, (pila->capacidad / SIZE_INDEX) * sizeof(void*));
   if(nuevos_datos == NULL) return false;

   pila->datos = nuevos_datos;
   pila->capacidad /= SIZE_INDEX;

   return true;
}

bool manejar_redimension(pila_t* pila){
   // Solo hay dos casos en los que debo redimensionar:

   if (pila->cantidad == pila->capacidad) return expandir(pila);
   // Si la pila esta llena

   if (pila->cantidad <= (pila->capacidad / SIZE_RATE)) return reducir(pila);
   // o si la pila esta a un cuarto de su capacidad. reducir no redimensiona por
   // por debajo del tamaño inicial

   return true;
}

/******************************************************************************/

pila_t* pila_crear(void){
   pila_t* pila = malloc(sizeof(pila_t)); 
   if(pila == NULL) return NULL;

   pila->datos = malloc(INITIAL_SIZE*sizeof(void*));
   if(INITIAL_SIZE > 0 && pila->datos == NULL){
      free(pila);
      return NULL;
   }

   pila->cantidad = 0;
   pila->capacidad = INITIAL_SIZE;      
   return pila;
}

void pila_destruir(pila_t *pila){
   if (pila->datos != NULL) free(pila->datos);
   free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
   return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void* valor){
   if (!manejar_redimension(pila)) return false;

   pila->datos[pila->cantidad] = valor;
   pila->cantidad ++;

   return true;
}

void* pila_ver_tope(const pila_t *pila){
   if (pila_esta_vacia(pila)) return NULL;
   return pila->datos[(pila->cantidad) - 1];
}

void* pila_desapilar(pila_t *pila){
   if (pila_esta_vacia(pila) || !manejar_redimension(pila)) return NULL; 

   void* valor = pila->datos[(pila->cantidad) - 1];
   pila->cantidad --;
   
   return valor;
}