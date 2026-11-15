
#include <stdio.h>
#include <string.h>

#define MAX 5
#define LARGO 50

void mostrarMenu();
int buscarProducto(char nombres[][LARGO], int cantidad, char nombre[]);
void ingresarProducto(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int *cantidad);
void mostrarProductos(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int cantidad);
void editarProducto(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int cantidad);
void eliminarProducto(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int *cantidad);
void calcularProduccion(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int cantidad);

int main() {
    char nombres[MAX][LARGO];
    int cantidades[MAX];
    float tiempos[MAX], recursos[MAX];
    int cantidad = 0, opcion;

    do {
        mostrarMenu();

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarProducto(nombres, cantidades, tiempos, recursos, &cantidad);
                break;

            case 2:
                mostrarProductos(nombres, cantidades, tiempos, recursos, cantidad);
                break;

            case 3:
                editarProducto(nombres, cantidades, tiempos, recursos, cantidad);
                break;

            case 4:
                eliminarProducto(nombres, cantidades, tiempos, recursos, &cantidad);
                break;

            case 5:
                calcularProduccion(nombres, cantidades, tiempos, recursos, cantidad);
                break;

            case 6:
                printf("\nPrograma finalizado.\n");
                break;

            default:
                printf("\nOpcion no valida.\n");
        }

    } while (opcion != 6);

    return 0;
}

void mostrarMenu() {
    printf("\n===== SISTEMA DE PRODUCCION =====\n");
    printf("1. Ingresar producto\n");
    printf("2. Mostrar productos\n");
    printf("3. Editar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Calcular produccion\n");
    printf("6. Salir\n");
}

int buscarProducto(char nombres[][LARGO], int cantidad, char nombre[]) {
    int i;

    for (i = 0; i < cantidad; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            return i;
        }
    }

    return -1;
}

void ingresarProducto(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int *cantidad) {
    char nombre[LARGO];

    if (*cantidad >= MAX) {
        printf("\nYa se ingreso el maximo de cinco productos.\n");
        return;
    }

    printf("Nombre del producto: ");
    scanf(" %49[^\n]", nombre);

    if (buscarProducto(nombres, *cantidad, nombre) != -1) {
        printf("Ese producto ya existe.\n");
        return;
    }

    printf("Cantidad demandada: ");
    scanf("%d", &cantidades[*cantidad]);

    printf("Tiempo de fabricacion por unidad (horas): ");
    scanf("%f", &tiempos[*cantidad]);

    printf("Recursos por unidad: ");
    scanf("%f", &recursos[*cantidad]);

    if (cantidades[*cantidad] < 0 || tiempos[*cantidad] < 0 || recursos[*cantidad] < 0) {
        printf("No se aceptan valores negativos.\n");
        return;
    }

    strcpy(nombres[*cantidad], nombre);

    (*cantidad)++;

    printf("\nProducto ingresado correctamente.\n");
}

void mostrarProductos(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int cantidad) {
    int i;

    if (cantidad == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\n===== PRODUCTOS REGISTRADOS =====\n");

    for (i = 0; i < cantidad; i++) {
        printf("\nProducto: %s\n", nombres[i]);
        printf("Cantidad: %d\n", cantidades[i]);
        printf("Tiempo por unidad: %.2f horas\n", tiempos[i]);
        printf("Recursos por unidad: %.2f\n", recursos[i]);
    }
}

void editarProducto(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int cantidad) {
    char nombre[LARGO];
    int pos;

    printf("Ingrese el nombre del producto que desea editar: ");
    scanf(" %49[^\n]", nombre);

    pos = buscarProducto(nombres, cantidad, nombre);

    if (pos == -1) {
        printf("No se encontro el producto.\n");
        return;
    }

    printf("Nuevo nombre: ");
    scanf(" %49[^\n]", nombres[pos]);

    printf("Nueva cantidad demandada: ");
    scanf("%d", &cantidades[pos]);

    printf("Nuevo tiempo por unidad: ");
    scanf("%f", &tiempos[pos]);

    printf("Nuevos recursos por unidad: ");
    scanf("%f", &recursos[pos]);

    if (cantidades[pos] < 0 || tiempos[pos] < 0 || recursos[pos] < 0) {
        printf("Los valores no pueden ser negativos.\n");
        return;
    }

    printf("\nProducto actualizado correctamente.\n");
}

void eliminarProducto(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int *cantidad) {
    char nombre[LARGO];
    int pos, i;

    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf(" %49[^\n]", nombre);

    pos = buscarProducto(nombres, *cantidad, nombre);

    if (pos == -1) {
        printf("No se encontro el producto.\n");
        return;
    }

    for (i = pos; i < *cantidad - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    (*cantidad)--;

    printf("\nProducto eliminado correctamente.\n");
}

void calcularProduccion(char nombres[][LARGO], int cantidades[], float tiempos[], float recursos[], int cantidad) {
    int i;

    float totalTiempo = 0;
    float totalRecursos = 0;

    float tiempoDisponible;
    float recursosDisponibles;

    if (cantidad == 0) {
        printf("\nPrimero debe ingresar productos.\n");
        return;
    }

    printf("Horas disponibles para produccion: ");
    scanf("%f", &tiempoDisponible);

    printf("Cantidad total de recursos disponibles: ");
    scanf("%f", &recursosDisponibles);

    if (tiempoDisponible < 0 || recursosDisponibles < 0) {
        printf("Los limites no pueden ser negativos.\n");
        return;
    }

    printf("\n===== DETALLE DE PRODUCCION =====\n");

    for (i = 0; i < cantidad; i++) {

        float t = cantidades[i] * tiempos[i];
        float r = cantidades[i] * recursos[i];

        totalTiempo = totalTiempo + t;
        totalRecursos = totalRecursos + r;

        printf("\nProducto: %s\n", nombres[i]);
        printf("Tiempo necesario: %.2f horas\n", t);
        printf("Recursos necesarios: %.2f\n", r);
    }

    printf("\n===== RESULTADOS FINALES =====\n");

    printf("Tiempo total necesario: %.2f horas\n", totalTiempo);
    printf("Recursos totales necesarios: %.2f\n", totalRecursos);

    if (totalTiempo <= tiempoDisponible && totalRecursos <= recursosDisponibles) {

        printf("\nLa fabrica SI puede cumplir con la demanda.\n");

    } else {

        printf("\nLa fabrica NO puede cumplir con toda la demanda.\n");

        if (totalTiempo > tiempoDisponible) {
            printf("Faltan horas de produccion.\n");
        }

        if (totalRecursos > recursosDisponibles) {
            printf("Faltan recursos.\n");
        }
    }
}
