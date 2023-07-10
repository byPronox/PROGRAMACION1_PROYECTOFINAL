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
