#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//Creacion de las 4 librerias necesarias para el codigo

struct OrdenTrabajo//Struct para almacenar los datos de cada orden
{
    int numeroOrden;
    char tipoEquipo[50];
    char servicio[50];
    float costo;
    char fechaCreacion[20];
};

struct OrdenTrabajo leerOrdenTrabajo(FILE *archivo)
{
    struct OrdenTrabajo orden;
    fscanf(archivo, "%d %s %s %f %s",
           &orden.numeroOrden, orden.tipoEquipo, orden.servicio, &orden.costo, orden.fechaCreacion);
    return orden;
}

struct OrdenTrabajo buscarOrdenTrabajo(FILE *archivo, int numeroOrden)//Creacion de la orden de trabajo
{
    struct OrdenTrabajo orden;
    while (!feof(archivo))//Lee la orden del trabajo y la almacena con if y while
    {
        orden = leerOrdenTrabajo(archivo);
        if (orden.numeroOrden == numeroOrden)
        {
            return orden;
        }
    }
    orden.numeroOrden = -1;
    return orden;
}

void escribirOrdenTrabajo(FILE *archivo, struct OrdenTrabajo orden)
{
    fprintf(archivo, "%d %s %s %.2f %s\n",
            orden.numeroOrden, orden.tipoEquipo, orden.servicio, orden.costo, orden.fechaCreacion);
}//Si la opcion del usuario es escribir la orden se crea con un void y la busca dentro del archivo plano con la ayuda de los punteros

void actualizarOrdenTrabajo(FILE *archivo, struct OrdenTrabajo orden)//Si desea que se edite una orden se crea con un void y la busca dentro del archivo plano con la yuda de los punteros
{
    FILE *archivoTemporal = fopen("temp.txt", "w");
    struct OrdenTrabajo ordenActual;
    while (!feof(archivo))//La busca una a una con while y descarta cada caso con if o else
    {
        ordenActual = leerOrdenTrabajo(archivo);
        if (ordenActual.numeroOrden == orden.numeroOrden)
        {
            escribirOrdenTrabajo(archivoTemporal, orden);
        }
        else
        {
            escribirOrdenTrabajo(archivoTemporal, ordenActual);
        }
    }
    fclose(archivo);
    fclose(archivoTemporal);
    remove("datos.txt");
    rename("temp.txt", "datos.txt");//Cierra el archivo plano
}

void eliminarOrdenTrabajo(FILE *archivo, int numeroOrden)//Si la opcion es eliminar una orden se crea un void con ayuda de los punteros para que busque en el archivo plano
{
    FILE *archivoTemporal = fopen("temp.txt", "w");
    struct OrdenTrabajo orden;
    int eliminado = 0;
    while (!feof(archivo))//Lo busca con while con las condiciones de if o else para ver se encuentra, si no tira que no exste la orden
    {
        orden = leerOrdenTrabajo(archivo);
        if (orden.numeroOrden != numeroOrden)
        {
            escribirOrdenTrabajo(archivoTemporal, orden);
        }
        else
        {
            eliminado = 1;
        }
    }
    fclose(archivo);
    fclose(archivoTemporal);
    remove("datos.txt");
    rename("temp.txt", "datos.txt");

    if (eliminado)
    {
        printf("Orden de trabajo eliminada correctamente.\n");
    }
    else
    {
        printf("No se encontró la orden de trabajo con el número %d.\n", numeroOrden);
    }
}

void mostrarOrdenTrabajo(struct OrdenTrabajo orden)//Creacion de void para dentro de ordentrabajo pra imprimir cada dato dentro de la terminal si lo desea el usuario
{
    printf("Numero de orden: %d\n", orden.numeroOrden);
    printf("Tipo de equipo: %s\n", orden.tipoEquipo);
    printf("Servicio: %s\n", orden.servicio);
    printf("Costo: %.2f\n", orden.costo);
    printf("Fecha de creacion: %s\n", orden.fechaCreacion);
}

void obtenerFechaHoraActual(char fechaHora[])//Se obtiene la hora dentro de fechahora con ayuda de void y strftme
{
    time_t tiempoActual = time(NULL);
    struct tm *tiempoLocal = localtime(&tiempoActual);
    strftime(fechaHora, 20, "%d/%m/%Y %H:%M:%S", tiempoLocal);
}

int main()
{
    FILE *archivo;

    if ((archivo = fopen("datos.txt", "r")) == NULL)
    {
        if ((archivo = fopen("datos.txt", "w")) == NULL)
        {
            printf("No se pudo abrir o crear el archivo datos.txt.\n");
            return 1;
        }
    }

    fclose(archivo);//Se abre el archivo plano

    archivo = fopen("datos.txt", "a+");
    if (archivo == NULL)
    {
        printf("No se pudo abrir o crear el archivo datos.txt.\n");
        return 1;
    }

    int opcion;//Creacion de las opciones del programa
    do
    {
        printf("\nMENU:\n");
        printf("1. Agregar una orden de trabajo\n");
        printf("2. Buscar una orden de trabajo\n");
        printf("3. Eliminar una orden de trabajo\n");
        printf("4. Modificar una orden de trabajo\n");
        printf("5. Salir\n");
        printf("Ingrese el número de la opción deseada: ");
        scanf("%d", &opcion);

        switch (opcion)//Swich para que aga la accion que desee el usuario de 1 a 5
        {
        case 1:
        {
            struct OrdenTrabajo nuevaOrden;
            printf("Ingrese el número de orden: ");
            scanf("%d", &nuevaOrden.numeroOrden);
            printf("Ingrese el tipo de equipo: ");
            scanf("%s", nuevaOrden.tipoEquipo);
            printf("Ingrese el servicio: ");
            scanf("%s", nuevaOrden.servicio);
            printf("Ingrese el costo: ");
            scanf("%f", &nuevaOrden.costo);
            obtenerFechaHoraActual(nuevaOrden.fechaCreacion);
            escribirOrdenTrabajo(archivo, nuevaOrden);
            printf("Orden de trabajo agregada correctamente.\n");
            break;
        }
        case 2:
        {
            int numeroBuscar;
            printf("Ingrese el número de orden a buscar: ");
            scanf("%d", &numeroBuscar);
            struct OrdenTrabajo ordenEncontrada = buscarOrdenTrabajo(archivo, numeroBuscar);
            if (ordenEncontrada.numeroOrden != -1)
            {
                printf("Orden de trabajo encontrada:\n");
                mostrarOrdenTrabajo(ordenEncontrada);
            }
            else
            {
                printf("No se encontró la orden de trabajo con el número %d.\n", numeroBuscar);
            }
            break;
        }
        case 3:
        {
            int numeroEliminar;
            printf("Ingrese el número de orden a eliminar: ");
            scanf("%d", &numeroEliminar);
            eliminarOrdenTrabajo(archivo, numeroEliminar);
            break;
        }
        case 4:
        {
            int numeroModificar;
            printf("Ingrese el número de orden a modificar: ");
            scanf("%d", &numeroModificar);
            fclose(archivo);
            archivo = fopen("datos.txt", "r");
            if (archivo == NULL)
            {
                printf("No se pudo abrir el archivo datos.txt.\n");
                return 1;
            }
            struct OrdenTrabajo ordenModificar = buscarOrdenTrabajo(archivo, numeroModificar);
            fclose(archivo);
            if (ordenModificar.numeroOrden != -1)
            {
                printf("Orden de trabajo encontrada:\n");
                mostrarOrdenTrabajo(ordenModificar);

                archivo = fopen("datos.txt", "r+");
                if (archivo == NULL)
                {
                    printf("No se pudo abrir o crear el archivo datos.txt.\n");
                    return 1;
                }
                printf("Ingrese el nuevo tipo de equipo: ");
                scanf("%s", ordenModificar.tipoEquipo);
                printf("Ingrese el nuevo servicio: ");
                scanf("%s", ordenModificar.servicio);
                printf("Ingrese el nuevo costo: ");
                scanf("%f", &ordenModificar.costo);
                obtenerFechaHoraActual(ordenModificar.fechaCreacion);

                actualizarOrdenTrabajo(archivo, ordenModificar);
                fclose(archivo);
                archivo = fopen("datos.txt", "a+");
                if (archivo == NULL)
                {
                    printf("No se pudo abrir o crear el archivo datos.txt.\n");
                    return 1;
                }
                printf("Orden de trabajo modificada correctamente.\n");
            }
            else
            {
                printf("No se encontró la orden de trabajo con el número %d.\n", numeroModificar);
            }
            break;
        }
        case 5:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción inválida. Por favor, ingrese un número válido.\n");
        }

        fclose(archivo);
        archivo = fopen("datos.txt", "a+");
        if (archivo == NULL)
        {
            printf("No se pudo abrir o crear el archivo datos.txt.\n");
            return 1;
        }
    } while (opcion != 5);//Se repite hasta que ponga una opcion diferente de 5 que es salir

    fclose(archivo);//Cierra el archivo
    return 0;
}