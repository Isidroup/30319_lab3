/**
 * @file    main.c
 * @brief   Práctica de laboratorio 3: Generación y control de señales con DDS.
 * @details Inicializa periféricos y ejecuta tareas periódicas para la gestión de
 *          pulsadores, LEDs y generación de señales analógicas mediante síntesis
 *          digital directa (DDS) en la placa FM4-176L-S6E2CC-ETH.
 *
 * @date    :2026/10/08 11:22:40
 *
 * @note    Organización de tareas: https://tinyurl.com/3vbre3dn
 */


// Cabeceras de los módulos propios
#include "ejercicios.h"
#include "pulsaciones.h"
// Cabeceras de los módulos hal y bsp
#include "FM4_leds_sw.h"
#include "FM4_WM8731.h"
#include "HAL_FM4_i2s.h"
#include "HAL_SysTick.h"
// Cabeceras estándar
#include <stdint.h>




/**
 *  @brief Función main(). Incluye la configuración e inicialización de
 *  periféricos y el "scheduling" de tareas https://tinyurl.com/3vbre3dn
 */
int32_t main(void) {

  // Configuración de LEDS y pulsador SW2
  LedsSwInit();

  //  Configuración e inicio Systick
  SysTick_Init(SystemCoreClock / 1000); //  base de tiempos -> 1ms

  // Inicializaci�n del I2C, Codec e I2S.
  FM4_WM8731_init(FS_48000_HZ,               // Sampling rate (sps)
                  WM8731_LINE_IN,            // Audio input port
                  WM8731_HP_OUT_GAIN_0_DB,   // Output headphone jack Gain (dB)
                  WM8731_LINE_IN_GAIN_0_DB); // Line-in input gain (dB)

                  // Puesta en marcha de I2S
  I2S_start();


  /**
   * Ejecutivo cíclico, utilizamos Round-Robin para la organización de tareas
   * @cite  David E. Simon, "An Embedded Software Primer", Addison-Wesley 2005
   */

  uint8_t pulsacion = 0;
  uint8_t contador = 0;
  while (1) {

    // 🗲 Tareas que se ejecutan cada ~1ms
    if (SysTick_ChkOvf()) {

      // Tarea 1: evalúa pulsación
      uint8_t entrada = Sw2Read(); // Lee SW2
      pulsacion = pulsaciones(entrada, 0);

      // Tarea 2: modifica contador
      if (pulsacion == 1)
          contador = (contador + 1) & 7;
      if (pulsacion == 2)
          contador = 0;

      // Tarea 3: Encendido del led RGB
      static const rgb_color_t color[8] = {OFF,    RED,     GREEN, BLUE,
                                           YELLOW, MAGENTA, CYAN,  WHITE};
      LedRGB(color[contador]);
    }

    // 🗲 Tarea 4: se ejecuta cuando hay hueco en el buffer de salida de I2S0
    if (I2S_isTxBufferFree())
    {
        #ifdef _LAB3_DEBUG_
            // Marca el inicio del procesamiento de una muestra.
            GPIO_ChannelWrite(P7D, GPIO_HIGH);
        #endif

        lab31();  // Sustituir por lab32(), lab33() ... según el ejercicio.

        #ifdef _LAB3_DEBUG_
            // Marca el final del procesamiento. La anchura del pulso indica
            // cuánto tarda la función en generar y enviar la muestra.
            GPIO_ChannelWrite(P7D, GPIO_LOW);

            // Detiene la ejecución si I2S indica que no se suministró una
            // muestra a tiempo para mantener la transmisión.
            if (I2S_get_tx_underrun())
            {
                __asm volatile ("BKPT #0");
            }
        #endif
    }
  }
}
