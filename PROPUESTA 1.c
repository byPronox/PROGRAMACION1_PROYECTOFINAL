#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDERS 100
#define FILENAME "ordenes.txt"

struct OrdenTrabajo {
    int numero;
    char fecha[11];
    char tipoTrabajo[50];
    float costoServicio;
};

struct OrdenTrabajo ordenes[MAX_ORDERS];
int numOrdenes = 0;

void guardarOrdenes() {
    FILE *archivo = fopen(FILENAME, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < numOrdenes; i++) {
        fprintf(archivo, "%d %s %s %.2f\n", ordenes[i].numero, ordenes[i].fecha, ordenes[i].tipoTrabajo, ordenes[i].costoServicio);
    }

    fclose(archivo);
}