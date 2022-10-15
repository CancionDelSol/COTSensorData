#ifndef CA821X_RF_IRQ_H
#define CA821X_RF_IRQ_H

#define TIMEOUT_MS(x) (uint16_t)(x)

#include <stdbool.h>
#include <stdint.h>

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_irq_init();

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
bool ca821x_irq_is_pending();

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_irq_signal();

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
uint8_t ca821x_irq_wait(uint16_t timeout_ms);

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_irq_enable();

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_irq_disable();

#endif // CA821X_RF_IRQ_H
