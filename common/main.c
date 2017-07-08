#include "stm32f7xx_nucleo_144.h"

#define USARTx                           USART3

extern volatile unsigned int ticks;
UART_HandleTypeDef UartHandle;
void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);

static void Error_Handler(void) {
	/* Turn LED3 on */
	BSP_LED_On(LED3);
	while (1) { }

}
void assert_failed(uint8_t* file, uint32_t line) {

	while (1) {

	}
}

int board_init(void) {
	CPU_CACHE_Enable();
	HAL_Init();
	SystemClock_Config();
	/* TODO: setup oscillator settings using HAL RCC */
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);

	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);

	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	UartHandle.Instance        = USARTx;
	
	UartHandle.Init.BaudRate   = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	printf("hello\n");
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
			if (curr % 2) {
				BSP_LED_On(LED_GREEN);
				printf("green led on\n");
			}else BSP_LED_Off(LED_GREEN);
		}
		prev = curr;
	}
}

void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 432;  
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	RCC_OscInitStruct.PLL.PLLR = 7;

	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		while(1) {};
	}
	/* Activate the OverDrive to reach the 216 Mhz Frequency */

	if(HAL_PWREx_EnableOverDrive() != HAL_OK) {
		while(1) {};
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
	   clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
	{
		while(1) {};
	}
}


static void CPU_CACHE_Enable(void){
	/* Enable I-Cache */
	SCB_EnableICache();
	/* Enable D-Cache */
	SCB_EnableDCache();

}
