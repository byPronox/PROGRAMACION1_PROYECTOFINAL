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

void escribirOrdenTrabajo(FILE* archivo, struct OrdenTrabajo orden) {
    fprintf(archivo, "%d %s %s %.2f %s\n",
            orden.numeroOrden, orden.tipoEquipo, orden.servicio, orden.costo, orden.fechaCreacion);
}

 

void actualizarOrdenTrabajo(FILE* archivo, struct OrdenTrabajo orden) {
    FILE* archivoTemporal = fopen("temp.txt", "w");
    struct OrdenTrabajo ordenActual;
    while (!feof(archivo)) {
        ordenActual = leerOrdenTrabajo(archivo);
        if (ordenActual.numeroOrden == orden.numeroOrden) {
            escribirOrdenTrabajo(archivoTemporal, orden);
        } else {
            escribirOrdenTrabajo(archivoTemporal, ordenActual);
        }
    }
    fclose(archivo);
    fclose(archivoTemporal);
    remove("datos.txt");
    rename("temp.txt", "datos.txt");
}