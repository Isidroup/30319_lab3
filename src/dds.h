/**
 * @file dds.h
 * @brief Definiciones y prototipos para la implementación de un DDS (Direct Digital Synthesis) de 16 bits.
 * @date :2026/10/06 21:00:23
 */

#include <stdint.h>

#ifndef __DDS_H__
#define __DDS_H__

/**
* Estructura para implementar un DDS
*/
typedef struct
{
    uint16_t phase_accumulator; /**< acumulador de fase */
    uint16_t phase_increment;   /**< incremento de fase */
} dds_16_bits_t;

/**
 * @brief    Da valor a la fase en un objeto de tipo DDS16Bits
 * @param [out]  self puntero a la estructura a inicializar
 * @param [in]   phase valor de la fase codificada en 16 bits [0->2pi)
 *
 * @return    void
 *
 * @note
 *-------------------------------------------------------------------*/
void dds_16_bits_set_phase(dds_16_bits_t *self, uint16_t phase);

/**
 * @brief    Da valor al incremento de fase en un objeto de tipo DDS16Bits
 * @param [out]  self puntero a la estructura a inicializar
 * @param [in]   phaseinc    valor del incremento de fase codificado en 16 bits
 *
 * @return    void
 *
 * @note
 *-------------------------------------------------------------------*/
void dds_16_bits_set_phase_increment(dds_16_bits_t *self, uint16_t phaseinc);

/**
 * @brief   Devuelve el siguiente valor de amplitud de la señal
 * @details Devuelve en 16 bits el valor de amplitud de un
 *             tono obtenido mediante DDS.
 * @param [inout]  self puntero a un módulo DDS
 * @return  amplitud codificada en 16 bits (int16_t)
 *
 * @note    es necesario dar valor previamente a la fase y al incremento de fase
 *-------------------------------------------------------------------*/
int16_t dds_16_bits_get_next_sample(dds_16_bits_t *self);

#endif
