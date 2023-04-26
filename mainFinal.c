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
    u32 n = NumeroDeVertices(g);
    u32 *orden1 = calloc(n, sizeof(u32));
    u32 *orden2 = calloc(n, sizeof(u32));
    u32 *color1 = calloc(n, sizeof(u32));
    u32 *color2 = calloc(n, sizeof(u32));
    u32 cantColores1, cantColores2, cantColoresMin;
    u32 *aux = NULL;
    
    // Aplicamos el orden natural para la primera corrida de Greedy.
    OrdenNatural(n, orden1);

    // Corremos Greedy una vez con el orden natural.
    u32 cantColores = Greedy(g, orden1, color1);
    printf("Cantidad de colores usando orden natural: %d\n", cantColores);

    // Aplicamos ambos ordenes para las dos siguientes corrida de Greedy (utilizando la primera corrida).
    OrdenImparPar(g->n, orden1, color1);
    OrdenJedi(g, orden2, color1);

    // Corremos Greedy dos veces con los ordenes Impar-Par y Jedi.
    cantColores = Greedy(g, orden1, color1);
    cantColores = Greedy(g, orden2, color2);

    /*
    Corremos Greedy 512 veces con cada uno de los colores, intercambiando
    los coloreos cada 16 iteraciones como se especifica en la consigna.
    En total corremos Greedy 2*32*16+3 = 1027 veces.
    */
    for (u32 i = 0; i < 32; i++) {
        for (u32 j = 0; j < 16; j++) {
            OrdenImparPar(n, orden1, color1);
            cantColores1 = Greedy(g, orden1, color1);

            OrdenJedi(g, orden2, color2);
            cantColores2 =  Greedy(g, orden2, color2);
        }
        aux = color1;
        color1 = color2;
        color2 = aux;
    }

    // Elegimos el coloreo con menor cantidad de colores.
    cantColoresMin = cantColores1 < cantColores2 ? cantColores1 : cantColores2;    
    printf("Cantidad de colores final: %d\n", cantColoresMin);

    // Liberamos la memoria de los arreglos auxiliares.
    free(orden1);
    free(orden2);
    free(color1);
    free(color2);

    DestruirGrafo(g);
    
    return 0;
}
