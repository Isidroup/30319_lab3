/**
 * @file    test_dds.c
 * @brief   Pruebas unitarias para el módulo DDS (Direct Digital Synthesis).
 * @date    :2026/10/08 14:02:51
 * @details Este archivo contiene diferentes casos de prueba para validar la generación
 *          de señales mediante DDS, comprobando la evolución de la amplitud en distintas
 *          configuraciones de fase e incremento de fase.
 *
 *          El incremento de fase se calcula como:
 *              phase_inc = 2^16 * fo / fs
 *          donde fs = 4800 Hz (frecuencia de muestreo) y fo es la frecuencia de salida deseada.
 */

#include <stdint.h>
#include "dds.h"

/**
 * @brief Inicializa el contador SysTick para generar una base de tiempos.
 */
void SysTick_Init__sample_period(void);

/**
 * @brief Espera a que SysTick complete un periodo.
 */
static inline void SysTick_Wait_sample_period(void);


/**
 * @var g_sample
 * @brief Contador de muestras para simular el avance temporal en las pruebas.
 */
__attribute__((section(".bss.noinit")))
uint16_t g_sample = 0;

/**
 * @var g_amp
 * @brief Valor de la muestra generada por el DDS.
 */
int16_t g_amp;

/**
 * @brief   Función principal de pruebas para DDS.
 * @details Ejecuta cinco casos de prueba para validar diferentes configuraciones del DDS.
 * @return  0 al finalizar la ejecución.
 */
int main ()
{
    static dds_16_bits_t dds_1; // ¿Es necesario static aquí?

    SysTick_Init__sample_period(); // Inicializa SysTick para generar una base de tiempos de 208

    // Test1: Señal 100 Hz durante 100 ms
    dds_16_bits_set_phase(&dds_1, 0);
    dds_16_bits_set_phase_increment(&dds_1, 1365);
    for (int i = 0; i < 48*10; i++)
    {
        SysTick_Wait_sample_period(); // Espera 208.33 µs
        g_sample = (g_sample < 47) ? g_sample + 1 : 0;
        g_amp = dds_16_bits_get_next_sample(&dds_1);
    }

    // Test2: Cambio a 200 Hz durante 50 ms
    dds_16_bits_set_phase_increment(&dds_1, 2731);
    for (int i = 0; i < 48*5; i++)
    {
        SysTick_Wait_sample_period();
        g_sample = (g_sample < 47) ? g_sample + 1 : 0;
        g_amp = dds_16_bits_get_next_sample(&dds_1);
    }

    // Test3: Cambios de fase con fo = 100 Hz (0°-180°-0°-180°-0°)
    dds_16_bits_set_phase_increment(&dds_1, 1365);
    uint16_t fases[] = {0, 32768, 0, 32768, 0};
    for (int j = 0; j < 5; j++)
    {
        dds_16_bits_set_phase(&dds_1, fases[j]);
        for (int i = 0; i < 48; i++)
        {
            SysTick_Wait_sample_period();
            g_sample = (g_sample < 47) ? g_sample + 1 : 0;
            g_amp = dds_16_bits_get_next_sample(&dds_1);
        }
    }

    // Test4: Oscilador parado (fo = 0 Hz) durante 50 ms
    dds_16_bits_set_phase(&dds_1, 0);
    dds_16_bits_set_phase_increment(&dds_1, 0);
    for (int i = 0; i < 48*5; i++)
    {
        SysTick_Wait_sample_period();
        g_sample = (g_sample < 47) ? g_sample + 1 : 0;
        g_amp = dds_16_bits_get_next_sample(&dds_1);
    }

    // Test5: Chirp lineal de 7.3 Hz a 0.586 kHz en 200 ms
    for (int i = 0; i < 48*20; i++)
    {
        SysTick_Wait_sample_period();
        g_sample = (g_sample < 47) ? g_sample + 1 : 0;
        uint16_t phase_inc = 100 + ((8000 - 100) * i) / (48*20);
        dds_16_bits_set_phase_increment(&dds_1, phase_inc);
        g_amp = dds_16_bits_get_next_sample(&dds_1);
    }

    // Test6: Propuesto por los estudiantes:


    // Test7: Propuesto por los estudiantes:


    // Punto de parada para depuración. Finalización del programa.
    __asm volatile ("BKPT #0");
    return 0;
}



/**
 * @section systick_base_tiempo Base de tiempos con SysTick
 * Configuración y espera del contador SysTick.
 */

#include "ARMCM4.h"
#include "core_cm4.h"   // o core_cm0.h, core_cm3.h, etc.

/**
 * @brief Configura e inicia el contador SysTick.
 * @details Carga el valor 2499 y habilita el contador con el reloj del procesador.
 *          No habilita la generación de interrupciones.
 */
void SysTick_Init__sample_period(void)
{
    SysTick->LOAD = 2500 - 1;    // 208.33 µs @ 12 MHz
    SysTick->VAL  = 0;           // Reinicia el contador

    SysTick->CTRL =
          SysTick_CTRL_CLKSOURCE_Msk  // Reloj del procesador
        | SysTick_CTRL_ENABLE_Msk;    // Habilita SysTick

    // TICKINT no se activa -> no hay interrupciones
}

/**
 * @brief Espera hasta que SysTick termine un periodo.
 * @details La función bloquea la ejecución hasta que el contador llega a cero.
 */
static inline void SysTick_Wait_sample_period(void)
{
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
    {
        // Espera hasta que el contador llegue a cero
    }
}
