# 30319 Laboratorio 3: Generación y Control de Señales con DDS

## Descripción

Este proyecto implementa una práctica de laboratorio para la generación y control de señales analógicas mediante síntesis digital directa (DDS - Direct Digital Synthesis) en la placa de desarrollo **FM4-176L-S6E2CC-ETH**.

## Características Principales

- **Plataforma**: FM4-176L-S6E2CC-ETH (ARM Cortex-M4)
- **Codec de Audio**: WM8731
- **Frecuencia de Muestreo**: 48 kHz
- **Interfaz de Audio**: I2S
- **Control**: Pulsadores y LEDs RGB

## Estructura del Proyecto

```
lab3/
├── _doc/                    # Documentación
├── bsp/                     # Board Support Package
│   ├── include/
│   │   ├── FM4_leds_sw.h   # Control de LEDs y pulsadores
│   │   └── FM4_WM8731.h    # Driver del codec WM8731
│   └── src/
├── hal/                     # Hardware Abstraction Layer
│   ├── include/
│   │   ├── HAL_FM4_dtimer.h # Timer hardware
│   │   ├── HAL_FM4_gpio.h   # GPIO hardware
│   │   ├── HAL_FM4_i2c.h    # I2C hardware
│   │   ├── HAL_FM4_i2s.h    # I2S hardware
│   │   └── HAL_SysTick.h    # SysTick timer
│   └── src/
├── src/                     # Código fuente principal
│   ├── dds.c               # Implementación DDS
│   ├── dds.h               # Definiciones DDS
│   ├── ejercicios.c        # Implementación de ejercicios
│   ├── ejercicios.h        # Prototipos de ejercicios
│   ├── main.c              # Función principal
│   └── dds_sine_tbl257.dat # Tabla de seno para DDS
├── test/                   # Código de pruebas
├── build_keil/            # Proyecto Keil uVision
└── shared/                # Código deasrrollado en otras prácticas
    ├── include/
    │   └── pulsaciones.h   # Gestión de pulsaciones
    └── src/
        └── pulsaciones.c   # Implementación de gestión de pulsaciones
```

## Ejercicios Implementados

### Ejercicio 3.1: Generación de Señales en Cuadratura
- **Función**: `lab31()`
- **Descripción**: Genera dos señales en cuadratura de 1 kHz
- **Salida**: Canal izquierdo y derecho del codec estéreo

### Ejercicio 3.2: Síntesis FM - Efecto Sirena
- **Función**: `lab32()`
- **Descripción**: Genera el sonido de una alarma/sirena
- **Salida**: Canal izquierdo (canal derecho a 0)

### Ejercicio 3.3: Control por Pulsaciones
- **Función**: `lab33(uint8_t pulsacion)`
- **Descripción**: Control de la generación de señal mediante pulsaciones
- **Control**: Pulsador SW2 para activar/desactivar

## Sistema DDS (Direct Digital Synthesis)

El proyecto implementa un sistema DDS de 16 bits que permite:

- **Acumulador de Fase**: Control preciso de la frecuencia
- **Incremento de Fase**: Determinación de la frecuencia de salida
- **Tabla de Seno**: 257 puntos para síntesis de ondas sinusoidales
- **Resolución**: 16 bits para alta calidad de audio


### Pasos de Compilación
1. Abrir `build_keil/lab3.uvprojx` en Keil uVision
2. Seleccionar el target deseado:
   - `Test_DDS`
   - `Test_Pulsaciones`
   - `lab3`
3. Compilar el proyecto (F7)
4. Programar la placa (F8)

### Configuración de Audio
- **Entrada**: Line-in (ganancia 0 dB)
- **Salida**: Headphone jack (ganancia 0 dB)
- **Formato**: Estéreo, 48 kHz, 16 bits

## Uso del Sistema

1. **Conexión**: Conectar auriculares al jack de salida
2. **Alimentación**: Alimentar la placa via USB o fuente externa
3. **Control**:
   - Pulsación corta de SW2: Cambiar modo/color
   - Pulsación larga de SW2: Reset
4. **Indicadores**:
   - LED RGB: Estado actual del sistema
   - LED ETH: Sistema funcionando (breathing)

keywords: DDS, FM4, WM8731, I2S, Audio, Keil, GPIO, Pulsaciones, Laboratorio
