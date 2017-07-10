#include "main.h"

static void CPU_CACHE_Enable();
static void SystemClock_Config();
void init_usb_uart(void);
int initI2C(void);

static void Error_Handler(void) {

	/* Turn LED3 on */
	printf("Error: %p\r\n", __builtin_return_address(0));
	BSP_LED_On(LED_RED);
	while (1) {;}
}

int board_init(void) {

	/* Core Initializations */
	CPU_CACHE_Enable();
	SystemClock_Config();
	HAL_Init();
	init_usb_uart();

	/* Board I/O */
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	return 0;
}

/*****************************************************************************/
/*                        				LED		                             */
/*****************************************************************************/
GPIO_TypeDef*	GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t	GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};

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

void BSP_LED_DeInit(Led_TypeDef Led) {
  GPIO_InitTypeDef  gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = GPIO_PIN[Led];
  HAL_GPIO_DeInit(GPIO_PORT[Led], gpio_init_structure.Pin);
}

void BSP_LED_On(Led_TypeDef Led) { HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET); }
void BSP_LED_Off(Led_TypeDef Led) { HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); }

/*****************************************************************************/
/*                        		PUSH BUTTON			                         */
/*****************************************************************************/
GPIO_TypeDef*	BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT}; 
const uint16_t	BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN}; 
const uint8_t	BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

void BSP_PB_DeInit(Button_TypeDef Button)
{
    GPIO_InitTypeDef gpio_init_structure;

    gpio_init_structure.Pin = BUTTON_PIN[Button];
    HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}

uint32_t BSP_PB_GetState(Button_TypeDef Button) {
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/*****************************************************************************/
/*                   	 	  		  UART		                             */
/*****************************************************************************/
void init_usb_uart(void) {
	usb_uart.Instance        = USART3;
	usb_uart.Init.BaudRate   = 115200;
	usb_uart.Init.WordLength = UART_WORDLENGTH_8B;
	usb_uart.Init.StopBits   = UART_STOPBITS_1;
	usb_uart.Init.Parity     = UART_PARITY_NONE;
	usb_uart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	usb_uart.Init.Mode       = UART_MODE_TX_RX;
	usb_uart.Init.OverSampling = UART_OVERSAMPLING_16;
	//usb_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&usb_uart) != HAL_OK)
		Error_Handler();
}

/*****************************************************************************/
/*                        			CLOCK		                             */
/*****************************************************************************/
void SystemClock_Config(void) {
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
/*                       			CACHE		                             */
/*****************************************************************************/
static void CPU_CACHE_Enable(void){
	SCB_EnableICache(); /* Enable I-Cache */
	SCB_EnableDCache(); /* Enable D-Cache */
}

/*****************************************************************************/
/*                   	 	  		  I2C		                             */
/*****************************************************************************/
int initI2C(void) {

	I2cHandle.Instance             = I2Cx;
	I2cHandle.Init.Timing          = I2C_TIMING;
	I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
	I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_10BIT;
	I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.OwnAddress2     = 0xFF;
	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_MspInit(&I2cHandle);
	if(HAL_I2C_Init(&I2cHandle) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	return 0;
}

