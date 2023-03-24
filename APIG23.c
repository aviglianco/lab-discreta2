#include "APIG23.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Construcción / Destrucción

// Debe ser a lo sumo O(mlogm)
Grafo ConstruirGrafo() {
    u32 n, m, delta;
    char *line = NULL;
    size_t bufsize = 0;
    size_t linelen;
    Grafo G;
    // Read lines from standard input until end-of-file is reached
    while ((linelen = getline(&line, &bufsize, stdin)) != -1)
    {
        // Remove the newline character from the end of the line, if present
        if (line[linelen-1] == '\n') {
            line[linelen-1] = '\0';
            linelen--;
        }
        // Process the line as needed
        if (strncmp(line, "p edge ", 7) == 0) {
            sscanf(line+7, "%d %d", &n, &m);
            printf("p edge: n=%d n=%d\n", n, m);
            break; 
            //dejo de leer lineas porque ya consumi todos los comentarios previos a la informacion sobre las aristas
        }//si no coincide con p edge, entonces es un comentario y sigo leyendo lineas
    }

    for (unsigned int i = 0; i < m; i++)//se que tengo que leer m lineas SI o SI porque ya se cuantas aristas hay
    {
        getline(&line, &bufsize, stdin);
        if (line[linelen-1] == '\n') {
            line[linelen-1] = '\0';
            linelen--;
        }
        if (strncmp(line, "e ", 2) == 0) {
            int i, j;
            sscanf(line+2, "%d %d", &i, &j);
            printf("edge: i=%d j=%d\n", i, j); //de esta forma ya leeo las aristas del grafo, falta cheqeo de errores
        }
        //las lineas de codigo que remueven el \n del line creo pueden ser eliminados, no se si afecta en algo. Igual creo sscanf necesita que el line que le pases temrine en \0
    }

    // Free the memory used by the input buffer
    free(line);
}

// Debe ser a lo sumo O(m)
void DestruirGrafo(Grafo G) {
    // Liberar memoria de los vecinos de cada vértice.
    for (u32 i = 0; i < G->n; i++) {
        free(G->vertices[i].vecinos);
        G->vertices[i].vecinos = NULL;
    }

    // Liberar memoria de los vértices.
    free(G->vertices);
    G->vertices = NULL;

    // Liberar memoria del grafo.
    free(G);
    G = NULL;
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