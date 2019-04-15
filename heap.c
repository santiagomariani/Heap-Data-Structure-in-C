#include "heap.h"

#define TAMINICIAL 10
#define NODO_RAIZ 0

struct heap{
	cmp_func_t cmp;
	void** arr;
	size_t cant;
	size_t tam;
};

void heap_downheap(const heap_t *heap,size_t pos,size_t cant);

void heap_upheap(const heap_t *heap,size_t pos);

void heap_swap(const heap_t *heap, size_t pos1, size_t pos2);

bool heap_nodo_hoja(const heap_t *heap,size_t pos,size_t cant);

size_t heap_hijo_mayor(const heap_t *heap,size_t pos,size_t cant,cmp_func_t cmp);

void heap_heapify(heap_t* heap);

void** copiar_arreglo(void *arreglo[],size_t n);

bool heap_arr_redimensionar(heap_t *heap,size_t tam_nuevo);

bool heap_lleno(const heap_t *heap);

size_t heap_cantidad(const heap_t *heap);

bool heap_esta_vacio(const heap_t *heap);

void *heap_ver_max(const heap_t *heap);

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;

	void** arr = malloc(TAMINICIAL*sizeof(void*));

	if(!arr){
		free(heap);
		return NULL;
	}

	for(int i = 0;i < TAMINICIAL;i++){ // Inicializo en NULL.
		arr[i] = NULL;
	}

	heap->arr = arr;
	heap->tam = TAMINICIAL;
	heap->cant = 0;
	heap->cmp = cmp;

	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

	heap_t* heap = heap_crear(cmp);
	if(!heap) return NULL;

	void** arreglo_nuevo = copiar_arreglo(arreglo,n); // O(N)
	if(!arreglo_nuevo){
		free(heap);
		return NULL;
	}
	free(heap->arr);
	heap->arr = arreglo_nuevo;
	heap->tam = n;
	heap->cant = n;

	heap_heapify(heap); // O(N)

	return heap; // O(N) + O(N) = O(N)
}

bool heap_encolar(heap_t *heap, void *elem){

	//printf("\n valor:%i | cantidad:%zu \n ",*(int*)elem,heap->cant);
	
	if(heap_lleno(heap)){
		if(!heap_arr_redimensionar(heap,heap->tam * 2)) return false;
	}
	// HACER REDIMENSION.

	size_t ultima_pos = heap->cant;
	heap->arr[ultima_pos] = elem;

	heap_upheap(heap,ultima_pos);
	heap->cant++;

	return true; 
}

void *heap_desencolar(heap_t *heap){

	if(heap_esta_vacio(heap)) return NULL;

	size_t cuarta_parte_tam = heap->tam / 4;

	if(heap->tam > TAMINICIAL && (heap->cant - 1) == cuarta_parte_tam){
		size_t tam_nuevo = heap->tam / 2;
		if(!heap_arr_redimensionar(heap,tam_nuevo)) return false;
	}

	void* dato = heap->arr[NODO_RAIZ];

	size_t pos_ultimo_nodo = heap->cant -1;

	heap->arr[NODO_RAIZ] = heap->arr[pos_ultimo_nodo];
	heap->arr[pos_ultimo_nodo] = NULL;

	heap->cant--;
	heap_downheap(heap,NODO_RAIZ,heap->cant);

	return dato;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

	heap_t* heap = heap_crear(cmp);
	if(!heap) return;

	free(heap->arr);
	heap->arr = elementos;
	heap->tam = cant;
	heap->cant = cant;

	heap_heapify(heap);  // O(N)

	int ultimo_relativo = (int)heap->cant -1;

	while(ultimo_relativo > 0){
		heap_swap(heap,NODO_RAIZ,ultimo_relativo);
		ultimo_relativo--;
		heap_downheap(heap,NODO_RAIZ,ultimo_relativo + 1);
	}// NLOG(N)
	free(heap);
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(destruir_elemento){
		for(int i = 0;i < heap->cant;i++){
			destruir_elemento(heap->arr[i]);
		}
	}
	free(heap->arr);
	free(heap);
}

void** copiar_arreglo(void *arreglo[],size_t n){
	void** arreglo_nuevo = malloc(n*sizeof(void*));
	if(!arreglo_nuevo) return NULL;

	for(size_t i = 0;i < n;i++){
		arreglo_nuevo[i] = arreglo[i];
	}

	return arreglo_nuevo; 
}


bool heap_arr_redimensionar(heap_t *heap,size_t tam_nuevo){
	printf("REDIMENSION\n");
	void** datos_nuevo = realloc(heap->arr,tam_nuevo*sizeof(void*));
	if(!datos_nuevo) return false;

	heap->tam = tam_nuevo;
	heap->arr = datos_nuevo;
	
	return true;
}

void heap_swap(const heap_t *heap, size_t pos1, size_t pos2){
	void* aux_dato = heap->arr[pos1];

	heap->arr[pos1] = heap->arr[pos2];
	heap->arr[pos2] = aux_dato;
}

bool heap_nodo_hoja(const heap_t *heap,size_t pos,size_t cant){
	size_t hijo_izq = 2*pos + 1;
	return hijo_izq >= cant;
}

size_t heap_hijo_mayor(const heap_t *heap,size_t pos,size_t cant,cmp_func_t cmp){
	size_t hijo_izq = 2*pos + 1;
	size_t hijo_der = 2*pos + 2;

	size_t indice_max = hijo_izq;

	if(hijo_der < cant){
		if(cmp(heap->arr[hijo_der],heap->arr[hijo_izq]) > 0){
			indice_max = hijo_der;
		}
	}
	return indice_max;
}

void heap_downheap(const heap_t *heap,size_t pos,size_t cant){

	if(heap_nodo_hoja(heap,pos,cant))return;

	size_t indice_max = heap_hijo_mayor(heap,pos,cant,heap->cmp);

	if(heap->cmp(heap->arr[pos],heap->arr[indice_max]) < 0){
		heap_swap(heap,pos,indice_max);
		heap_downheap(heap,indice_max,cant);
	}
}

void heap_upheap(const heap_t *heap,size_t pos){
	if(pos == 0) return;

	size_t padre_pos = (pos-1) / 2;

	if(heap->cmp(heap->arr[pos],heap->arr[padre_pos]) > 0){
		heap_swap(heap,pos,padre_pos);
		heap_upheap(heap,padre_pos);
	}
}

void heap_heapify(heap_t* heap){

	int i = (int)heap->cant - 2 / 2;

	while(i >= 0){
		heap_downheap(heap,i,heap->cant);
		i--;
	}
}

bool heap_lleno(const heap_t *heap){
	return heap->cant == heap->tam;
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}

void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	return heap->arr[0];
}



