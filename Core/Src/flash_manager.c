/*
 * flash_manager.c
 *
 *  Created on: Jan 25, 2025
 *      Author: tevzselcan
 */

#include "flash_manager.h"

//Delete one page starting at page_address
HAL_StatusTypeDef Flash_ErasePage(uint32_t page_address) {
    FLASH_EraseInitTypeDef eraseInitStruct;
    uint32_t page_error;

    HAL_FLASH_Unlock();

    eraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInitStruct.Page = (page_address - FLASH_BASE) / FLASH_PAGE_SIZE; //(0x0807F800 - 0x08000000) / 2048 = 255
    eraseInitStruct.NbPages = 1; //Number of pages to erase

    HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&eraseInitStruct, &page_error);

    HAL_FLASH_Lock();
    return status;
}

HAL_StatusTypeDef Flash_WriteParams(uint32_t address, FSTestParams *params) {
    if (!params) return HAL_ERROR;

    HAL_StatusTypeDef status;

    HAL_FLASH_Unlock();

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    // Cast the structure to a uint64_t pointer for 8-byte writes
    uint64_t *data64 = (uint64_t *)params;
    size_t full_chunks = sizeof(FSTestParams) / 8;  // Number of full 8-byte chunks
    size_t remaining_bytes = sizeof(FSTestParams) % 8; // Bytes left after full chunks

    // Write full 8-byte chunks
    for (size_t i = 0; i < full_chunks; i++) {
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + i * 8, data64[i]);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            return status;
        }
    }

    // Handle remaining bytes
    if (remaining_bytes > 0) {
        uint8_t buffer[8] = {0};
        uint8_t *data8 = (uint8_t *)params;

        memcpy(buffer, &data8[full_chunks * 8], remaining_bytes);

        // Cast the buffer to uint64_t for 64-bit write
        uint64_t padded_data = *(uint64_t *)buffer;

        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + full_chunks * 8, padded_data);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            return status;
        }
    }

    HAL_FLASH_Lock();
    return HAL_OK;
}


// Read parameters from Flash
void Flash_ReadParams(uint32_t address, FSTestParams *params) {
    if (!params) return;
    memcpy(params, (void *)address, sizeof(FSTestParams));
}

