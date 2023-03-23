#include "APIG23.h"

// Construcción / Destrucción

// Debe ser a lo sumo O(mlogm)
Grafo ConstruirGrafo() {
    
}

// Debe ser a lo sumo O(m)
void DestruirGrafo(Grafo G) {

}



// Funciones para extraer datos del grafo.

// Debe ser O(1)
u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

// Debe ser O(1)
u32 NumeroDeLados(Grafo G) {
    return G->m;
}

// Debe ser O(1)
u32 Delta(Grafo G) {
    return G->delta;
}



// Funciones de extraccion de informacion de vertices 

// Debe ser O(1)
u32 Nombre(u32 i,Grafo G) {
    return G->vertices[i].nombre;
}

// Debe ser O(1)
u32 Grado(u32 i,Grafo G) {
    return G->vertices[i].grado;
}

// Debe ser O(1)
u32 IndiceVecino(u32 j,u32 i,Grafo G) {
    return G->vertices[i].vecinos[j];
}