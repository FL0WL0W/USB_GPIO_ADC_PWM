/**
  ******************************************************************************
  * @file           : usbd_cdc_if.cpp
  * @version        : v2.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */

#include "stdlib.h"
#include <algorithm>
#include <string>

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
#define APP_RX_DATA_SIZE  1000
#define APP_TX_DATA_SIZE  1000
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  /* USER CODE BEGIN 3 */
  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  /* USER CODE BEGIN 5 */
  switch(cmd)
  {
    case CDC_SEND_ENCAPSULATED_COMMAND:

    break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

    break;

    case CDC_SET_COMM_FEATURE:

    break;

    case CDC_GET_COMM_FEATURE:

    break;

    case CDC_CLEAR_COMM_FEATURE:

    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
    case CDC_SET_LINE_CODING:

    break;

    case CDC_GET_LINE_CODING:

    break;

    case CDC_SET_CONTROL_LINE_STATE:

    break;

    case CDC_SEND_BREAK:

    break;

  default:
    break;
  }

  return (USBD_OK);
  /* USER CODE END 5 */
}
	
/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result
  *         in receiving more data while previous ones are still not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
void *buildConfig;
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
	/* USER CODE BEGIN 6 */	
	std::string command = std::string((char *)Buf, *Len);
	std::transform(command.begin(), command.end(), command.begin(),::toupper);
	
	if (*Len > 19 && command .find("INITIALIZE GPIO ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		unsigned int charPos = 16;
		
		GPIO_TypeDef *GPIO = 0;
				
		if (*Len > charPos)
		{
			switch (Buf[charPos])
			{
			case 'A':
			case 'a':
				GPIO = GPIOA;
				break;
			case 'B':
			case 'b':
				GPIO = GPIOB;
				break;
			case 'C':
			case 'c':
				GPIO = GPIOC;
				break;
			default:
				break;
			}
		}
		
		charPos += 1;
				
		unsigned int pinNum = 16;
		if (*Len > charPos)
		{
			if (Buf[charPos + 1] == ' ')
			{
				char subbuf[1];
				memcpy(subbuf, &Buf[charPos], 1);
				pinNum = std::atoi(subbuf);
				charPos += 2;
			}
			else
			{
				char subbuf[2];
				memcpy(subbuf, &Buf[charPos], 2);
				pinNum = std::atoi(subbuf);
				charPos += 3;
			}
		}
		
		unsigned short GPIO_PIN = 0;
		switch (pinNum)
		{
		case 0:
			GPIO_PIN = GPIO_PIN_0;
			break;
		case 1:
			GPIO_PIN = GPIO_PIN_1;
			break;
		case 2:
			GPIO_PIN = GPIO_PIN_2;
			break;
		case 3:
			GPIO_PIN = GPIO_PIN_3;
			break;
		case 4:
			GPIO_PIN = GPIO_PIN_4;
			break;
		case 5:
			GPIO_PIN = GPIO_PIN_5;
			break;
		case 6:
			GPIO_PIN = GPIO_PIN_6;
			break;
		case 7:
			GPIO_PIN = GPIO_PIN_7;
			break;
		case 8:
			GPIO_PIN = GPIO_PIN_8;
			break;
		case 9:
			GPIO_PIN = GPIO_PIN_9;
			break;
		case 10:
			GPIO_PIN = GPIO_PIN_10;
			break;
		case 11:
			GPIO_PIN = GPIO_PIN_11;
			break;
		case 12:
			GPIO_PIN = GPIO_PIN_12;
			break;
		case 13:
			GPIO_PIN = GPIO_PIN_13;
			break;
		case 14:
			GPIO_PIN = GPIO_PIN_14;
			break;
		case 15:
			GPIO_PIN = GPIO_PIN_15;
			break;
		}
		
		if (*Len > charPos && GPIO != 0 && pinNum < 16)
		{
			if (Buf[charPos] == 'I' || Buf[charPos] == 'i')
			{
				GPIO_InitTypeDef GPIO_InitStructure;
		
				GPIO_InitStructure.Pin = GPIO_PIN;
		
				GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
				GPIO_InitStructure.Pull = GPIO_NOPULL;
				GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
				if (command.find("UP") > charPos)
				{
					GPIO_InitStructure.Pull = GPIO_PULLUP;
				}
				else if (command.find("DOWN") > charPos)
				{
					GPIO_InitStructure.Pull = GPIO_PULLDOWN;
				}
				HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
				
				if (GPIO == GPIOA)
				{
					if (GPIO_InitStructure.Pull == GPIO_PULLUP)
					{
						sprintf(responseText, "GPIO A%d Initialized as input with pull up.\n", pinNum);
					}
					else if (GPIO_InitStructure.Pull == GPIO_PULLDOWN)
					{
						sprintf(responseText, "GPIO A%d Initialized as input with pull down.\n", pinNum);
					}
					else
					{
						sprintf(responseText, "GPIO A%d Initialized as floating input.\n", pinNum);
					}
				}
				else if (GPIO == GPIOB)
				{
					if (GPIO_InitStructure.Pull == GPIO_PULLUP)
					{
						sprintf(responseText, "GPIO B%d Initialized as input with pull up.\n", pinNum);
					}
					else if (GPIO_InitStructure.Pull == GPIO_PULLDOWN)
					{
						sprintf(responseText, "GPIO B%d Initialized as input with pull down.\n", pinNum);
					}
					else
					{
						sprintf(responseText, "GPIO B%d Initialized as floating input.\n", pinNum);
					}
				}
				else if (GPIO == GPIOC)
				{
					if (GPIO_InitStructure.Pull == GPIO_PULLUP)
					{
						sprintf(responseText, "GPIO C%d Initialized as input with pull up.\n", pinNum);
					}
					else if (GPIO_InitStructure.Pull == GPIO_PULLDOWN)
					{
						sprintf(responseText, "GPIO C%d Initialized as input with pull down.\n", pinNum);
					}
					else
					{
						sprintf(responseText, "GPIO C%d Initialized as floating input.\n", pinNum);
					}
				}
			}
			else if (Buf[charPos] == 'O' || Buf[charPos] == 'o')
			{
				GPIO_InitTypeDef GPIO_InitStructure;
		
				GPIO_InitStructure.Pin = GPIO_PIN;
		
				GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
				GPIO_InitStructure.Pull = GPIO_NOPULL;
				GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
				HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
				
				if (GPIO == GPIOA)
				{
					sprintf(responseText, "GPIO A%d Initialized as output.\n", pinNum);
				}
				else if (GPIO == GPIOB)
				{
					sprintf(responseText, "GPIO B%d Initialized as output.\n", pinNum);
				}
				else if (GPIO == GPIOC)
				{
					sprintf(responseText, "GPIO C%d Initialized as output.\n", pinNum);
				}
			}
		}
		
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	else if (command.find("INITIALIZE ADC ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	else if (command.find("INITIALIZE PWM ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	else if (command.find("SET GPIO ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		unsigned int charPos = 9;
		
		GPIO_TypeDef *GPIO = 0;
				
		if (*Len > charPos)
		{
			switch (Buf[charPos])
			{
			case 'A':
			case 'a':
				GPIO = GPIOA;
				break;
			case 'B':
			case 'b':
				GPIO = GPIOB;
				break;
			case 'C':
			case 'c':
				GPIO = GPIOC;
				break;
			default:
				break;
			}
		}
		
		charPos += 1;
				
		unsigned int pinNum = 16;
		if (*Len > charPos)
		{
			if (Buf[charPos + 1] == ' ')
			{
				char subbuf[1];
				memcpy(subbuf, &Buf[charPos], 1);
				pinNum = std::atoi(subbuf);
				charPos += 2;
			}
			else
			{
				char subbuf[2];
				memcpy(subbuf, &Buf[charPos], 2);
				pinNum = std::atoi(subbuf);
				charPos += 3;
			}
		}
		
		unsigned short GPIO_PIN = 0;
		switch (pinNum)
		{
		case 0:
			GPIO_PIN = GPIO_PIN_0;
			break;
		case 1:
			GPIO_PIN = GPIO_PIN_1;
			break;
		case 2:
			GPIO_PIN = GPIO_PIN_2;
			break;
		case 3:
			GPIO_PIN = GPIO_PIN_3;
			break;
		case 4:
			GPIO_PIN = GPIO_PIN_4;
			break;
		case 5:
			GPIO_PIN = GPIO_PIN_5;
			break;
		case 6:
			GPIO_PIN = GPIO_PIN_6;
			break;
		case 7:
			GPIO_PIN = GPIO_PIN_7;
			break;
		case 8:
			GPIO_PIN = GPIO_PIN_8;
			break;
		case 9:
			GPIO_PIN = GPIO_PIN_9;
			break;
		case 10:
			GPIO_PIN = GPIO_PIN_10;
			break;
		case 11:
			GPIO_PIN = GPIO_PIN_11;
			break;
		case 12:
			GPIO_PIN = GPIO_PIN_12;
			break;
		case 13:
			GPIO_PIN = GPIO_PIN_13;
			break;
		case 14:
			GPIO_PIN = GPIO_PIN_14;
			break;
		case 15:
			GPIO_PIN = GPIO_PIN_15;
			break;
		}
		
		if (*Len > charPos && GPIO != 0 && pinNum < 16)
		{
			switch (Buf[charPos])
			{
			case 'T':
			case 't':
			case '1':
				HAL_GPIO_WritePin(GPIO, GPIO_PIN, GPIO_PIN_SET);
				if (GPIO == GPIOA)
				{
					sprintf(responseText, "GPIO A%d Set to 1.\n", pinNum);
				}
				else if (GPIO == GPIOB)
				{
					sprintf(responseText, "GPIO B%d Set to 1.\n", pinNum);
				}
				else if (GPIO == GPIOC)
				{
					sprintf(responseText, "GPIO C%d Set to 1.\n", pinNum);
				}
				break;
			case 'F':
			case 'f':
			case '0':
				HAL_GPIO_WritePin(GPIO, GPIO_PIN, GPIO_PIN_RESET);
				if (GPIO == GPIOA)
				{
					sprintf(responseText, "GPIO A%d Set to 0.\n", pinNum);
				}
				else if (GPIO == GPIOB)
				{
					sprintf(responseText, "GPIO B%d Set to 0.\n", pinNum);
				}
				else if (GPIO == GPIOC)
				{
					sprintf(responseText, "GPIO C%d Set to 0.\n", pinNum);
				}
				break;
			case 'O':
				if (*Len > charPos + 1)
				{
					switch (Buf[charPos + 1])
					{
					case 'N':
					case 'n':
						HAL_GPIO_WritePin(GPIO, GPIO_PIN, GPIO_PIN_SET);
						if (GPIO == GPIOA)
						{
							sprintf(responseText, "GPIO A%d Set to 1.\n", pinNum);
						}
						else if (GPIO == GPIOB)
						{
							sprintf(responseText, "GPIO B%d Set to 1.\n", pinNum);
						}
						else if (GPIO == GPIOC)
						{
							sprintf(responseText, "GPIO C%d Set to 1.\n", pinNum);
						}
						break;
					case 'F':
					case 'f':
						HAL_GPIO_WritePin(GPIO, GPIO_PIN, GPIO_PIN_RESET);
						if (GPIO == GPIOA)
						{
							sprintf(responseText, "GPIO A%d Set to 0.\n", pinNum);
						}
						else if (GPIO == GPIOB)
						{
							sprintf(responseText, "GPIO B%d Set to 0.\n", pinNum);
						}
						else if (GPIO == GPIOC)
						{
							sprintf(responseText, "GPIO C%d Set to 0.\n", pinNum);
						}
						break;
					}
				}
				break;
			}
		}
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	else if (command.find("READ GPIO ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	else if (command.find("READ ADC ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	else if (command.find("SET PWM ") == 0)
	{
		char responseText[64] = "Invalid Parameters\n";
		CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
	}
	
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);
  
	return (USBD_OK);
	/* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0){
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
