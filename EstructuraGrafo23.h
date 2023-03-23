#ifndef ESTRUCTURA_GRAFO_H
#define ESTRUCTURA_GRAFO_H

#include <stdint.h>


// u32 se define a partir de uint32_t
typedef uint32_t u32;

// Estructura de un vértice.
typedef struct VerticeSt {
    u32 nombre;
    u32 grado;
    u32 *vecinos;
} VerticeSt;

// Estructura de un grafo.
typedef struct GrafoSt {
    u32 n;
    u32 m;
    u32 delta;
    VerticeSt *vertices;
} GrafoSt;


#endif