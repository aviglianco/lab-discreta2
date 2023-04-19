#include <stdio.h> 
#include <stdlib.h>
#include "EstructuraGrafo23.h"
#include "APIG23.h"
#include "APIParte2.h"


int main(void) {
    Grafo g = ConstruirGrafo();

    printf("Se construyó bien el grafo\n"); 

    printf("Nro. de Vértices %d\n",g->n);  
    printf("Nro. de Lados %d\n"   ,g->m);
    printf("Delta  %d\n",g->delta);

    u32 *orden = calloc(g->n, sizeof(u32));
    u32 *color = calloc(g->n, sizeof(u32));

    for (u32 i = 0; i < g->n; i++){
        orden[i] = i;
    }

    u32 cantColores = Greedy(g, orden, color);
    
    printf("Cantidad de colores: %d\n", cantColores);

    printf("------------------------\n");
    for (unsigned int i = 0; i < 200; i++){
        cantColores = Greedy(g, orden, color);
        OrdenImparPar(g->n, orden, color);
    }
    printf("Cantidad de colores: %d\n", cantColores);

    // Imprimir arreglo de colores:
    printf("------------------------\n");
    for (u32 i = 0; i < g->n; i++){
        printf("Vertice %d, color %d\n", i, color[i]);
    }

    DestruirGrafo(g);
    
    return 0;
}
