#ifndef APIG23_H
#define APIG23_H


#include <stdio.h>
#include <stdlib.h>


// el .h de abajo debe tener definida GrafoSt y u32.
#include "EstructuraGrafo23.h"



// Grafo es un puntero a una estructura GrafoSt.
typedef GrafoSt *Grafo;


// Construcción / Destrucción

// Función que construye un grafo leyendo desde el stdin.
// @returns G - un grafo con toda la información cargada.
Grafo ConstruirGrafo();

// Función que libera la memoria de un grafo.
// @param {Grafo} G - el grafo que se desea destruir.
void DestruirGrafo(Grafo G);



// Funciones para extraer datos del grafo.

// Función que devuelve el número de vértices de un grafo.
// @param {Grafo} G - el grafo del que se desea conocer el número de vértices.
// @returns n - el número de vértices de G.
u32 NumeroDeVertices(Grafo G);

// Función que devuelve el número de lados de un grafo.
// @param {Grafo} G - el grafo del que se desea conocer el número de lados.
// @returns m - el número de lados de G.
u32 NumeroDeLados(Grafo G);

// Función que devuelve el grado máximo de un grafo.
// @param {Grafo} G - el grafo del que se desea conocer el grado máximo.
// @returns delta - el grado máximo de G.
u32 Delta(Grafo G);


// Funciones de extraccion de informacion de vertices 

// Función que devuelve el nombre de un vértice.
// @param {u32} i - el índice del vértice del que se desea conocer el nombre.
// @param {Grafo} G - el grafo del que se desea conocer el nombre del vértice.
// @returns nombre - el nombre del vértice i de G.
u32 Nombre(u32 i,Grafo G);

// Función que devuelve el grado de un vértice.
// @param {u32} i - el índice del vértice del que se desea conocer el grado.
// @param {Grafo} G - el grafo del que se desea conocer el grado del vértice.
// @returns grado - el grado del vértice i de G.
u32 Grado(u32 i,Grafo G);

// Función que devuelve el índice del j-ésimo vecino de un vértice.
// @param {u32} j - el índice del vecino del que se desea conocer el índice.
// @param {u32} i - el índice del vértice del que se desea conocer el índice del j-ésimo vecino.
// @param {Grafo} G - el grafo del que se desea conocer el índice del j-ésimo vecino del vértice i.
// @returns indice - el índice del j-ésimo vecino del vértice i de G.
u32 IndiceVecino(u32 j,u32 i,Grafo G);


#endif
