#include "APIG23.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_U32 4294967295

// Estructuras y Funciones auxiliares

/* Estructura (simboliza una tupla) que representa un lado del grafo. */
typedef struct EdgeSt {
    u32 a;
    u32 b;
} EdgeSt;

/*
 * @brief Compara dos lados del grafo.
 * @param a puntero a un lado del grafo.
 * @param b puntero a un lado del grafo.
 * @returns -1 si a < b, 1 si a > b.
 */
static int cmpLado(const void* a, const void* b) {
    const EdgeSt *p = a, *q = b;
    if (p->a < q->a) {
        return -1;
    }
    if (p->a > q->a) {
        return 1;
    }
    if (p->b < q->b) {
        return -1;
    }
    if (p->b > q->b) {
        return 1;
    }
    /* Si se llega hasta acá, quiere decir que los lados son iguales. */
    fprintf(stderr, "Hay un lado repetido.\n");
    return 0;
}


/*
 * @brief Lee los lados del grafo desde el stdin.
 * @param lista_de_lados lista de lados del grafo.
 * @param G el grafo del que se desean leer los lados.
 * @returns La lista de lados del grafo.
 * 
 * @bug Debemos evitar el uso de fgets, ya que las líneas pueden ser 
 * arbitrariamente grandes y causar comportamientos inesperados si se supera
 * el tamaño del buffer de fgets.
 */
static EdgeSt* LeerLados(Grafo G) {
    assert(G!=NULL);
    bool es_p_edge = false;
    u32 cant_lados = 0;
    u32 nombre_a = 0, nombre_b = 0;
    int res;
    char curr_char;
    /*
    Leemos el archivo hasta encontrar la linea que empieza con 'p edge'.
    */ 
    curr_char = getchar();
    while (!es_p_edge  && curr_char != EOF) {
        switch (curr_char) {
            case 'c':
                while (curr_char != '\n') {
                    curr_char = getchar();
                    if (curr_char == EOF) {
                        return NULL;
                    }   
                }
                break; // si comenzó con un comentario, lo ignoramos
            case 'p':
                res = scanf(" edge %u %u", &(G->n), &(G->m));
                if (res != 2) {
                    fprintf(stderr, "Error al leer la cantidad de vértices y lados.\n");
                    exit(1);
                }
                es_p_edge = true;
                break;
            case '\n':
                break; // si es una linea vacia, la ignoramos
            case EOF:
                return NULL;
                /* Si llegamos al EOF, es un error. */
        }
        curr_char = getchar();
    }
    /* Lista que almacena los lados del grafo. */
    EdgeSt *lista_de_lados = calloc(G->m * 2, sizeof(EdgeSt));
    /*  
    Leemos los lados mientras no se haya leido la cantidad de lados que se 
    esperan, y no se haya llegado al EOF.
    */
    while(cant_lados < G->m && (curr_char=getchar())!=EOF) {
        if(curr_char =='e') {
            res = scanf(" %u %u ", &nombre_a, &nombre_b);
            if (res != 2) {
                free(lista_de_lados);
                return NULL; // si no se pudo leer el lado, es un error
            }
            /* Colocamos el vértice 1~2 */
            lista_de_lados[cant_lados * 2].a = nombre_a;
            lista_de_lados[cant_lados * 2].b = nombre_b;
            /* Colocamos el vértice 2~1 */
            lista_de_lados[cant_lados * 2 + 1].a = nombre_b;
            lista_de_lados[cant_lados * 2 + 1].b = nombre_a;
            cant_lados++;
        }
        else if(curr_char !='e' && curr_char !='\n'){                   
            printf("Formato de archivo incorrecto\n");
            printf("Se esperaba 'e' y se encontró '%c'\n", curr_char);
        }
    }

    /*
    Si salimos del bucle y no leímos la cantidad de lados esperados, es un error.
    */
    if (G->m != cant_lados) {
        fprintf(stderr, "Hay menos cantidad de lados que los especificados\n");
        free(lista_de_lados);
        return NULL;
    }

    /* Ordenamos la lista de lados */
    qsort(lista_de_lados, G->m * 2, sizeof(EdgeSt), cmpLado);
    
    return lista_de_lados;
}


static u32 BusquedaBinaria(Vertice *arreglo_de_vertices, u32 valor, int length) {
    u32 izq  = 0; 
    u32 der = length-1;
    u32 mit = 0;

    while(izq <= der) {
        mit = (izq + der)/2; 
        
        if (arreglo_de_vertices[mit]->nombre == valor) {
            return mit;
        }
        else if (arreglo_de_vertices[mit]->nombre < valor) {
            izq = mit + 1;
        }
        else {
            der = mit- 1;
        }
    }
    return -1;
}

// Construcción / Destrucción

// Debe ser a lo sumo O(mlogm)
Grafo ConstruirGrafo() {

    Grafo G = malloc(sizeof(struct GrafoSt));
    EdgeSt *arreglo_de_lados = NULL;
    
    arreglo_de_lados = LeerLados(G);
    if (arreglo_de_lados == NULL) {
        free(G);
        return NULL; //Si no se pudo leer los lados, devolvemos NULL
    }

    //Creamos el arreglo que contiene a los vértices.
    Vertice *arreglo_de_vertices = calloc(G->n, sizeof(VerticeSt));

    u32 vertice;
    u32 vertice_ant = arreglo_de_lados[0].a;
    u32 j = 0;
    u32 max_grado = 1;

    // Recorremos el arreglo de lados y creamos el arreglo de vértices.
    for (u32 i = 0u; i < G->m*2; i++) {
        vertice = arreglo_de_lados[i].a;
        /* Si el vértice es distinto al anterior, o es el primer vértice,
            lo agregamos al arreglo de vértices. */
        if (i == 0 || vertice != vertice_ant) {
            arreglo_de_vertices[j] = calloc(1,sizeof(struct VerticeSt));
            arreglo_de_vertices[j]->nombre = vertice; 
            arreglo_de_vertices[j]->indice  = i; 
            arreglo_de_vertices[j]->grado  = 1;
        
            vertice_ant = vertice;
            j++;
        } else {
            arreglo_de_vertices[j-1]->grado++; // Si el vértice es igual al anterior, aumentamos su grado.
            if(arreglo_de_vertices[j-1]->grado > max_grado){
                // Si el grado del vértice es mayor al máximo, actualizamos el máximo.
                max_grado = arreglo_de_vertices[j-1]->grado ; 
            }
         }
    }

    //Creamos el arreglo con los índices de los vecinos de i
    u32 *arreglo_indices_vecinos = calloc(2*G->m,sizeof(u32));
    u32 nombre_vecino;
    u32 indice_vecino;

    for (u32 i = 0u; i < 2*G->m; i++) {
        nombre_vecino = arreglo_de_lados[i].b;
        indice_vecino = BusquedaBinaria(arreglo_de_vertices, nombre_vecino, G->n);
        
        arreglo_indices_vecinos[i] = indice_vecino;
       
    }

    G->vertices = arreglo_de_vertices;
    G->lista_de_adyacencia = arreglo_indices_vecinos;
    G->delta = max_grado;
    free(arreglo_de_lados);
    return G;
}


// Debe ser a lo sumo O(m)
void DestruirGrafo(Grafo G) {
    // Liberamos memoria de los vértices.
    for (u32 i = 0; i < G->n; i++) {
        free(G->vertices[i]);
        G->vertices[i] = NULL;
    }
    free(G->vertices);
    G->vertices = NULL;
    
    // Liberamos memoria de los vecinos 
    free(G->lista_de_adyacencia);
    G->lista_de_adyacencia = NULL;

    // Liberamos memoria del grafo.
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
    assert(G!=NULL);
    return G->delta;
}



// Funciones de extraccion de informacion de vertices 

// Debe ser O(1)
u32 Nombre(u32 i, Grafo G) {
    return G->vertices[i]->nombre;
}

// Debe ser O(1)
u32 Grado(u32 i, Grafo G) {
    return G->vertices[i]->grado;
}

// Debe ser O(1)
u32 IndiceVecino(u32 j, u32 i, Grafo G) {
    u32 indice = 0;
    if (G->n > i && Grado(i,G) > j) {
        u32 indice_vertice = G->vertices[i]->indice;
        indice = G->lista_de_adyacencia[indice_vertice + j];
    } else {
        indice = MAX_U32; // Retornamos el MAX_U32 para indicar que no existe el vecino.
    }
    
    return indice;
}