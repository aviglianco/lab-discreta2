#include <stdio.h> 
#include <stdlib.h>
#include "EstructuraGrafo23.h"
#include "APIG23.h"

int main(void){
    char path[100]; 

    //Abrir el stdin 
    printf("Ingrese el path del archivo: ");
    scanf("%s", path);

    if (!freopen(path, "r",stdin)){
        printf("Error al abrir el archivo");
        return -1;
    }

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
    // Print the orden array
    printf("Orden: ");
    for (u32 i = 0; i < g->n; i++){
        printf("%d ", orden[i]);
    }
    printf("\n");

    // Print the color array
    printf("Color: ");
    for (u32 i = 0; i < g->n; i++){
        printf("%d ", color[i]);
    }
    printf("\n");

    char check = OrdenImparPar(g->n, orden, color);

    // print the orden array
    printf("Orden Impar-Par: ");
    for (u32 i = 0; i < g->n; i++){
        printf("%d ", orden[i]);
    }
    printf("\n");

    printf("------------------------\n");
    for (unsigned int i = 0; i < 3; i++){
        printf("Ejecución: %d\n", i+1);
        cantColores = Greedy(g, orden, color);
        check = OrdenImparPar(g->n, orden, color);

        // print the color array
        printf("Color: ");
        for (u32 i = 0; i < g->n; i++){
            printf("%d ", color[i]);
        }
        printf("\n");

        // print the orden array
        printf("Orden Impar-Par: ");
        for (u32 i = 0; i < g->n; i++){
            printf("%d ", orden[i]);
        }
        printf("\n");
    }
    
    return 0;
}
