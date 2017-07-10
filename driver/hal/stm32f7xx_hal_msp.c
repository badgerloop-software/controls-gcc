/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
 * @brief UART MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	USARTx_TX_GPIO_CLK_ENABLE();
	USARTx_RX_GPIO_CLK_ENABLE();

	/* Select SysClk as source of USART1 clocks */
	RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
	HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

	/* Enable USARTx clock */
	USARTx_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = USARTx_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = USARTx_TX_AF;

	HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = USARTx_RX_PIN;
	GPIO_InitStruct.Alternate = USARTx_RX_AF;

	HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief UART MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	/*##-1- Reset peripherals ##################################################*/
	USARTx_FORCE_RESET();
	USARTx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	/* Configure UART Tx as alternate function  */
	HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
	/* Configure UART Rx as alternate function  */
	HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

}


/**
 * @brief I2C MSP Initialization 
 *        This function configures the hardware resources used in this example: 
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration  
 *           - DMA configuration for transmission request by peripheral 
 *           - NVIC configuration for DMA interrupt request enable
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	I2Cx_SCL_GPIO_CLK_ENABLE();
	I2Cx_SDA_GPIO_CLK_ENABLE();
	/* Enable I2Cx clock */
	I2Cx_CLK_ENABLE(); 

	/*##-2- Configure peripheral GPIO ##########################################*/  
	/* I2C TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

	/* I2C RX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = I2Cx_SDA_PIN;
	GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);

	/*##-3- Configure the NVIC for I2C ########################################*/   
	/* NVIC for I2Cx */
	HAL_NVIC_SetPriority(I2Cx_ER_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(I2Cx_ER_IRQn);
	HAL_NVIC_SetPriority(I2Cx_EV_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(I2Cx_EV_IRQn);
}

/**
 * @brief I2C MSP De-Initialization 
 *        This function frees the hardware resources used in this example:
 *          - Revert GPIO, DMA and NVIC configuration to their default state
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) {

	/*##-1- Reset peripherals ##################################################*/
	I2Cx_FORCE_RESET();
	I2Cx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	/* Configure I2C Tx as alternate function  */
	HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
	/* Configure I2C Rx as alternate function  */
	HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);

	/*##-3- Disable the NVIC for I2C ##########################################*/
	HAL_NVIC_DisableIRQ(I2Cx_ER_IRQn);
	HAL_NVIC_DisableIRQ(I2Cx_EV_IRQn);
}
