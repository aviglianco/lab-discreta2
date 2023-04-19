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
    
    u32 n = NumeroDeVertices(g);
    u32 *orden1 = calloc(n, sizeof(u32));
    u32 *orden2 = calloc(n, sizeof(u32));
    u32 *color1 = calloc(n, sizeof(u32));
    u32 *color2 = calloc(n, sizeof(u32));
    
    OrdenNatural(n, orden1);
    OrdenNatural(n, orden2);
    u32 cantColores = Greedy(g, orden1, color1);
    printf("Cantidad de colores usando orden natural: %d\n", cantColores);


    OrdenImparPar(g->n, orden1, color1);
    OrdenJedi(g, orden2, color1);

    cantColores = Greedy(g, orden1, color1);
    printf("Cantidad de colores usando orden impar par: %d\n", cantColores);

    
    cantColores = Greedy(g, orden2, color2);
    printf("Cantidad de colores usando orden Jedi: %d\n", cantColores);

    u32 cantColores1,cantColores2,cantColores3;
    u32 *aux;
    for (u32 i = 0; i < 32; i++)
    {
        for (u32 i = 0; i < 16; i++)
        {
            OrdenImparPar(n, orden1, color1);
            cantColores1 = Greedy(g, orden1, color1);
            
            OrdenJedi(g, orden2, color2);
            cantColores2 =  Greedy(g, orden2, color2);
        }
        aux = color1;
        color1 = color2;
        color2 = aux;
    }

    /* cantidad de colores3 es el maximo entre 1 y 2 */
    cantColores3 = cantColores1 > cantColores2 ? cantColores1 : cantColores2;    

    printf("Cantidad de colores: %d\n", cantColores3);

    DestruirGrafo(g);
    
    return 0;
}
