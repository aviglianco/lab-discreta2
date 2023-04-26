#include <stdio.h> 
#include <stdlib.h>
#include "EstructuraGrafo23.h"
#include "APIG23.h"
#include "APIParte2.h"


/**
 * @brief Ordena los vértices de forma natural.
 * @param n la cantidad de vértices del grafo.
 * @param Orden el arreglo donde se va a guardar el orden.
 * @returns 0 en caso de éxito, 1 en caso de error.
 * 
 * Debería ir en el archivo Orden.c, pero la dejamos aquí para evitar modificar 
 * el header provisto por la cátedra
*/
static char OrdenNatural(u32 n, u32* Orden) {
    u32 i;
    for (i = 0; i < n; i++) {
        Orden[i] = i;
    }
    return 0;
}


int main(void) {
    Grafo g = ConstruirGrafo();

    printf("Se construyó bien el grafo\n"); 

    printf("Nro. de Vértices %d\n",g->n);  
    printf("Nro. de Lados %d\n"   ,g->m);
    printf("Delta  %d\n",g->delta);

    u32 *orden = calloc(g->n, sizeof(u32));
    u32 *color = calloc(g->n, sizeof(u32));

    OrdenNatural(g->n, orden);

    u32 cantColores = Greedy(g, orden, color);
    printf("Cantidad de colores: %d\n", cantColores);

    // Aplicar orden Impar-Par y ejecutar Greedy 100 veces
    for (u32 i = 0; i < 100; i++) {
        u32 cantAnterior = cantColores;
        OrdenImparPar(g->n, orden, color);
        cantColores = Greedy(g, orden, color);
        if (cantColores > cantAnterior) {
            printf("ERROR!\n");
        } else {
            printf("Cantidad de colores: %d\n", cantColores);
        }
    }

    DestruirGrafo(g);
    
    return 0;
}
