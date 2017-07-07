#include "stm32f7xx_nucleo_144.h"

extern volatile unsigned int ticks;

void assert_failed(uint8_t* file, uint32_t line) {

	while (1) {

	}
}

int board_init(void) {

	/* TODO: setup oscillator settings using HAL RCC */
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	return 0;
}

int main(void) {
	unsigned int curr = 0, prev = 0;

	board_init();

	while (1) {
		if (BSP_PB_GetState(BUTTON_USER)) {
			BSP_LED_On(LED_BLUE);
			BSP_LED_On(LED_RED);
		}
		else {
			BSP_LED_Off(LED_BLUE);
			BSP_LED_Off(LED_RED);
		}

		/* Blink Red LED */
		curr = ticks / 500;
		if (curr != prev) {
			(curr % 2) ? 
				BSP_LED_On(LED_GREEN) : BSP_LED_Off(LED_GREEN);
		}
		prev = curr;
	}
}

