/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SBypassA_P3_MCU_Pin|SBypassA_P4_MCU_Pin|SBypassA_P5_MCU_Pin|SBypassA_P6_MCU_Pin
                          |SBypassA_P7_MCU_Pin|SBypassA_P8_MCU_Pin|SBypassA_P1_MCU_Pin|SBypassA_P2_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SSwA_N3_MCU_Pin|SSwA_N4_MCU_Pin|SSwA_N5_MCU_Pin|SSwA_P1_MCU_Pin
                          |SSwA_P2_MCU_Pin|SSwA_P3_MCU_Pin|SSwA_P4_MCU_Pin|SSwA_P5_MCU_Pin
                          |SSwA_P6_MCU_Pin|SSwA_P7_MCU_Pin|SSwA_P8_MCU_Pin|SSwA_N1_MCU_Pin
                          |SSwA_N2_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, I2C2_SDA_INTPUT_Pin|I2C2_SCL_INTPUT_Pin|ADC1_RESET_Pin|ADC2_RESET_Pin
                          |ADC3_RESET_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI1_NSS_ADC3_Pin|SPI3_NSS_FRAM_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SNOE1_Pin|SNOE2_Pin|SNOE3_Pin|SPI2_NSS_ADC2_Pin
                          |I2C3_SDA_LED_Pin|I2C3_SCL_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SByoffA_P1_MCU_Pin|SByoffA_P2_MCU_Pin|SByoffA_P3_MCU_Pin|SByoffA_P4_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, SByoffA_P5_MCU_Pin|SByoffA_P6_MCU_Pin|SByoffA_P7_MCU_Pin|SByoffA_P8_MCU_Pin
                          |DA1_MAX_MCU_Pin|DA2_MAX_MCU_Pin|DA3_MAX_MCU_Pin|DA4_MAX_MCU_Pin
                          |DA5_MAX_MCU_Pin|DA6_MAX_MCU_Pin|DA7_MAX_MCU_Pin|DA8_MAX_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_LED2_Pin|GPIO_LED1_Pin|SPI4_NSS_ADC1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, CTR_ON6_MCU_Pin|CTR_ON7_MCU_Pin|CTR_ON8_MCU_Pin|CLRDOG_Pin
                          |SSwA_N6_MCU_Pin|SSwA_N7_MCU_Pin|SSwA_N8_MCU_Pin|CTR_ON1_MCU_Pin
                          |CTR_ON2_MCU_Pin|CTR_ON3_MCU_Pin|CTR_ON4_MCU_Pin|CTR_ON5_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, I2C1_SDA_EEPROM_Pin|I2C1_SCL_EEPROM_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin PEPin
                           PEPin PEPin */
  GPIO_InitStruct.Pin = SBypassA_P3_MCU_Pin|SBypassA_P4_MCU_Pin|SBypassA_P5_MCU_Pin|SBypassA_P6_MCU_Pin
                          |SBypassA_P7_MCU_Pin|SBypassA_P8_MCU_Pin|GPIO_LED2_Pin|GPIO_LED1_Pin
                          |SBypassA_P1_MCU_Pin|SBypassA_P2_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin PCPin PCPin PCPin
                           PCPin PCPin PCPin PCPin
                           PCPin */
  GPIO_InitStruct.Pin = SSwA_N3_MCU_Pin|SSwA_N4_MCU_Pin|SSwA_N5_MCU_Pin|SSwA_P1_MCU_Pin
                          |SSwA_P2_MCU_Pin|SSwA_P3_MCU_Pin|SSwA_P4_MCU_Pin|SSwA_P5_MCU_Pin
                          |SSwA_P6_MCU_Pin|SSwA_P7_MCU_Pin|SSwA_P8_MCU_Pin|SSwA_N1_MCU_Pin
                          |SSwA_N2_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin */
  GPIO_InitStruct.Pin = I2C2_SDA_INTPUT_Pin|I2C2_SCL_INTPUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin PFPin
                           PFPin PFPin PFPin */
  GPIO_InitStruct.Pin = ADC1_RESET_Pin|ADC2_RESET_Pin|ADC3_RESET_Pin|SByoffA_P1_MCU_Pin
                          |SByoffA_P2_MCU_Pin|SByoffA_P3_MCU_Pin|SByoffA_P4_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin PFPin */
  GPIO_InitStruct.Pin = INT_OTP_Pin|INT_OCP_OVP_Pin|INT_current_Pin | ADC3_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RS485_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RS485_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = SPI1_NSS_ADC3_Pin|SPI3_NSS_FRAM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = SNOE1_Pin|SNOE2_Pin|SNOE3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = SByoffA_P5_MCU_Pin|SByoffA_P6_MCU_Pin|SByoffA_P7_MCU_Pin|SByoffA_P8_MCU_Pin
                          |DA1_MAX_MCU_Pin|DA2_MAX_MCU_Pin|DA3_MAX_MCU_Pin|DA4_MAX_MCU_Pin
                          |DA5_MAX_MCU_Pin|DA6_MAX_MCU_Pin|DA7_MAX_MCU_Pin|DA8_MAX_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SPI4_NSS_ADC1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SPI4_NSS_ADC1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADC1_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADC1_BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADC2_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADC2_BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SPI2_NSS_ADC2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SPI2_NSS_ADC2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin PDPin PDPin PDPin
                           PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = CTR_ON6_MCU_Pin|CTR_ON7_MCU_Pin|CTR_ON8_MCU_Pin|CLRDOG_Pin
                          |SSwA_N6_MCU_Pin|SSwA_N7_MCU_Pin|SSwA_N8_MCU_Pin|CTR_ON1_MCU_Pin
                          |CTR_ON2_MCU_Pin|CTR_ON3_MCU_Pin|CTR_ON4_MCU_Pin|CTR_ON5_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin */
  GPIO_InitStruct.Pin = I2C1_SDA_EEPROM_Pin|I2C1_SCL_EEPROM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = Fan1_error_Pin|Fan2_error_Pin|Fan3_error_Pin|Fan4_error_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = I2C3_SDA_LED_Pin|I2C3_SCL_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
  //HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);  //等待3片58601都初始化完成后再开启中断

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
