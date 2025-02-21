#include "CanFactory.h"
#include "stm32l4xx_hal.h"

/**
 * @brief Method that creates a CanMsg which sends Confirmation to dash when AIR+/- is connected
 * @param AIR_Type defines if AIR+ or AIR- was connected (1 = AIR-, 2 = AIR+)
 * @return CanMessage
 */

CanMessage CreateSendAIRConfirmationToDash(int AIR_Type) {
	CanMessage canMessage;
	canMessage.id = 0x710;
	canMessage.DLC = 1;
	canMessage.RTR = CAN_RTR_DATA;
	canMessage.IDE = CAN_ID_STD;
	canMessage.data.bytes[0] = AIR_Type;
	return canMessage;
}
