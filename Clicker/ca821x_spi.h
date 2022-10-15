
#ifndef CA821X_SPI_H
#define CA821X_SPI_H

#include <stdint.h>

typedef unsigned long (*spi_transfer_t)(unsigned long buffer);



#define CA821X_SPI_OK (0x00)
#define CA821X_SPI_ERROR (0x01)
#define CA821X_SPI_NO_MSG (0x02)
#define CA821X_SPI_INVALID_PACKET (0x03)

typedef struct MAC_Message MAC_Message_t;
typedef union MacAddr MacAddr_t;

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_spi_init(spi_transfer_t spi_transfer);


/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
uint8_t ca821x_spi_receive(uint8_t *buf);



#ifdef __cplusplus
}
#endif

#endif // CA821X_SPI_H
