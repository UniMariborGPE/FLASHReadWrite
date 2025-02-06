/**
  ******************************************************************************

  EEPROM.h Using the HAL I2C Functions
  Author:   ControllersTech
  Updated:  Feb 6, 2025
  Updated by: tevzselcan

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stdint.h"
#include "stm32l4xx_hal.h"

typedef union {
    uint32_t uInt;
    int32_t Int;
    float Float;
} parameterValue;

typedef struct {
    uint8_t id;
    uint8_t dataType; // Data type: (0: uInt, 1: Int, 2: Float)
    parameterValue value;
} parameter;


void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_PageErase (uint16_t page);

void EEPROM_Write_NUM (uint16_t page, uint16_t offset, float  fdata);
float EEPROM_Read_NUM (uint16_t page, uint16_t offset);

// New function prototypes for parameter arrays
void EEPROM_Write_Parameter_Array(uint16_t page, uint16_t offset, const parameter *params, uint16_t numParams);
void EEPROM_Read_Parameter_Array(uint16_t page, uint16_t offset, parameter *params, uint16_t numParams);

#endif /* INC_EEPROM_H_ */
