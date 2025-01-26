/*
 * flash_manager.h
 *
 *  Created on: Jan 25, 2025
 *      Author: tevzselcan
 */

#ifndef INC_FLASH_MANAGER_H_
#define INC_FLASH_MANAGER_H_

#include "stm32l4xx_hal.h"
#include <stdint.h>
#include <string.h>

#define FLASH_START_ADDR  0x08000000  // Flash start address
#define FLASH_PARAMS_ADDR 0x0807F800  // Start address for writing params

// Params structure
typedef struct {
    float tire_pressure_front_left;
    float tire_pressure_front_right;
    float tire_pressure_rear_left;
    float tire_pressure_rear_right;
    float suspension_stiffness_front;
    float suspension_stiffness_rear;
    float brake_bias;
    float aero_coefficient;
} FSTestParams;

HAL_StatusTypeDef Flash_ErasePage(uint32_t page_address);
HAL_StatusTypeDef Flash_WriteParams(uint32_t address, FSTestParams *params);
void Flash_ReadParams(uint32_t address, FSTestParams *params);

#endif /* INC_FLASH_MANAGER_H_ */
