#include "main.h"
#include "stm32f7xx_hal.h"

/* Initializes the Global MSP */
void HAL_MspInit(void) {
 
}

/* DeInitializes the Global MSP */
void HAL_MspDeInit(void) {

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
	GPIO_InitTypeDef  GPIO_InitStruct;

	__HAL_RCC_GPIOD_CLK_ENABLE(); /* D8 and D9 used */

	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = GPIO_PIN_8;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* use default APB1 clock source */
	__HAL_RCC_USART3_CLK_ENABLE();
}

/**
 * @brief UART MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @param huart: UART handle pointer
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
	/*##-1- Reset peripherals ##################################################*/
	__HAL_RCC_USART3_FORCE_RESET();
	__HAL_RCC_USART3_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9);
	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8);
}

