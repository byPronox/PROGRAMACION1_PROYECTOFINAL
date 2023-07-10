#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 

struct OrdenTrabajo {
    int numeroOrden;
    char tipoEquipo[50];
    char servicio[50];
    float costo;
    char fechaCreacion[20];
};

struct OrdenTrabajo leerOrdenTrabajo(FILE* archivo) {
    struct OrdenTrabajo orden;
    fscanf(archivo, "%d %s %s %f %s",
&orden.numeroOrden, orden.tipoEquipo, orden.servicio, &orden.costo, orden.fechaCreacion);
    return orden;
}

struct OrdenTrabajo buscarOrdenTrabajo(FILE* archivo, int numeroOrden) {
    struct OrdenTrabajo orden;
    while (!feof(archivo)) {
        orden = leerOrdenTrabajo(archivo);
        if (orden.numeroOrden == numeroOrden) {
            return orden;
        }
    }
    orden.numeroOrden = -1;
    return orden;
}