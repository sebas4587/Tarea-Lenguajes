#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_LINEA 100  

typedef struct TNodo {
    char* linea;
    struct TNodo* siguiente;
} TNodo;

TNodo* crearNodo(char* linea) {
    TNodo* nuevo = (TNodo*)malloc(sizeof(TNodo));
    nuevo->linea = strdup(linea); 
    nuevo->siguiente = NULL;
    return nuevo;
}

TNodo* leerArchivo(const char* nombre) {
    FILE* archivo = fopen(nombre, "r");
    if (archivo == NULL) {
        printf("Error\n");
        return NULL;
    }

    TNodo* cabeza = NULL;
    TNodo* cola = NULL;
    char buffer[TAMANO_LINEA];

    while (fgets(buffer, TAMANO_LINEA, archivo)) {
        buffer[strcspn(buffer, "\n")] = 0;  

        TNodo* nuevoNodo = crearNodo(buffer);
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

void imprimirLista(TNodo* cabeza) {
    TNodo* actual = cabeza;
    while (actual != NULL) {
        printf("%s\n", actual->linea);
        actual = actual->siguiente;
    }
}

void liberarLista(TNodo* cabeza) {
    TNodo* actual = cabeza;
    TNodo* siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual->linea);  
        free(actual);         
        actual = siguiente;
    }
}

int main() {
    const char* nombreArchivo = "tarea.txt";
    TNodo* lista = leerArchivo(nombreArchivo);

    if (lista != NULL) {
        imprimirLista(lista);
        liberarLista(lista); 
    }

    return 0;
}