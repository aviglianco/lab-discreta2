#ifndef ESTRUCTURA_GRAFO_H
#define ESTRUCTURA_GRAFO_H

#include <stdint.h>


// u32 se define a partir de uint32_t
typedef uint32_t u32;

// Estructura de un vértice.
typedef struct VerticeSt {
    u32 nombre; // Nombre del vértice.
    u32 grado; // Grado del vértice.
    u32 indice; // Indice del primer vecino en el arreglo de vecinos.
} VerticeSt;

// Se define Vertice como puntero a VerticeSt.
typedef struct VerticeSt *Vertice;

// Estructura de un grafo.
typedef struct GrafoSt {
    u32 n; // Cantidad de vértices.
    u32 m; // Cantidad de lados.
    u32 delta; // Grado máximo.
    Vertice *vertices; // Arreglo de vértices.
    u32 *lista_de_adyacencia; // Arreglo de vecinos.
} GrafoSt;


#endif