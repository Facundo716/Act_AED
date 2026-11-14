# Simulador Artemis: Escenario 4 🚀

## 👥 Equipo de Desarrollo y Comisión
* **Integrantes**: Alan Aguirre, Facundo Ferreyra, Gonzalo Ferreyra
* **Comisión**: Noche (1.4) 

Proyecto desarrollado en C para simular el reingreso atmosférico y acuatizaje de la cápsula espacial Orion (Misión Artemis). Este programa calcula parámetros físicos críticos, valida estrictamente las entradas del usuario y mantiene un historial de simulaciones en memoria.

## ⚙️ Características y Módulos
* **Ingreso seguro de parámetros**: Blindaje contra ingresos de texto, caracteres especiales y valores nulos (cero absoluto) para evitar caídas del sistema.
* **Cálculo de Trabajo y Desaceleración**: Computa el trabajo de rozamiento (Joules) y la desaceleración media (m/s²).
* **Cálculo de Fuerza de Impacto**: Determina la fuerza promedio ejercida por el océano y el múltiplo del peso de la nave.
* **Evaluación de Ángulo**: Verifica si el ángulo de reingreso se encuentra dentro de la ventana óptima de seguridad (5.5° - 7.0°).
* **Historial de Simulaciones**: Almacena temporalmente (mediante arreglos y punteros) hasta 10 intentos de simulación para generar un reporte comparativo final.

## Breve Detalle de Funcionamiento

El programa está estructurado utilizando el principio de diseño descendente (Top-Down) y modularización en lenguaje C.
El flujo principal es orquestado por un ciclo do-while interactivo en main.c. La lógica matemática y el motor físico están aislados en el módulo artemis.c (con su respectivo .h), mientras que el blindaje contra errores de tipeo del usuario (como ingresar letras en lugar de números o valores nulos que provoquen divisiones por cero) se gestiona desde el módulo independiente validaciones.c. Los datos históricos se manejan en memoria interna a través de un arreglo de registros (struct).

## Registro Detallado del Uso de Inteligencia Artificial

Durante el ciclo de desarrollo de este proyecto, se utilizó asistencia de Inteligencia Artificial (Gemini) con los siguientes propósitos:

Resolución de Conflictos en Git: Asistencia para identificar y limpiar marcadores de control de versiones.
Refactorización de Código: Apoyo para aislar funciones en módulos .c y .h independientes, mejorando la arquitectura del proyecto.
Preparación de Presentación: Generación de assets visuales (fondos para diapositivas).

## 🛠️ Compilación y Ejecución
El proyecto incluye un archivo `Makefile` para facilitar su compilación en entornos compatibles.

**Opción 1: Usando Make (Recomendado)**
```bash
make
.\simulador.exe

**Opción 2: Compilación manual con GCC (Windows/MinGW)
    gcc -Wall -Wextra -std=c99 -o simulador main.c artemis.c validaciones.c -lm
    .\simulador.exe

📅 Historial de Versiones (Bitácora de Desarrollo)
V1: Creación de la estructura base del proyecto, diseño del menú principal interactivo y habilitación de carga de datos sin protección.

V2: Implementación inicial del módulo validaciones.c para lectura segura de enteros, blindando la navegación del menú.

V3: Integración del motor físico (artemis.c). Nota de testing: Se dejó asentado un bug crítico (división por cero / NaN) al permitir tiempos de desaceleración en 0 segundos durante las pruebas de estrés.

V4 (Estable/Final): Aplicación de parche de seguridad lógico en leerFlotante para restringir límites inferiores y limpiar la basura del buffer del teclado. Implementación definitiva del sistema de arreglos para el reporte histórico.
