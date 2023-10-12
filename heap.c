#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if(pq->size ==0){
    return NULL;
  }
  return pq->heapArray[0].data;
}


//Función para obtener el índice del padre
int parent(int i) {
    return (i - 1) / 2;
}

// Función para intercambiar dos elementos
void swap(heapElem* x, heapElem* y) {
    heapElem temp = *x;
    *x = *y;
    *y = temp;
}
void heap_push(Heap* pq, void* data, int priority){
  heapElem nuevo;
  nuevo.data=data;
  nuevo.priority=priority;

  if(pq->size==pq->capac){//asegurarse del espacio
    pq->capac=pq->capac*2+1;
    pq->heapArray=realloc(pq->heapArray, pq->capac*(sizeof(heapElem)));
  }

  int i=pq->size;
  pq->heapArray[i]=nuevo;
  pq->size++;

  while(i != 0 && pq->heapArray[i].priority > pq->heapArray[parent(i)].priority){
    swap(&(pq->heapArray[i]), &(pq->heapArray[(i-1)/2]));
    i=parent(i);
  }   
}  


void heap_pop(Heap* pq){
  //void*max=pq->heapArray[0].data;
  pq->heapArray[0]=pq->heapArray[pq->size-1];
  pq->size--;
  int i=0;
  int larg=i;
  int izq=2*i+1;
  int der=2*i+2;

  if (izq < pq->size && pq->heapArray[izq].priority > pq->heapArray[larg].priority){
    larg=izq;
  }
  if(der < pq->size && pq->heapArray[der].priority > pq->heapArray[larg].priority){
    larg=der;
    
  }
  if (larg!=i){
    swap(&(pq->heapArray[i]), &(pq->heapArray[larg]));
  }

}

Heap* createHeap(){
  Heap*nuevo=(Heap*)malloc(3*sizeof(Heap));
  nuevo->heapArray=(heapElem*)malloc(3*sizeof(heapElem));
  nuevo->size=0;
  nuevo->capac=3;
  return nuevo;
}
