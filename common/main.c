#include "stm32f7xx_nucleo_144.h"

void assert_failed(uint8_t* file, uint32_t line) {

	while (1) {

	}
}

int main(void) {

	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	while (1) {
		if (BSP_PB_GetState(BUTTON_USER)) {
			BSP_LED_On(LED_BLUE);
			BSP_LED_On(LED_RED);
			BSP_LED_On(LED_GREEN);
		}
		else {
			BSP_LED_Off(LED_BLUE);
			BSP_LED_Off(LED_RED);
			BSP_LED_Off(LED_GREEN);
		}
	}
}

