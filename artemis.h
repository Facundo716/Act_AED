#ifndef ARTEMIS_H
#define ARTEMIS_H

// ============================================================================
// AMBIENTE: CONSTANTES FÍSICAS DEL ESCENARIO 4 (REINGRESO Y AMERIZAJE)
// ============================================================================

#define GRAVEDAD_TERRESTRE 9.80
#define MASA_ORION 10400.0          // Masa del módulo de tripulación (kg)
#define ALTITUD_REINGRESO 120000.0  // 120,0 km expresados en metros
#define ALTITUD_PARACAIDAS 2500.0   // 2,50 km expresados en metros
#define VELOCIDAD_REINGRESO 11000.0 // 11,0 km/s expresados en m/s
#define VELOCIDAD_PARACAIDAS 25.0   // Rapidez al abrir paracaídas (m/s)
#define VELOCIDAD_IMPACTO 8.0       // Rapidez final de amerizaje (m/s)

#define ANGULO_MIN_SEGURO 5.5       // Límite inferior ventana (rebote si es menor)
#define ANGULO_MAX_SEGURO 7.0       // Límite superior ventana (desaceleración excesiva)

#define MAX_SIMULACIONES 10         // Tamaño del arreglo para guardar el historial

// ============================================================================
// AMBIENTE: ESTRUCTURA DE DATOS (Equivalente a "Registro" de la cátedra)
// ============================================================================

typedef struct {
    int id_simulacion;              // Número de intento (1, 2, 3...)
    
    // Datos de entrada (ingresados por el usuario)
    float tiempo_desaceleracion;    // Delta t (ej. 400.0 s)
    float profundidad_hundimiento;  // Distancia d en el agua (ej. 1.50 m)
    float angulo_reingreso;         // Ángulo gamma en grados (ej. 6.0°)
    
    // Resultados de salida (calculados por las subacciones)
    double trabajo_rozamiento;      // W_roz en Joules (J)
    float desaceleracion_media;     // a_media en m/s^2
    float fuerzas_g;                // Múltiplos de la gravedad terrestre (g)
    double fuerza_impacto_agua;     // F_prom del agua en Newtons (N)
    float multiplo_peso_nave;       // F_prom expresada como múltiplo del peso
    int estado_angulo;              // 0 = Óptimo, -1 = Rebote (<5.5), 1 = Excesivo (>7.0)
} EstadoOrion;

// ============================================================================
// PROTOTIPOS DE SUBACCIONES (Funciones y Procedimientos que hará Alan)
// ============================================================================
void inicializarSimulacion(EstadoOrion *estado);
void calcularTrabajoYDesaceleracion(EstadoOrion *estado);
void calcularFuerzaImpacto(EstadoOrion *estado);
void evaluarAnguloReingreso(EstadoOrion *estado);

// Subacciones que manejan el Arreglo de Registros (Historial y Estadísticas)
void guardarEnHistorial(EstadoOrion historial[], int *cantidad, EstadoOrion actual);
void generarReporteFinal(const EstadoOrion historial[], int cantidad);

#endif