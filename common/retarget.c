#include "main.h"

int _write(int fd, const void *buf, size_t count) {
	HAL_UART_Transmit(&UartHandle, (uint8_t *) buf, count, 5000);
	return count;
}

int _read(int fd, const void *buf, size_t count) {
	HAL_UART_Receive(&UartHandle, (uint8_t *) buf, count, 5000);
	return count;
}

