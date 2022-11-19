#ifndef CA821X_BSP_H
#define CA821X_BSP_H

#include <stdbool.h>

/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_bsp_reset_low();


/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_bsp_reset_high();


/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_bsp_cs_low();


/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
void ca821x_bsp_cs_high();


/***************************************************************************//**
 * @brief 
 *
 * @param 
 * @return 
 */
bool ca821x_bsp_irq_sense();

#endif // CA821X_BSP_H