#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definidas las 3 librerias nesesarias
#define MAX_ORDERS 100
#define FILENAME "ordenes.txt"
//Definicion de las 2 constantes del progrma
struct OrdenTrabajo {//Struct para gurdad todos los datos
    int numero;
    char fecha[11];
    char tipoTrabajo[50];
    float costoServicio;
};

struct OrdenTrabajo ordenes[MAX_ORDERS];
int numOrdenes = 0;
//Abrimos el archivo plano con fopen y imprimimos todos los datos ingresados con printf
void guardarOrdenes() {
    FILE *archivo = fopen(FILENAME, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < numOrdenes; i++) {
        fprintf(archivo, "%d %s %s %.2f\n", ordenes[i].numero, ordenes[i].fecha, ordenes[i].tipoTrabajo, ordenes[i].costoServicio);
    }

    fclose(archivo);//Se cierra el .txt
}
//Creacion de la deteccion de los datos del archivo plano
void cargarOrdenes() {
    FILE *archivo = fopen(FILENAME, "r");
    if (archivo == NULL) {
        printf("No se encontró el archivo. Se creará uno nuevo al guardar las órdenes.\n");
        return;
    }

    int numero;
    char fecha[11];
    char tipoTrabajo[50];
    float costoServicio;

    while (fscanf(archivo, "%d %s %s %f", &numero, fecha, tipoTrabajo, &costoServicio) == 4) {//Se escanea la orden
        struct OrdenTrabajo orden;
        orden.numero = numero;
        strcpy(orden.fecha, fecha);
        strcpy(orden.tipoTrabajo, tipoTrabajo);
        orden.costoServicio = costoServicio;

        ordenes[numOrdenes++] = orden;
    }

    fclose(archivo);//Se cierra el .txt
}
//Si la opcion es agregar la orden se crea un void donde:
void agregarOrden() {
    if (numOrdenes == MAX_ORDERS) {
        printf("Error: No se pueden agregar más órdenes de trabajo.\n");//Si se alcanza el maximo de oredenes no se almacenan
        return;
    }

    struct OrdenTrabajo nuevaOrden;//Se pregunta al usurio con printf cada dato
    printf("Número de orden: ");
    scanf("%d", &nuevaOrden.numero);
    printf("Fecha (YYYY-MM-DD): ");
    scanf("%s", nuevaOrden.fecha);
    printf("Tipo de trabajo: ");
    scanf("%s", nuevaOrden.tipoTrabajo);
    printf("Costo de servicio: ");
    scanf("%f", &nuevaOrden.costoServicio);

    ordenes[numOrdenes++] = nuevaOrden;

    printf("Orden de trabajo agregada con éxito.\n");
    guardarOrdenes();
}
//Si desea mostrar las ordenes se las crea con void:
void mostrarOrdenes() {
    if (numOrdenes == 0) {
        printf("No hay órdenes de trabajo registradas.\n");//Si no existen ordenes osea == 0 retira que no hay
        return;
    }

    printf("Número\tFecha\t\tTipo de Trabajo\t\tCosto de Servicio\n"); //Imprime todos los datos de cada orden del archivo .txt
    for (int i = 0; i < numOrdenes; i++) {
        printf("%d\t%s\t%s\t\t%.2f\n", ordenes[i].numero, ordenes[i].fecha, ordenes[i].tipoTrabajo, ordenes[i].costoServicio);
    }
}
// Si desea editar la orden el usurio de crea otro void con:
void editarOrden() {
    if (numOrdenes == 0) {//Si no existen ordenes creadas retira que no hay
        printf("No hay órdenes de trabajo registradas.\n");
        return;
    }

    int numero;//Solicita el numero de la orden y lo escanea con scanf
    printf("Ingrese el número de la orden de trabajo que desea editar: ");
    scanf("%d", &numero);

    int indice = -1;//Busca el numero de la orden solicitada con un for
    for (int i = 0; i < numOrdenes; i++) {
        if (ordenes[i].numero == numero) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {//Si no hay la orden ingresada retira un error
        printf("Error: Número de orden de trabajo inválido.\n");
        return;
    }

    struct OrdenTrabajo *orden = &ordenes[indice];//Imprime cada opcion para que el usuario las edite

    printf("Fecha (YYYY-MM-DD) [%s]: ", orden->fecha);
    scanf("%s", orden->fecha);
    printf("Tipo de trabajo [%s]: ", orden->tipoTrabajo);
    scanf("%s", orden->tipoTrabajo);
    printf("Costo de servicio [%.2f]: ", orden->costoServicio);
    scanf("%f", &orden->costoServicio);

    printf("Orden de trabajo actualizada con éxito.\n");
    guardarOrdenes();
}
//Si desea borrar una orden se crea un void con:
void borrarOrden() {
    if (numOrdenes == 0) {
        printf("No hay órdenes de trabajo registradas.\n");//Si el numero de las ordenes es 0 retorna que no hay
        return;
    }

    int numero;
    printf("Ingrese el número de la orden de trabajo que desea borrar: ");//Se escanea la orden que desea borrar
    scanf("%d", &numero);

    int indice = -1;//Escanea al documento plano para la orden solicitada con un for
    for (int i = 0; i < numOrdenes; i++) {
        if (ordenes[i].numero == numero) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {//Si no existe se retorna que es invalido
        printf("Error: Número de orden de trabajo inválido.\n");
        return;
    }

    for (int i = indice; i < numOrdenes - 1; i++) {//Se busca la orden para borrarla con un for y numordenes
        ordenes[i] = ordenes[i + 1];
    }

    numOrdenes--;

    printf("Orden de trabajo borrada con éxito.\n");
    guardarOrdenes();
}

int main() {
    cargarOrdenes();

    int opcion;

    while (1) {//Se crea un while con swich para el menu dentro del main para la terminal del programa
        printf("\n--- Sistema de Órdenes de Trabajo ---\n");
        printf("1. Agregar orden de trabajo\n");
        printf("2. Mostrar órdenes de trabajo\n");
        printf("3. Editar orden de trabajo\n");
        printf("4. Borrar orden de trabajo\n");
        printf("5. Guardar cambios y salir\n");
        printf("Ingrese el número de opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarOrden();
                break;
            case 2:
                mostrarOrdenes();
                break;
            case 3:
                editarOrden();
                break;
            case 4:
                borrarOrden();
                break;
            case 5:
                printf("Guardando cambios y saliendo del programa...\n");
                guardarOrdenes();
                exit(0);
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    }

    return 0;
}