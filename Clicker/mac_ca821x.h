

#ifndef CA821X_MAC_H
#define CA821X_MAC_H

#include <stdint.h>

#include "ca821x_api.h"
#include "ca821x_irq.h"
#include "ca821x_spi.h"

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************//**
 * @brief Initializes CA-821x driver and module.
 *
 * @param 
 * @return Error code 
 */
uint8_t mac_init();


/***************************************************************************//**
 * @brief Reset CA-821x driver and module.
 *
 * @param 
 * @return Error code 
 */
uint8_t mac_reset();

/***************************************************************************//**
 * @brief Sends MSDU to destination address.
 *
 * @param lladdr_dst - Destination EUI-64 address.
 * @param msdu - MSDU to send.
 * @param msdu_length - MSDU length.
 *
 * @return Error code 
 */
uint8_t mac_send(
    uint8_t *lladdr_dst,
    uint8_t *msdu,
    uint16_t msdu_length
);


/***************************************************************************//**
 * @brief Module proccess for handling asynchronious events. 
 * 
 * Should be called in loop.
 *        
 * @param 
 * @return Error code 
 */
 uint8_t mac_process();


/***************************************************************************//**
 * @brief Get EUI-64 address.
 *
 * It uses sync command message to read PIBAttribute from CA-821x module.
 *
 * @param addr - Pointer to buffer for storing EUI-64 address.
 * @return Error code 
 */
uint8_t mac_get_addr(uint8_t *addr);


/***************************************************************************//**
 * @brief Set EUI-64 address.
 *
 * It uses sync command message to write PIBAttribute to CA-821x module.
 *
 * @param addr - Pointer to buffer where is stored EUI-64 address.
 * @return Error code 
 */
uint8_t mac_set_addr(uint8_t *addr);


#ifdef __cplusplus
}
#endif

#endif // CA821X_MAC_H
