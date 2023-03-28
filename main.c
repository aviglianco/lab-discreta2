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
    
    
    return 0;
}
