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
    Estado_Orion nave; // Variable temporal para testear la carga de datos .. 
    
    // DECLARACIONES AGREGADAS PARA EL HISTORIAL
    Estado_Orion historial[MAX_HISTORIAL]; 
    int cant_historial = 0;

    Inicializar_Simulacion(&nave);

    do {
        Menu();
        // Lectura temporal... Luego se tiene que reemplazar x leerEntero(1, 6)
        opcion = leerEntero(1, 6); 
    
        switch (opcion) {
            case 1:
                LimpiarPantalla();
                printf("\n--- CARGA DE PARAMETROS ---\n");

                // Uso de la funcion LeerFlotante y evitamos ingresos de ceros y letras 
                printf("Tiempo de desaceleracion (s): ");
                nave.t_desacel = leerFlotante(0.0, 5000.0); 

                printf("Profundidad de hundimiento (m): ");
                nave.prof_hundimiento = leerFlotante(0.0, 50.0);
                
                printf("Angulo de reingreso (grados): ");
                nave.ang_reingreso = leerFlotante(0.0, 90.0);

                datos_cargados = true;
                printf("\n[Parametros cargados exitosamente]\n");
                break;
            case 2:
                LimpiarPantalla();
                if (datos_cargados) {
                    Calcular_Trabajo(&nave); // <- PUNTO Y COMA AGREGADO
                    Guardar_Historial(historial, &cant_historial, nave);
                } else {
                    printf("\nError: Debe ingresar parametros primero (Opcion 1).\n");
                }
                break;
            case 3:
                LimpiarPantalla();
                if (datos_cargados) {
                    Fuerza_Impacto(&nave);
                } else {
                    printf("\nError: Debe ingresar parametros primero (Opcion 1).\n");
                }
                break;
            case 4:
                LimpiarPantalla();
                if (datos_cargados) {
                    Evaluar_Angulo(nave); // Usamos el paso por valor 
                } else {
                    printf("\nError: Debe ingresar parametros primero (Opcion 1).\n");
                }
                break;
            case 5:
                LimpiarPantalla();
                Mostrar_Reporte(historial, cant_historial);
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
