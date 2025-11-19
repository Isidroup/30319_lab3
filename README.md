# Lab 3 - Generación y Control de Señales con DDS

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

### Estructura DDS

```c
typedef struct {
    uint16_t phaseAccumulator; // Acumulador de fase
    uint16_t phaseIncrement;   // Incremento de fase
} dds16bits_t;
```

## Hardware Utilizado

### Placa de Desarrollo FM4-176L-S6E2CC-ETH
- **MCU**: ARM Cortex-M4 con FPU
- **Frecuencia**: 12 MHz (configurable)
- **Memoria**: SRAM y Flash integradas

### Periféricos
- **I2S0**: Interfaz de audio estéreo
- **I2C**: Comunicación con codec WM8731
- **GPIO**: Control de LEDs y lectura de pulsadores
- **SysTick**: Base de tiempos de 1ms

### LEDs y Controles
- **LED RGB**: Indicador visual con 8 colores
- **LED ETH**: Efecto "breathing"
- **Pulsador SW2**: Control de funcionalidades

## Organización de Tareas

El proyecto utiliza un **ejecutivo cíclico Round-Robin** con las siguientes tareas:

### Tareas de 1ms (SysTick)
1. **Evaluación de pulsaciones**: Lectura y debounce de SW2
2. **Control de contador**: Modificación según pulsaciones
3. **Control LED RGB**: Cambio de color según contador

### Tareas de Audio (I2S)
4. **Generación DDS**: Síntesis de señales cuando el buffer está libre

### Tareas Continuas
5. **Efecto Breathing**: LED ETH con efecto visual

## Compilación y Uso

### Requisitos
- **Keil uVision 5** o superior
- **ARM Compiler 6.22**
- **CMSIS Pack**: ARM.Cortex_DFP.1.1.0

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

## Funciones Principales

### Control de DDS
```c
void DDS16Bits_setPhase(dds16bits_t *p_dds, uint16_t phase);
void DDS16Bits_setPhaseInc(dds16bits_t *p_dds, uint16_t phaseinc);
int16_t DDS16Bits_getNextSample(dds16bits_t *p_dds);
```

### Control de Audio
```c
void FM4_WM8731_init(uint32_t fs, uint8_t input, int8_t hp_gain, int8_t line_gain);
void I2S_start(void);
uint8_t I2S_isTxBufferFree(void);
```

### Control de Hardware
```c
void LedsSwInit(void);
uint8_t Sw2Read(void);
void LedRGB(rgb_color_t color);
```

## Notas Técnicas

- **Base de Tiempos**: SysTick configurado a 1ms
- **Gestión de Buffers**: I2S con buffers de doble tamaño para audio continuo
- **Debounce**: Implementado en software para pulsadores
- **Colores RGB**: 8 estados predefinidos (OFF, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE)

## Autor

Proyecto desarrollado para la asignatura **656_30319_SEMP** - Sistemas Empotrados y de Tiempo Real.

**Fecha**: Octubre 2025

## Referencias

- [Organización de Tareas](https://tinyurl.com/3vbre3dn)
- David E. Simon, "An Embedded Software Primer", Addison-Wesley 2005
- Documentación del microcontrolador FM4 S6E2CC
- Datasheet del codec WM8731
