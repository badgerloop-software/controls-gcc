#include "main.h"

void SystemClock_Config();
void init_usb_uart(void);
int init_accel_i2c(void);

static void Error_Handler(void) {

	if (usb_uart.gState != HAL_UART_STATE_RESET)
		printf("Error: %p\r\n", __builtin_return_address(0));

	BSP_LED_On(LED_RED); /* Turn LED3 on */
	while (1) {;}
}

inline void nucleo144_gpio_init(void) {
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
}

int board_init(void) {

	/* Core Initializations */
	SCB_EnableICache();
	SCB_EnableDCache();
	SystemClock_Config();
	HAL_Init();
	nucleo144_gpio_init();
	init_usb_uart();

	/* Drivers Under Construction */
	init_accel_i2c();

	return 0;
}

/*****************************************************************************/
/*                   	 	  		  UART		                             */
/*****************************************************************************/
inline void init_usb_uart(void) {
	usb_uart.gState =          HAL_UART_STATE_RESET;
	usb_uart.Instance        = USART3;
	usb_uart.Init.BaudRate   = 115200;
	usb_uart.Init.WordLength = UART_WORDLENGTH_8B;
	usb_uart.Init.StopBits   = UART_STOPBITS_1;
	usb_uart.Init.Parity     = UART_PARITY_NONE;
	usb_uart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	usb_uart.Init.Mode       = UART_MODE_TX_RX;
	usb_uart.Init.OverSampling = UART_OVERSAMPLING_16;
	usb_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&usb_uart) != HAL_OK)
		Error_Handler();
}

/*****************************************************************************/
/*                        			CLOCK		                             */
/*****************************************************************************/
inline void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 160;  
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 10;
	RCC_OscInitStruct.PLL.PLLR = 5;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		Error_Handler();

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
	   clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  

	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
		Error_Handler();

	__HAL_RCC_HSI_DISABLE();
}

/*****************************************************************************/
/*                   	 	  		  I2C		                             */
/*****************************************************************************/
int init_accel_i2c(void) {

	accel_i2c.State =					HAL_I2C_STATE_RESET;
	accel_i2c.Instance =				I2Cx;
	accel_i2c.Init.Timing =				I2C_TIMING;
	accel_i2c.Init.OwnAddress1 =		I2C_ADDRESS;
	accel_i2c.Init.AddressingMode =		I2C_ADDRESSINGMODE_10BIT;
	accel_i2c.Init.DualAddressMode =	I2C_DUALADDRESS_DISABLE;
	accel_i2c.Init.OwnAddress2 =		0xFF;
	accel_i2c.Init.GeneralCallMode =	I2C_GENERALCALL_DISABLE;
	accel_i2c.Init.NoStretchMode =		I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&accel_i2c) != HAL_OK)
		Error_Handler();

	return 0;
}

/*****************************************************************************/
/*                        		Nucleo I/O			                         */
/*****************************************************************************/
GPIO_TypeDef*	GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t	GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
GPIO_TypeDef*	BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT}; 
const uint16_t	BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN}; 
const uint8_t	BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

void BSP_LED_On(Led_TypeDef Led) { HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET); }
void BSP_LED_Off(Led_TypeDef Led) { HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); }
uint32_t BSP_PB_GetState(Button_TypeDef Button) { return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]); }

void BSP_LED_Init(Led_TypeDef Led) {
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = GPIO_PIN[Led];
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); 
}

void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode) {
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  /* Configure Button pin as input */
  if(ButtonMode == BUTTON_MODE_GPIO) {
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  /* Configure Button pin as input with External interrupt */
  if(ButtonMode == BUTTON_MODE_EXTI) {
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

void BSP_LED_DeInit(Led_TypeDef Led) {
  GPIO_InitTypeDef  gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = GPIO_PIN[Led];
  HAL_GPIO_DeInit(GPIO_PORT[Led], gpio_init_structure.Pin);
}

void BSP_PB_DeInit(Button_TypeDef Button) {
    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}

