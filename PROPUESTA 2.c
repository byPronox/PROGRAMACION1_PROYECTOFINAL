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

void eliminarOrdenTrabajo(FILE* archivo, int numeroOrden) {
    FILE* archivoTemporal = fopen("temp.txt", "w");
    struct OrdenTrabajo orden;
    int eliminado = 0;
    while (!feof(archivo)) {
        orden = leerOrdenTrabajo(archivo);
        if (orden.numeroOrden != numeroOrden) {
            escribirOrdenTrabajo(archivoTemporal, orden);
        } else {
            eliminado = 1;
        }
    }
    fclose(archivo);
    fclose(archivoTemporal);
    remove("datos.txt");
    rename("temp.txt", "datos.txt");

 

    if (eliminado) {
        printf("Orden de trabajo eliminada correctamente.\n");
    } else {
        printf("No se encontró la orden de trabajo con el número %d.\n", numeroOrden);
    }
}

void mostrarOrdenTrabajo(struct OrdenTrabajo orden) {
    printf("Numero de orden: %d\n", orden.numeroOrden);
    printf("Tipo de equipo: %s\n", orden.tipoEquipo);
    printf("Servicio: %s\n", orden.servicio);
    printf("Costo: %.2f\n", orden.costo);
    printf("Fecha de creacion: %s\n", orden.fechaCreacion);
}

void obtenerFechaHoraActual(char fechaHora[]) {
    time_t tiempoActual = time(NULL);
    struct tm* tiempoLocal = localtime(&tiempoActual);
    strftime(fechaHora, 20, "%d/%m/%Y %H:%M:%S", tiempoLocal);
}


