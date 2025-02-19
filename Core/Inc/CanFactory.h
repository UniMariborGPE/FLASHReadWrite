#pragma once

#include "stdint.h"

typedef union
{
	uint64_t value;
	uint8_t bytes[8];
	int16_t sint[4];
	uint16_t shorts[4];
	int32_t ints[2];
	uint32_t uints[2];
	float floats[2];
	double dub;
}
CanPayload;

typedef struct
{
	uint32_t id;
	uint8_t DLC;
    uint32_t RTR;
    uint32_t IDE;
	CanPayload data;
}
CanMessage;

CanMessage CreateSendAIRConfirmationToDash(int AIR_Type);
