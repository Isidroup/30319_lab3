/**
 * @file dds.c
 * @brief Implementación de funciones para un DDS (Direct Digital Synthesis) de 16 bits.
 * @date :2025/10/03 16:27:12
 */

#include <stdint.h>
#include "dds.h"

/**
 * @brief Tabla con 257 valores de amplitud correspondientes
 *          al primer cuadrante de una senoide
 */
static const int16_t SinLookupTbl[257] = {
#include "dds_sine_tbl257.dat"
};

/**
 * @brief   Conversor fase → amplitud
 * @details Devuelve en 16 bits el valor de amplitud que
 *             corresponde a fase.
 * @param [in]  fase codificada en 10 bits [0->2pi)
 * @return  Amplitud codificada en 16 bits (int16_t)
 * @note    Utiliza una tabla con valores de amplitud (257) del
 *             1er cuadrante de una senoide
 *-------------------------------------------------------------------*/
inline static int16_t SineTbl(uint16_t fase)
{
    int16_t sine_amp;


    return (sine_amp);
}

/**
 * @brief    Da valor a la fase en un objeto de tipo DDS16Bits
 */
void DDS16Bits_setPhase(dds16bits_t *p_dds, uint16_t phase)
{


}

/**
 * @brief  Da valor al incremento de fase en un objeto de tipo DDS16Bits
 */
void DDS16Bits_setPhaseInc(dds16bits_t *p_dds, uint16_t phaseinc)
{


}

/**
 * @brief   Devuelve el siguiente valor de amplitud de la señal
 */
int16_t DDS16Bits_getNextSample(dds16bits_t *p_dds)
{
    int16_t amp ;



    return amp;
}
