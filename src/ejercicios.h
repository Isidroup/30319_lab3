/**
 * @file ejercicios.h
 * @brief Prototipos de funciones para las prácticas de laboratorio 3.
 *
 * Contiene las declaraciones de las funciones lab31, lab32 y lab33.
 */

#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <stdint.h>

/**
 * @brief Genera dos señales en cuadratura de 1 kHz.
 *
 * Esta función genera dos señales en cuadratura de 1 kHz y las envía a cada una
 *  de las salidas del códec estéreo.
 */
void lab31(void);

/**
 * @brief Genera el sonido de una alarma por el canal izquierdo.
 *
 * @note Esta función genera el sonido de una alarma por el canal izquierdo del
 *       códec estéreo. El canal derecho se mantiene a 0.
 */
 void lab32(void);

 /**
 * @brief Controla la funcionalidad de la práctica 3.3 según la pulsación.
 *        El pulsador se utiliza para controlar si se escucha o no la sirena.
 *
 * @param pulsacion Valor que indica el estado del pulsador.
 */
void lab33(uint8_t pulsacion);

#endif // EJERCICIOS_H
