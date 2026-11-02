Accion SimuladorArtemis_Escenario4 Es
Ambiente
    // ------------------- CONSTANTES FÍSICAS ------------------- //
    MASA_ORION = 10400.0: real
    GRAVEDAD = 9.80: real
    ALT_REINGRESO = 120000.0: real
    ALT_PARACAIDAS = 2500.0: real
    VEL_REINGRESO = 11000.0: real
    VEL_PARACAIDAS = 25.0: real
    VEL_IMPACTO = 8.0: real

    // ---------------- DEFINICIÓN DE REGISTROS ----------------- //
    EstadoOrion = Registro
        tiempo_desaceleracion: real
        profundidad_hundimiento: real
        angulo_reingreso: real
        trabajo_rozamiento: real
        desaceleracion_media: real
        fuerza_impacto_agua: real
    FinRegistro

    // ---------------- VARIABLES GLOBALES ---------------------- //
    opcion, cant_historial: entero
    datos_cargados: logico
    nave: EstadoOrion
    historial: Arreglo [1..10] de EstadoOrion

    // ---------------- PROCEDIMIENTOS (SUBACCIONES) ------------- //

    // Usamos 'var' para pasar el registro por referencia y poder modificarlo
    Procedimiento InicializarSimulacion(var estado: EstadoOrion) Es
    Proceso
        estado.tiempo_desaceleracion := 0.0
        estado.profundidad_hundimiento := 0.0
        estado.angulo_reingreso := 0.0
        estado.trabajo_rozamiento := 0.0
        estado.desaceleracion_media := 0.0
        estado.fuerza_impacto_agua := 0.0
    FinProcedimiento

    Procedimiento CalcularFisicaTrabajo(var estado: EstadoOrion) Es
    Ambiente
        energia_inicial, energia_final: real
    Proceso
        energia_inicial := (0.5 * MASA_ORION * (VEL_REINGRESO * VEL_REINGRESO)) + (MASA_ORION * GRAVEDAD * ALT_REINGRESO)
        energia_final := (0.5 * MASA_ORION * (VEL_PARACAIDAS * VEL_PARACAIDAS)) + (MASA_ORION * GRAVEDAD * ALT_PARACAIDAS)
        
        estado.trabajo_rozamiento := energia_final - energia_inicial
        estado.desaceleracion_media := (VEL_PARACAIDAS - VEL_REINGRESO) / estado.tiempo_desaceleracion

        Esc("Trabajo del rozamiento (Joules): ", estado.trabajo_rozamiento)
        Esc("Desaceleracion media (m/s2): ", estado.desaceleracion_media)
    FinProcedimiento

    Procedimiento CalcularFuerzaImpacto(var estado: EstadoOrion) Es
    Ambiente
        energia_cinetica_impacto, fuerza_neta, multiplo_peso: real
    Proceso
        energia_cinetica_impacto := 0.5 * MASA_ORION * (VEL_IMPACTO * VEL_IMPACTO)
        fuerza_neta := energia_cinetica_impacto / estado.profundidad_hundimiento
        estado.fuerza_impacto_agua := fuerza_neta + (MASA_ORION * GRAVEDAD)
        
        multiplo_peso := estado.fuerza_impacto_agua / (MASA_ORION * GRAVEDAD)
        
        Esc("Fuerza promedio del agua (Newtons): ", estado.fuerza_impacto_agua)
        Esc("Multiplo del peso de la nave: ", multiplo_peso)
    FinProcedimiento

    // NO usamos 'var' porque solo consultamos el registro, no lo modificamoss
    Procedimiento EvaluarAngulo(estado: EstadoOrion) Es
    Proceso
        Si (estado.angulo_reingreso >= 5.5) y (estado.angulo_reingreso <= 7.0) entonces
            Esc("OPTIMO: La nave esta dentro de la ventana segura.")
        Sino
            Si (estado.angulo_reingreso > 7.0) entonces
                Esc("ALERTA: Muy empinado. Peligro de desaceleracion excesiva.")
            Sino
                Esc("ALERTA: Muy bajo. Peligro de rebote atmosferico.")
            FinSi
        FinSi
    FinProcedimiento

    // Actualiza el vector histórico sumando un registro nuevo en la posición 'cant'
    Procedimiento GuardarHistorial(var hist: Arreglo [1..10] de EstadoOrion, var cant: entero, estado: EstadoOrion) Es
    Proceso
        Si cant < 10 entonces
            cant := cant + 1
            hist[cant] := estado
        Sino
            Esc("Historial lleno, no se pueden guardar mas intentos.")
        FinSi
    FinProcedimiento

    Procedimiento MostrarReporte(hist: Arreglo [1..10] de EstadoOrion, cant: entero) Es
    Ambiente
        i: entero
    Proceso
        Si cant = 0 entonces
            Esc("No hay simulaciones registradas.")
        Sino
            Esc("--- REPORTE HISTORICO ---")
            Para i := 1 hasta cant hacer
                Esc("Intento Nro: ", i)
                Esc("Angulo: ", hist[i].angulo_reingreso, " - Trabajo (J): ", hist[i].trabajo_rozamiento)
            FinPara
        FinSi
    FinProcedimiento

Proceso

    cant_historial := 0
    datos_cargados := FALSO
    InicializarSimulacion(nave)

    Repetir
        Esc("=========================================")
        Esc("   SIMULADOR ARTEMIS: ESCENARIO 4        ")
        Esc("=========================================")
        Esc("1. Ingresar parametros de simulacion")
        Esc("2. Calcular Trabajo y Desaceleracion")
        Esc("3. Calcular Fuerza de Impacto en Oceano")
        Esc("4. Evaluar Ventana de Angulo de Reingreso")
        Esc("5. Generar Reporte Final (Historial)")
        Esc("6. Salir")
        Esc("Seleccione una opcion: ")
        Leer(opcion)

        Segun opcion Hacer
            1: 
                Esc("Tiempo de desaceleracion (s): ")
                Leer(nave.tiempo_desaceleracion)
                Esc("Profundidad de hundimiento (m): ")
                Leer(nave.profundidad_hundimiento)
                Esc("Angulo de reingreso (grados): ")
                Leer(nave.angulo_reingreso)
                
                datos_cargados := VERDADERO
                Esc("Parametros cargados exitosamente.")
            
            2: 
                // Condicional para bloquear cálculos si no hay datos previos
                Si datos_cargados = VERDADERO entonces
                    CalcularFisicaTrabajo(nave)
                    // Guardamos la simulación en el arreglo después de calcular
                    GuardarHistorial(historial, cant_historial, nave)
                Sino
                    Esc("Error: Debe ingresar parametros primero (Opcion 1).")
                FinSi

            3: 
                Si datos_cargados = VERDADERO entonces
                    CalcularFuerzaImpacto(nave)
                Sino
                    Esc("Error: Debe ingresar parametros primero (Opcion 1).")
                FinSi

            4: 
                Si datos_cargados = VERDADERO entonces
                    EvaluarAngulo(nave)
                Sino
                    Esc("Error: Debe ingresar parametros primero (Opcion 1).")
                FinSi

            5: 
                MostrarReporte(historial, cant_historial)

            6: 
                Esc("Saliendo del simulador de vuelo...")
        FinSegun
    Hasta que opcion = 6
FinAccion