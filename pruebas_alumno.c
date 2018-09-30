#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LARGO_VECTOR 10000
#define CADENA_DE_PRUEBA "abcdefghij"
#define LARGO_DE_CADENA 3

#define CREAR_PILA() pila_t* pila = pila_crear()
#define FINAL_DE_LINEA() printf("\n")

void test_comportamiento_vacio(){
    CREAR_PILA();

    printf("\nPRUEBAS: PILA VACIA\n");
    print_test("  Pude crear la pila", pila != NULL);
    print_test("  Pila recien creada esta vacia", pila_esta_vacia(pila));
    print_test("  El ver tope devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("  Desapilar devuelve NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
    print_test("  Destruyo la pila", true);
}

void test_comportamiento_un_elemento(){
    CREAR_PILA();
    char dummy_a = 'a';

    printf("\nPRUEBAS: PILA CON UN ELEMENTO\n");
    print_test("  Apilo un elemento", pila_apilar(pila, &dummy_a));
    print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
    print_test("  El tope es el elemento apilado", *(char*)pila_ver_tope(pila) == dummy_a);
    print_test("  Desapilar el mismo elemento", *(char *)pila_desapilar(pila) == dummy_a);
    print_test("  Pila esta vacia", pila_esta_vacia(pila));
    print_test("  El ver tope devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("  Desapilar devuelve NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

void test_comportamiento_varios_elementos(){
    CREAR_PILA();
    char dummy[] = CADENA_DE_PRUEBA;
    int dummy_1 = 1;

    printf("\nPRUEBAS: VARIOS ELEMENTOS\n");

    for (int i = 0; i < LARGO_DE_CADENA; i++){
        print_test("  Apilo un elemento", pila_apilar(pila, &dummy[i]));
        print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
        print_test("  Tope es el esperado", *(char*)pila_ver_tope(pila) == dummy[i]);
        FINAL_DE_LINEA();
    }

    for (int i = LARGO_DE_CADENA-1; i > 0; i--){ //Saco todos los elementos menos el ultimo
        print_test("  Desapilar devuelve el elemento correcto", *(char*)pila_desapilar(pila) == dummy[i]);
        print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
        print_test("  Tope es el esperado", *(char*)pila_ver_tope(pila) == dummy[i-1]);
        FINAL_DE_LINEA();
    }

    print_test("  Apilo un elemento", pila_apilar(pila, &dummy_1));
    print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
    print_test("  Tope es el esperado", *(int*)pila_ver_tope(pila) == dummy_1);

    print_test("  Desapilar devuelve el elemento correcto", *(int*)pila_desapilar(pila) == dummy_1);
    print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
    print_test("  Tope es el esperado", *(char*)pila_ver_tope(pila) == dummy[0]);

    print_test("  Desapilar devuelve el elemento correcto", *(char*)pila_desapilar(pila) == dummy[0]);
    print_test("  Pila esta vacia", pila_esta_vacia(pila));
    print_test("  Tope es NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
}

void test_volumen(){
    CREAR_PILA();
    int vector_prueba[LARGO_VECTOR];
    size_t fallos;   

    printf("\nPRUEBA: VOLUMEN\n");

    fallos = 0;    
    for (int i = 0; i < LARGO_VECTOR; i++){
        vector_prueba[i] = i;
        if (!pila_apilar(pila, &vector_prueba[i])) fallos++;
        if (pila_esta_vacia(pila)) fallos++;
        if (*(int*)pila_ver_tope(pila) != vector_prueba[i]) fallos++;
    }

    print_test("  Pude apliar muchos elementos manteniendo invariantes", fallos == 0);
        
    fallos = 0;
    for(int i = LARGO_VECTOR-1; i > -1; i--){
        if (pila_esta_vacia(pila)) fallos++;
        if (*(int*)pila_ver_tope(pila) != vector_prueba[i]) fallos++;
        if (*(int*)pila_desapilar(pila) != vector_prueba[i]) fallos++; 
    }
    
    print_test("  Pude desapilar todos los elementos manteniendo invariantes", fallos == 0);

    pila_destruir(pila);
}

void test_NULL(){
    CREAR_PILA();

    printf("\nPRUEBA: MANEJO DE ELEMENTOS NULL\n"); 

    print_test("  Puedo apilar NULL", pila_apilar(pila, NULL));
    print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
    print_test("  El tope es NULL", pila_ver_tope(pila) == NULL);
    FINAL_DE_LINEA();
    print_test("  Apilo otro NULL", pila_apilar(pila, NULL));
    print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
    print_test("  El tope es NULL", pila_ver_tope(pila) == NULL);
    FINAL_DE_LINEA();
    print_test("  Desapilar devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("  Pila no esta vacia", !pila_esta_vacia(pila));
    print_test("  Desapilar devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("  Pila esta vacia", pila_esta_vacia(pila));

    pila_destruir(pila);  
}

void test_destruccion(){
    printf("\nPRUEBA: DESTRUCCION DE ELEMENTOS\n");

    CREAR_PILA();
    int vector_prueba[LARGO_VECTOR];
    for (int i = 0; i < LARGO_VECTOR; i++){
        vector_prueba[i] = i;
        pila_apilar(pila, &vector_prueba[i]);
    }
    pila_destruir(pila);
    print_test("  Pude destruir una pila con varios elementos", true);
}

void pruebas_pila_alumno() {
    test_comportamiento_vacio();
    test_comportamiento_un_elemento();
    test_comportamiento_varios_elementos();

    test_volumen();
    test_NULL();
    test_destruccion();    
}
