// Probando el main 
#include <stdio.h>
#include <stdbool.h>
#include "artemis.h"
#include "validaciones.h"

void Menu() {
    printf("   SIMULADOR ARTEMIS: ESCENARIO 4        \n");
    printf("1. Ingresar parametros de simulacion\n");
    printf("2. Calcular Trabajo y Desaceleracion\n");
    printf("3. Calcular Fuerza de Impacto en Oceano\n");
    printf("4. Evaluar Ventana de Angulo de Reingreso\n");
    printf("5. Generar Reporte Final (Historial)\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int opcion;
    bool datos_cargados = false; // Variable bandera para el control del program 

    do {
        Menu();
        // Lectura temporal... Luego se tiene que reemplazar x leerEntero(1, 6)
        scanf("%d", &opcion); 

        switch (opcion) {
            case 1:
                printf("\n[Modulo en proceso ... Aca ingresan los datos por teclado]\n");
                datos_cargados = true; // Simulamos que se cargaron los datos, temporalmente para probar 
                break;
            case 2:
                if (datos_cargados) {
                    printf("\n[Modulo en construccion: Calculo de Fisica y Trabajo]\n");
                } else {
                    printf("\nError: Debe ingresar parametros primero (Opcion 1).\n");
                }
                break;
            case 3:
                if (datos_cargados) {
                    printf("\n[Modulo en construccion: Calculo de Impacto en Oceano]\n");
                } else {
                    printf("\nError: Debe ingresar parametros primero (Opcion 1).\n");
                }
                break;
            case 4:
                if (datos_cargados) {
                    printf("\n[Modulo en construccion: Evaluacion de Angulo]\n");
                } else {
                    printf("\nError: Debe ingresar parametros primero (Opcion 1).\n");
                }
                break;
            case 5:
                printf("\n[Modulo en construccion: Reporte Historial]\n");
                break;
            case 6:
                printf("\nSaliendo del simulador de vuelo...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}