#include "heap.h"
#include "testing.h"
#include <stddef.h>

heap_t *heap_crear(cmp_func_t cmp);
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);
void heap_destruir(heap_t *heap, void destruir_elemento(void *e));

size_t heap_cantidad(const heap_t *heap);
bool heap_esta_vacio(const heap_t *heap);

bool heap_encolar(heap_t *heap, void *elem);
void *heap_ver_max(const heap_t *heap);
void *heap_desencolar(heap_t *heap);

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);


int cmpint(const void *a,const void *b){
	int valor1 = *(int*)a;
	int valor2 = *(int*)b;

	if(valor1 == valor2) return 0;

	if(valor1 < valor2) return -1;

	return 1;
}

void pruebas_heap_vacio(){

	heap_t* heap = heap_crear(cmpint);

	print_test("Prueba heap crear heap vacio",heap);
	print_test("Prueba heap esta vacio",heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de heap vacio es 0",heap_cantidad(heap) == 0);
	print_test("Prueba heap ver max es NULL",heap_ver_max(heap) == NULL);
	print_test("Prueba heap desencolar es NULL",heap_desencolar(heap) == NULL);

	heap_destruir(heap,NULL);
}

void pruebas_heap_encolar(){

	heap_t* heap = heap_crear(cmpint);
	
	print_test("Prueba heap crear heap vacio",heap);
	int valor1 = 1,valor2 = 2,valor3 = 3,valor4 = 4;

	print_test("Prueba heap encolar valor1",heap_encolar(heap,&valor1));
	print_test("Prueba heap cantidad es 1",heap_cantidad(heap) == 1);
	print_test("Prueba heap ver max es valor1",*(int*)heap_ver_max(heap) == valor1);
	print_test("Prueba heap encolar valor3",heap_encolar(heap,&valor3));
	print_test("Prueba heap cantidad es 2",heap_cantidad(heap) == 2);
	print_test("Prueba heap ver max es valor3",*(int*)heap_ver_max(heap) == valor3);
	print_test("Prueba heap encolar valor2",heap_encolar(heap,&valor2));
	print_test("Prueba heap cantidad es 3",heap_cantidad(heap) == 3);
	print_test("Prueba heap ver max es valor3",*(int*)heap_ver_max(heap) == valor3);
	print_test("Prueba heap encolar valor4",heap_encolar(heap,&valor4));
	print_test("Prueba heap cantidad es 4",heap_cantidad(heap) == 4);
	print_test("Prueba heap ver max es valor4",*(int*)heap_ver_max(heap) == valor4);

	heap_destruir(heap,NULL);

}

void pruebas_heap_desencolar(){
	heap_t* heap = heap_crear(cmpint);
	print_test("Prueba heap crear heap vacio",heap);
	int valor1 = 1,valor2 = 2,valor3 = 3,valor4 = 4,valor5 = 5,valor6 = 6,valor7 = 7;

	print_test("Se encola valor6",heap_encolar(heap,&valor6));
	print_test("Se encola valor4",heap_encolar(heap,&valor4));
	print_test("Se encola valor1",heap_encolar(heap,&valor1));
	print_test("Se encola valor7",heap_encolar(heap,&valor7));
	print_test("Se encola valor2",heap_encolar(heap,&valor2));
	print_test("Se encola valor5",heap_encolar(heap,&valor5));
	print_test("Se encola valor3",heap_encolar(heap,&valor3));

	print_test("Prueba heap desencolar  es valor7",*(int*)heap_desencolar(heap) == 7);
	print_test("Prueba heap cantidad es 6",heap_cantidad(heap) == 6);
	print_test("Prueba heap ver max es 6",*(int*)heap_ver_max(heap) == 6);
	print_test("Prueba heap desencolar es valor6",*(int*)heap_desencolar(heap) == 6);
	print_test("Prueba heap cantidad es 5",heap_cantidad(heap) == 5);
	print_test("Prueba heap ver max es 5",*(int*)heap_ver_max(heap) == 5);
	print_test("Prueba heap desencolar es valor5",*(int*)heap_desencolar(heap) == 5);
	print_test("Prueba heap cantidad es 4",heap_cantidad(heap) == 4);
	print_test("Prueba heap ver max es 4",*(int*)heap_ver_max(heap) == 4);
	print_test("Prueba heap desencolar es valor4",*(int*)heap_desencolar(heap) == 4);
	print_test("Prueba heap cantidad es 3",heap_cantidad(heap) == 3);
	print_test("Prueba heap ver max es 3",*(int*)heap_ver_max(heap) == 3);
	print_test("Prueba heap desencolar es valor3",*(int*)heap_desencolar(heap) == 3);
	print_test("Prueba heap cantidad es 2",heap_cantidad(heap) == 2);
	print_test("Prueba heap ver max es 2",*(int*)heap_ver_max(heap) == 2);
	print_test("Prueba heap desencolar es valor2",*(int*)heap_desencolar(heap) == 2);
	print_test("Prueba heap cantidad es 1",heap_cantidad(heap) == 1);
	print_test("Prueba heap ver max es 1",*(int*)heap_ver_max(heap) == 1);
	print_test("Prueba heap desencolar es valor1",*(int*)heap_desencolar(heap) == 1);
	print_test("Prueba heap ver max es NULL",heap_desencolar(heap) == NULL);
	print_test("Prueba heap cantidad es 0",heap_cantidad(heap) == 0);

	heap_destruir(heap,NULL);
}

void pruebas_heap_redimensionar(){

	heap_t* heap = heap_crear(cmpint);	

	int valor1 = 1,valor2 = 2,valor3 = 3,valor4 = 4,valor5 = 5,valor6 = 6,valor7 = 7;
	int valor8 = 8,valor9 = 9,valor10 = 10,valor11 = 11;

	print_test("Se encola valor1",heap_encolar(heap,&valor1));
	print_test("Se encola valor2",heap_encolar(heap,&valor2));
	print_test("Se encola valor3",heap_encolar(heap,&valor3));
	print_test("Se encola valor4",heap_encolar(heap,&valor4));
	print_test("Se encola valor5",heap_encolar(heap,&valor5));
	print_test("Se encola valor6",heap_encolar(heap,&valor6));
	print_test("Se encola valor7",heap_encolar(heap,&valor7));
	print_test("Se encola valor8",heap_encolar(heap,&valor8));
	print_test("Se encola valor9",heap_encolar(heap,&valor9));
	print_test("Se encola valor10",heap_encolar(heap,&valor10));
	print_test("Se encola valor11",heap_encolar(heap,&valor11));

	print_test("Prueba heap desencolar es valor11",*(int*)heap_desencolar(heap) == 11);
	print_test("Prueba heap desencolar es valor10",*(int*)heap_desencolar(heap) == 10);
	print_test("Prueba heap desencolar es valor9",*(int*)heap_desencolar(heap) == 9);
	print_test("Prueba heap desencolar es valor8",*(int*)heap_desencolar(heap) == 8);
	print_test("Prueba heap desencolar es valor7",*(int*)heap_desencolar(heap) == 7);
	print_test("Prueba heap desencolar es valor6",*(int*)heap_desencolar(heap) == 6);
	
	print_test("Se encola valor6",heap_encolar(heap,&valor6));
	print_test("Se encola valor7",heap_encolar(heap,&valor7));
	print_test("Se encola valor8",heap_encolar(heap,&valor8));
	print_test("Se encola valor9",heap_encolar(heap,&valor9));
	print_test("Se encola valor10",heap_encolar(heap,&valor10));
	print_test("Se encola valor11",heap_encolar(heap,&valor11));

	heap_destruir(heap,NULL);
}

void pruebas_heap_sort(){

	void* datos[11];
	int orden1[11] = {1,4,6,3,5,8,2,7,11,9,10};
	int orden2[11] = {6,1,9,5,2,3,10,4,8,7,11};

	//ORDEN 1//
	for(int i = 0;i < 11;i++){
		datos[i] = &orden1[i];
	}

	printf("%i",*(int*)datos[0]);
	for(int i = 1;i < 11;i++){
		printf("- %i",*(int*)datos[i]);
	}

	heap_sort(datos,11,cmpint);

	printf("\n\n%i",*(int*)datos[0]);
	for(int i = 1;i < 11;i++){
		printf("- %i",*(int*)datos[i]);
	}

	// ORDEN 2
	for(int i = 0;i < 11;i++){
		datos[i] = &orden2[i];
	}

	printf("\n %i",*(int*)datos[0]);
	for(int i = 1;i < 11;i++){
		printf("- %i",*(int*)datos[i]);
	}

	heap_sort(datos,11,cmpint);

	printf("\n\n%i",*(int*)datos[0]);
	for(int i = 1;i < 11;i++){
		printf("- %i",*(int*)datos[i]);
	}
}

void pruebas_heap_arr(){

	void* datos[11];
	int orden1[11] = {1,4,6,3,5,8,2,7,11,9,10};

	//ORDEN 1//
	for(int i = 0;i < 11;i++){
		datos[i] = &orden1[i];
	}

	heap_t* heap = heap_crear_arr(datos,11,cmpint);

	print_test("Prueba heap arr se convierte arreglo generico a heap de maximos",heap);
	print_test("Prueba heap arr ver max es 11",*(int*)heap_ver_max(heap) == 11);
	print_test("Prueba heap arr desencolar es 11",*(int*)heap_desencolar(heap) == 11);
	print_test("Prueba heap arr ver max es 10",*(int*)heap_ver_max(heap) == 10);
	print_test("Prueba heap arr desencolar es 10",*(int*)heap_desencolar(heap) == 10);
	print_test("Prueba heap arr ver max es 9",*(int*)heap_ver_max(heap) == 9);
	print_test("Prueba heap arr desencolar es 9",*(int*)heap_desencolar(heap) == 9);
	print_test("Prueba heap arr ver max es 8",*(int*)heap_ver_max(heap) == 8);
	print_test("Prueba heap arr desencolar es 8",*(int*)heap_desencolar(heap) == 8);
	print_test("Prueba heap arr ver max es 7",*(int*)heap_ver_max(heap) == 7);
	print_test("Prueba heap arr desencolar es 7",*(int*)heap_desencolar(heap) == 7);
	print_test("Prueba heap arr ver max es 6",*(int*)heap_ver_max(heap) == 6);
	print_test("Prueba heap arr desencolar es 6",*(int*)heap_desencolar(heap) == 6);
	print_test("Prueba heap arr ver max es 5",*(int*)heap_ver_max(heap) == 5);
	print_test("Prueba heap arr desencolar es 5",*(int*)heap_desencolar(heap) == 5);
	print_test("Prueba heap arr ver max es 4",*(int*)heap_ver_max(heap) == 4);
	print_test("Prueba heap arr desencolar es 4",*(int*)heap_desencolar(heap) == 4);
	print_test("Prueba heap arr ver max es 3",*(int*)heap_ver_max(heap) == 3);
	print_test("Prueba heap arr desencolar es 3",*(int*)heap_desencolar(heap) == 3);
	print_test("Prueba heap arr ver max es 2",*(int*)heap_ver_max(heap) == 2);
	print_test("Prueba heap arr desencolar es 2",*(int*)heap_desencolar(heap) == 2);
	print_test("Prueba heap arr ver max es 1",*(int*)heap_ver_max(heap) == 1);
	print_test("Prueba heap arr desencolar es 1",*(int*)heap_desencolar(heap) == 1);
	print_test("Prueba heap arr ver max es NULL",heap_ver_max(heap) == NULL);
	print_test("Prueba heap arr desencolar es NULL",heap_desencolar(heap) == NULL);

	heap_destruir(heap,NULL);
}

void pruebas_heap(){
	pruebas_heap_vacio();
	pruebas_heap_encolar();
	pruebas_heap_desencolar();
	pruebas_heap_redimensionar();
	pruebas_heap_sort();
	pruebas_heap_arr();
}

// //////////////////////////////
