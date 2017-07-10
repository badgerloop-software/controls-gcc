#include "main.h"

int _write(int fd, const void *buf, size_t count) {
	HAL_UART_Transmit(&usb_uart, (uint8_t *) buf, count, 500);
	return count;
}

int _read(int fd, const void *buf, size_t count) {
	HAL_UART_Receive(&usb_uart, (uint8_t *) buf, count, 500);
	return count;
}

