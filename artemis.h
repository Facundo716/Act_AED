#ifndef ARTEMIS_H
#define ARTEMIS_H

#define GRAVEDAD 9.80
#define M_ORION 10400.0
#define VEL_REINGRESO 11000.0
#define H_REINGRESO 120000.0
#define H_PARACAIDAS 2500.0
#define VEL_PARACAIDAS 25.0
#define VEL_IMP 8.0
#define MAX_HISTORIAL 10  // Numero maximo de simulaciones para guardarr

typedef struct {
    float t_desacel;
    float prof_hundimiento;
    float ang_reingreso;
    float w_rozamiento;
    float desacel_media;
    float fuerza_imp;
} Estado_Orion;

void Inicializar_Simulacion(Estado_Orion *nave);
void Calcular_Trabajo(Estado_Orion *nave);
void Fuerza_Impacto(Estado_Orion *nave);
void Evaluar_Angulo(Estado_Orion nave);
// Nuevas funciones 
void Guardar_Historial(Estado_Orion historial[], int *cant, Estado_Orion nave);
void Mostrar_Reporte(Estado_Orion historial[], int cant); // <- PUNTO Y COMA AGREGADO

#endif