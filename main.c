#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 100

typedef struct Nodo {
    char* produccion;
    struct Nodo* siguiente;
} Nodo;

Nodo* crearNodo(char* produccion) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->produccion = strdup(produccion);
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

Nodo* leerArchivoALista(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo '%s'.\n", nombreArchivo);
        return NULL;
    }

    Nodo* cabeza = NULL;
    Nodo* cola = NULL;
    char buffer[MAX_LINEA];

    while (fgets(buffer, MAX_LINEA, archivo)) {
        buffer[strcspn(buffer, "\n")] = 0;

        Nodo* nuevoNodo = crearNodo(buffer);
        if (cabeza == NULL) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            cola = nuevoNodo;
        }
    }

    fclose(archivo);
    return cabeza;
}

void imprimirLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%s\n", actual->produccion);
        actual = actual->siguiente;
    }
}

void liberarLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        Nodo* siguienteNodo = actual->siguiente;
        free(actual->produccion);
        free(actual);
        actual = siguienteNodo;
    }
}

int main() {
    const char* nombreArchivo = "gramatica.txt";
    Nodo* lista = leerArchivoALista(nombreArchivo);

    if (lista != NULL) {
        printf("Producciones leídas del archivo:\n");
        imprimirLista(lista);
        liberarLista(lista);
    } else {
        printf("No se leyeron producciones del archivo.\n");
    }

    return 0;
}