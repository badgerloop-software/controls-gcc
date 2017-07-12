#include <stdio.h>
#include "main.h"

#define NUM_CLK_SRCS 7
typedef enum clk_src {
	HSI = 0, HSE = 1, PLL = 2, PLLSAI = 3, PLLI2S = 4, LSI = 5, LSE = 6
} clk_src_t;

clk_src_t rcc_get_SysClockSrc(void);
clk_src_t rcc_get_PLLClockSrc(void);
int rcc_getClockState(clk_src_t clk);

const char *clk_src_strings[] = {
	"HSI", "HSE", "PLL", "PLLSAI", "PLLI2S", "LSI", "LSE"
};

void print_post_info(void) {
	int i;

	printf("\r\n----------------------------------------------------------------------\r\n");
	printf("-        University of Wisconsin-Madison Embedded Engineering        -\r\n");
	printf("----------------------------------------------------------------------\r\n");
	printf("Board:\t\t%s\r\n", BOARD);
	printf("Processor:\t%s\r\n\n", PROCESSOR);

	printf("Oscillator Settings:\r\n");
	for (i = 0; i < NUM_CLK_SRCS; i++) {
		printf("%s:\t%s", clk_src_strings[i], rcc_getClockState((clk_src_t) i) ? "ON" : "OFF");
		if (i == HSE) printf("\t(%u kHz), bypass %s", HSE_VALUE / 1000, (RCC->CR & RCC_CR_HSEBYP) ? "on" : "off");
		if (i == HSI) printf("\t(%u kHz)", HSI_VALUE / 1000);
		if (i == LSE) printf("\t(%u Hz), bypass %s", LSE_VALUE, (RCC->BDCR & RCC_BDCR_LSEBYP) ? "on" : "off");
		if (i == PLL) printf("\t(source: %s)", clk_src_strings[rcc_get_PLLClockSrc()]);
		printf("\r\n");
	}

	printf("\nFrequencies:\r\n");
	printf("SYSCLK:\t%lu kHz (source: %s)\r\n", HAL_RCC_GetSysClockFreq() / 1000, clk_src_strings[rcc_get_SysClockSrc()]);
	printf("HCLK:\t%lu kHz\r\n", HAL_RCC_GetHCLKFreq() / 1000);
	printf("APB1:\t%lu kHz\r\n", HAL_RCC_GetPCLK1Freq() / 1000);
	printf("APB2:\t%lu kHz\r\n", HAL_RCC_GetPCLK2Freq() / 1000);

	printf("\nUse 'help' for a list of commands.\r\n");
	printf("----------------------------------------------------------------------\r\n\r\n");
}

void assert_failed(uint8_t* file, uint32_t line) {
	printf("assert failed in file %s on line %lu.\n", file, line);
	while (1) {;}
}

int rcc_getClockState(clk_src_t clk) {
	switch (clk) {
		case HSI: return RCC->CR & RCC_CR_HSIRDY; break;
		case HSE: return RCC->CR & RCC_CR_HSERDY; break;
		case PLL: return RCC->CR & RCC_CR_PLLRDY; break;
		case PLLSAI: return RCC->CR & RCC_CR_PLLSAIRDY; break;
		case PLLI2S: return RCC->CR & RCC_CR_PLLI2SRDY; break;
		case LSI: return RCC->CSR & RCC_CSR_LSIRDY; break;
		case LSE: return RCC->BDCR & RCC_BDCR_LSERDY; break;
	}
	return 0;
}

clk_src_t rcc_get_PLLClockSrc(void) {
	switch (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) {
		case RCC_PLLCFGR_PLLSRC_HSE: return HSE;
		case RCC_PLLCFGR_PLLSRC_HSI: return HSI;
	}
	return PLLI2S; /* indicate error */
}

clk_src_t rcc_get_SysClockSrc(void) {
	switch (RCC->CFGR & RCC_CFGR_SWS_Msk) {
		case RCC_CFGR_SWS_HSI: return HSI;
		case RCC_CFGR_SWS_HSE: return HSE;
		case RCC_CFGR_SWS_PLL: return PLL;
	}
	return PLLI2S; /* indicatg error */
}

