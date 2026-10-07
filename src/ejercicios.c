/**
 * @file ejercicios.c
 * @brief Implementación de las funciones para las prácticas de laboratorio 3.
 * @date :2026/10/07 09:27:16
 */

#include "ejercicios.h"

#include "FM4_WM8731.h"
#include <stdint.h>

/**
 * @brief Genera dos señales en cuadratura de 1 kHz.
 */
void lab31(void)
{
    // Canales de salida del codec
    int16_t sample_left;
    int16_t sample_right;

    // Cálculo de los valores de amplitud de las dos señales
    //   >>> Incluir aquí el código <<<

    // Pasa datos al codec
    FM4_WM8731_wr(sample_left, sample_right);
}

/**
 * @brief Genera el sonido de una alarma por el canal izquierdo.
 *        El canal derecho se mantiene a 0.
 *        El pulsador controla si se escucha o no la sirena.
 */
void lab32(void)
{
    // Canales de salida del codec
    int16_t sample_left;
    int16_t sample_right;

    // Cálculo de los valores de amplitud de las dos señales
    //   >>> Incluir aquí el código <<<

    // Pasa datos al codec
    FM4_WM8731_wr(sample_left, sample_right);
}

/**
 * @brief Controla la funcionalidad de la práctica 3.3 según la pulsación.
 * @param pulsacion Valor que indica el estado del pulsador.
 */
void lab33(uint8_t pulsacion)
{

}
