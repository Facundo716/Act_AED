#include <stdio.h>
#include "validaciones.h"

void LimpiarPantalla() {
    printf("\033[2J\033[H");
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leerEntero(int min, int max) {
    int valor, estado;
    while (1) {
        estado = scanf("%d", &valor);
        if (estado != 1 || valor < min || valor > max) {
            printf("Error. Ingrese un numero valido entre %d y %d: ", min, max);
            limpiarBuffer();
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}

float leerFlotante(float min, float max) {
    float valor;
    int estado;
    while (1) {
        estado = scanf("%f", &valor);
        // FIX: Ahora evitamos leer valores nulos (0)
        if (estado != 1 || valor <= min || valor > max) {
            printf("Error. Ingrese un decimal valido (Mayor a %.2f y hasta %.2f): ", min, max);
            limpiarBuffer();
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}
