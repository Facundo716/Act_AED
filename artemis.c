#include <stdio.h>
#include "artemis.h"

void Inicializar_Simulacion(Estado_Orion *nave) {
    nave->t_desacel = 0.0;
    nave->prof_hundimiento = 0.0;
    nave->ang_reingreso = 0.0;
    nave->w_rozamiento = 0.0;
    nave->desacel_media = 0.0;
    nave->fuerza_imp = 0.0;
}

void Calcular_Trabajo(Estado_Orion *nave) {
    float Energia_Inicial = (0.5 * M_ORION * (VEL_REINGRESO * VEL_REINGRESO)) + (M_ORION * GRAVEDAD * H_REINGRESO);
    float Energia_Final = (0.5 * M_ORION * (VEL_PARACAIDAS * VEL_PARACAIDAS)) + (M_ORION * GRAVEDAD * H_PARACAIDAS);
    
    nave->w_rozamiento = Energia_Final - Energia_Inicial;
    
    nave->desacel_media = (VEL_PARACAIDAS - VEL_REINGRESO) / nave->t_desacel;

    printf("\nTrabajo de rozamiento (Joules): %.2f\n", nave->w_rozamiento);
    printf("Desaceleracion media (m/s^2): %.2f\n", nave->desacel_media);
}

void Fuerza_Impacto(Estado_Orion *nave) {
    float Energia_K = 0.5 * M_ORION * (VEL_IMP * VEL_IMP);
    float Fuerza_Neta = Energia_K / nave->prof_hundimiento;
    nave->fuerza_imp = Fuerza_Neta + (M_ORION * GRAVEDAD);
    float Multiplo_Peso = nave->fuerza_imp / (M_ORION * GRAVEDAD);

    printf("\nFuerza promedio del agua (Newton): %.2f\n", nave->fuerza_imp);
    printf("Multiplo del peso de la nave: %.2f\n", Multiplo_Peso);
}

void Evaluar_Angulo(Estado_Orion nave) {
    if ((nave.ang_reingreso >= 5.5) && (nave.ang_reingreso <= 7.0)) {
        printf("\nValor optimo. La nave esta dentro de la ventana segura.\n");
    } else if (nave.ang_reingreso > 7.0) {
        printf("\nAlerta: Angulo muy empinado. Peligro de desaceleracion excesiva!!.\n");
    } else {
        printf("\nAlerta: Angulo muyy bajo. Peligro de rebote atmosferico!!.\n");
    }
}

void Guardar_Historial(Estado_Orion historial[], int *cant, Estado_Orion nave) {
    if (*cant < MAX_HISTORIAL) {
        historial[*cant] = nave;
        *cant += 1;
        printf("\n[Datos de simulacion guardados en el historial]\n");
    } else {
        printf("\nMemoria llena: No se pueden guardar mas simulaciones.\n");
    }
}

void Mostrar_Reporte(Estado_Orion historial[], int cant) {
    if (cant == 0) {
        printf("\nNo hay simulaciones registradas.\n");
    } else {
        printf("\n--- REPORTE HISTORICO DE SIMULACIONES ---\n");
        for(int i = 0; i < cant; i++) {
            printf("Intento Nro %d:\n", i + 1);
            printf("   Angulo (grados): %.2f\n", historial[i].ang_reingreso);
            printf("   Trabajo (Joules): %.2f\n", historial[i].w_rozamiento);
            printf("-----------------------------------------\n");
        }
    }
}


