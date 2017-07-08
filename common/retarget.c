#include <stdio.h>
extern UartHandle;
int _write(int fd, const void *buf, size_t count) {
	HAL_UART_Transmit(UartHandle, buf, count, 1);
	return count;
}

int _read(int fd, const void *buf, size_t count) {
	HAL_UART_Receive( UartHandle, buf, count, 1);
	return count;
}

