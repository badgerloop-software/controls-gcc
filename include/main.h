#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include "nuc144.h"
#include "hal_conf.h"

UART_HandleTypeDef usb_uart;
I2C_HandleTypeDef accel_i2c;

#define BOARD		"STM32 Nucleo144 F767ZI"
#define PROCESSOR	"STM32F767ZI"

void print_post_info(void);
extern volatile unsigned int ticks;

/*****************************************************************************/
/*                        		   I2C	   		                             */
/*****************************************************************************/
#define I2C_ADDRESS       0x30F
#define I2C_TIMING        0x00D00E28  /* (Rise time = 120ns, Fall time = 25ns) */

/* Definition for I2Cx clock resources */
#define I2Cx                            I2C1
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2Cx_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

/* Size of Transmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                      TXBUFFERSIZE

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#endif

