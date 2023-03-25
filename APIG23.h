#ifndef APIG23_H
#define APIG23_H


#include <stdio.h>
#include <stdlib.h>


// el .h de abajo debe tener definida GrafoSt y u32.
#include "EstructuraGrafo23.h"



// Grafo es un puntero a una estructura GrafoSt.
typedef GrafoSt *Grafo;


// Construcción / Destrucción

/* 
 * @brief Construye un grafo leyendo desde el stdin.
 * @returns El grafo con toda la información cargada.
 */
Grafo ConstruirGrafo();

/*
 * @brief Libera la memoria de un grafo.
 * @param G el grafo que se desea destruir.
 */
void DestruirGrafo(Grafo G);



// Funciones para extraer datos del grafo.

/*
 * Función Devuelve el número de vértices de un grafo.
 * @param G el grafo del que se desea conocer el número de vértices.
 * @returns El número de vértices de G.
 */
u32 NumeroDeVertices(Grafo G);

/* 
 * @brief Devuelve el número de lados de un grafo.
 * @param G el grafo del que se desea conocer el número de lados.
 * @returns El número de lados de G. 
 */
u32 NumeroDeLados(Grafo G);

/* 
 * @brief Devuelve el grado máximo de un grafo.
 * @param G el grafo del que se desea conocer el grado máximo.
 * @returns El grado máximo de G. 
 */
u32 Delta(Grafo G);


// Funciones de extraccion de informacion de vertices 

/* 
 * @brief Devuelve el nombre de un vértice.
 * @param i el índice del vértice del que se desea conocer el nombre.
 * @param G el grafo del que se desea conocer el nombre del vértice.
 * @returns El nombre del vértice i de G. 
 */
u32 Nombre(u32 i,Grafo G);

/*
 * @brief Devuelve el grado de un vértice.
 * @param i el índice del vértice del que se desea conocer el grado.
 * @param G el grafo del que se desea conocer el grado del vértice.
 * @returns El grado del vértice i de G. 
 */
u32 Grado(u32 i,Grafo G);

/* 
 * @brief Devuelve el índice del j-ésimo vecino de un vértice.
 * @param j el índice del vecino del que se desea conocer el índice.
 * @param i el índice del vértice del que se desea conocer el índice del j-ésimo vecino.
 * @param G el grafo del que se desea conocer el índice del j-ésimo vecino del vértice i.
 * @returns El índice del j-ésimo vecino del vértice i de G. 
 */
u32 IndiceVecino(u32 j,u32 i,Grafo G);


#endif
