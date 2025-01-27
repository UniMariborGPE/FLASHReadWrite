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

typedef union {
    uint32_t uInt;
    int32_t Int;
    float Float;
} parameterValue;

typedef struct {
    uint8_t id;
    parameterValue value;
} parameter;

HAL_StatusTypeDef Flash_ErasePage(uint32_t page_address);
HAL_StatusTypeDef Flash_WriteParams(uint32_t address, parameter *params, size_t count);
void Flash_ReadParams(uint32_t address, parameter *params, size_t count);

#endif /* INC_FLASH_MANAGER_H_ */
