/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define LSE_IN_Pin GPIO_PIN_14
#define LSE_IN_GPIO_Port GPIOC
#define LSE_Out_Pin GPIO_PIN_15
#define LSE_Out_GPIO_Port GPIOC
#define SDA_Pin GPIO_PIN_0
#define SDA_GPIO_Port GPIOF
#define SCL_Pin GPIO_PIN_1
#define SCL_GPIO_Port GPIOF
#define Analog_6_Pin GPIO_PIN_3
#define Analog_6_GPIO_Port GPIOF
#define Analog_7_Pin GPIO_PIN_4
#define Analog_7_GPIO_Port GPIOF
#define Analog_8_Pin GPIO_PIN_5
#define Analog_8_GPIO_Port GPIOF
#define Analog_9_Pin GPIO_PIN_10
#define Analog_9_GPIO_Port GPIOF
#define HSE_IN_Pin GPIO_PIN_0
#define HSE_IN_GPIO_Port GPIOH
#define HSE_OUT_Pin GPIO_PIN_1
#define HSE_OUT_GPIO_Port GPIOH
#define Analog_3_Pin GPIO_PIN_0
#define Analog_3_GPIO_Port GPIOC
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define Analog_4_Pin GPIO_PIN_2
#define Analog_4_GPIO_Port GPIOC
#define Analog_5_Pin GPIO_PIN_3
#define Analog_5_GPIO_Port GPIOC
#define PWM1_Pin GPIO_PIN_0
#define PWM1_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define Analog_1_Pin GPIO_PIN_3
#define Analog_1_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define Analog_2_Pin GPIO_PIN_1
#define Analog_2_GPIO_Port GPIOB
#define GPIO9_Pin GPIO_PIN_12
#define GPIO9_GPIO_Port GPIOF
#define GPIO10_Pin GPIO_PIN_0
#define GPIO10_GPIO_Port GPIOG
#define GPIO11_Pin GPIO_PIN_1
#define GPIO11_GPIO_Port GPIOG
#define Retro_1_Pin GPIO_PIN_9
#define Retro_1_GPIO_Port GPIOE
#define Retro_2_Pin GPIO_PIN_11
#define Retro_2_GPIO_Port GPIOE
#define Retro_3_Pin GPIO_PIN_13
#define Retro_3_GPIO_Port GPIOE
#define GPIO8_Pin GPIO_PIN_14
#define GPIO8_GPIO_Port GPIOE
#define PWM2_Pin GPIO_PIN_10
#define PWM2_GPIO_Port GPIOB
#define PWM3_Pin GPIO_PIN_11
#define PWM3_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define UART_USB_TX_Pin GPIO_PIN_8
#define UART_USB_TX_GPIO_Port GPIOD
#define UART_USB_RX_Pin GPIO_PIN_9
#define UART_USB_RX_GPIO_Port GPIOD
#define Limit_Switch_1_Pin GPIO_PIN_2
#define Limit_Switch_1_GPIO_Port GPIOG
#define Limit_Switch_2_Pin GPIO_PIN_3
#define Limit_Switch_2_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define SD_Card_D0_Pin GPIO_PIN_8
#define SD_Card_D0_GPIO_Port GPIOC
#define SD_Card_D1_Pin GPIO_PIN_9
#define SD_Card_D1_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SD_Card_D2_Pin GPIO_PIN_10
#define SD_Card_D2_GPIO_Port GPIOC
#define SD_Card_D3_Pin GPIO_PIN_11
#define SD_Card_D3_GPIO_Port GPIOC
#define SD_Card_CK_Pin GPIO_PIN_12
#define SD_Card_CK_GPIO_Port GPIOC
#define GPIO1_Pin GPIO_PIN_0
#define GPIO1_GPIO_Port GPIOD
#define GPIO2_Pin GPIO_PIN_1
#define GPIO2_GPIO_Port GPIOD
#define SD_Card_CMD_Pin GPIO_PIN_2
#define SD_Card_CMD_GPIO_Port GPIOD
#define GPIO3_Pin GPIO_PIN_3
#define GPIO3_GPIO_Port GPIOD
#define GPIO4_Pin GPIO_PIN_4
#define GPIO4_GPIO_Port GPIOD
#define GPIO5_Pin GPIO_PIN_5
#define GPIO5_GPIO_Port GPIOD
#define GPIO6_Pin GPIO_PIN_6
#define GPIO6_GPIO_Port GPIOD
#define GPIO7_Pin GPIO_PIN_7
#define GPIO7_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
