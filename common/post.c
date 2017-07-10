#include <stdio.h>
#include "main.h"

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
		if (i == HSE) printf("\t(%u kHz), bypass %s", HSE_VALUE / 1000, rcc_getHSEBYP() ? "on" : "off");
		if (i == HSI) printf("\t(%u kHz)", HSI_VALUE / 1000);
		if (i == LSE) printf("\t(%u Hz), bypass %s", LSE_VALUE, rcc_getLSEBYP() ? "on" : "off");
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

