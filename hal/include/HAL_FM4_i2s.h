/**
 *  @todo reescribir comentarios en doxygen
*/
#ifndef __HAL_FM4_I2S__
#define __HAL_FM4_I2S__

#include <stdint.h>

void I2S_init(char fs);
uint32_t I2S_rx(void);
void I2S_tx(uint32_t c);
void I2S_start(void);

uint8_t I2S_isTxBufferFree(void);


/**
 * @brief Obtiene el estado de underrun de transmisión del registro STATUS de I2S.
 *
 * @return uint8_t Devuelve:
 *         - Bit 0: TXUDR0 (Underrun durante la trama)
 *         - Bit 1: TXUDR1 (Underrun al inicio de la trama)
 */
uint8_t I2S_get_tx_underrun(void);


#endif
