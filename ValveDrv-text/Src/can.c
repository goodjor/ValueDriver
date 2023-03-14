/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
	#include "gpio.h"
	#include "stdio.h"

	CAN_TxHeaderTypeDef TxHeader;
	CAN_RxHeaderTypeDef RxHeader;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	uint8_t TxData[8];
	uint8_t RxData[8];
	uint32_t TxMailbox;
	
	extern uint8_t CAN_Data_0;
	extern uint8_t CAN_Data_1;
	extern uint8_t CAN_Data_2;
	
	extern uint8_t Control_Flag; 	//1 - ��λ������ 0 - ��λ������
	extern uint16_t Set_Time;		//������������ϣ���1��ʱ��
	extern uint16_t Reset_Time;		//������������ϣ���0��ʱ��
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 9;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_8TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CAN_Transmit_1(void)
{
	
	TxHeader.StdId = 0;
	TxHeader.ExtId = 0x19C6D2D3;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;

	TxData[0] = 0x00;			//CAN���߷����Զ����п�����־λ����ʾ�Ƿ����Զ�����
	TxData[1] = 0x11;
	TxData[2] = 0XFF;
	TxData[3] = 0XFF;
	TxData[4] = 0XFF;
	TxData[5] = 0XFF;
	TxData[6] = 0XFF;
	TxData[7] = 0XFF;
	 // printf("in CAN transmit\n");
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		/* Transmission request Error */
		Error_Handler();
	}
		//  printf("transmit ok\n");
}

void CAN_Transmit_2(void)
{
	
	TxHeader.StdId = 0;
	TxHeader.ExtId = 0x19C7D2D3;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;

	TxData[0] = 0x00;			//CAN���߷����Զ����п�����־λ����ʾ�Ƿ����Զ�����
	TxData[1] = 0x11;
	TxData[2] = Reset_Time & 0x00ff;
	TxData[3] = (Reset_Time >> 8) & 0x00ff;
	TxData[4] = 0XFF;
	TxData[5] = 0XFF;
	TxData[6] = 0XFF;
	TxData[7] = 0XFF;
	 // printf("in CAN transmit\n");
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		/* Transmission request Error */
		Error_Handler();
	}
		//  printf("transmit ok\n");
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	//    __HAL_CAN_ENABLE_IT(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);//���¿���FIF00��Ϣ�Һ��ж�

	/* Get RX message */

	//	__disable_irq();

	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
		return;
	}

	if (RxHeader.IDE == CAN_ID_EXT){ 	//ȷ�����յ���չ֡����
		//switch(RxHeader.ExtId & 0x00FFFF00)
		switch (RxHeader.ExtId)
		{
			case 0x19C1D2D4:				//��ֲ��ֿ���
				
			CAN_Data_0 = RxData[0];
			CAN_Data_1 = RxData[1];		
			CAN_Data_2 = RxData[2];		
			
			break;
			
			case 0x19C9D2D3:				//��λ������
				
			Control_Flag = RxData[0] & 0x01;
			Reset_Time = (RxData[3] << 8) | RxData[2];		
			Set_Time = (RxData[5] << 8) | RxData[4];	
			
			break;
						
			default:
				break;
		}
	}
	
	for (int i = 0; i < 8; i++) {
		RxData[i] = 0;
	}
	RxHeader.ExtId = 0;
}

void CAN_User_Init(CAN_HandleTypeDef *hcan) //�û���ʼ������
{
	CAN_FilterTypeDef sFilterConfig;
	HAL_StatusTypeDef HAL_Status;

	//  TxMeg.IDE=CAN_ID_STD;//CAN_ID_EXT;
	//  TxMeg.RTR=CAN_RTR_DATA;

	sFilterConfig.FilterBank = 0;					  //������0
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; //��Ϊ�б�ģʽ
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

	sFilterConfig.FilterIdHigh = 0;
	sFilterConfig.FilterIdLow = 0;

	sFilterConfig.FilterMaskIdHigh = 0;
	sFilterConfig.FilterMaskIdLow = 0;

	//	sFilterConfig.FilterIdHigh =((0x030000F5<<3) >>16) &0xffff;//��������һ����Ա��������Ϊ��֤��
	//  sFilterConfig.FilterIdLow =((0x030000F5<<3)&0xffff) | CAN_ID_EXT;

	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0; //���յ��ı��ķ��뵽FIFO0��

	sFilterConfig.FilterActivation = ENABLE; //�����������
	sFilterConfig.SlaveStartFilterBank = 14;

	HAL_Status = HAL_CAN_ConfigFilter(hcan, &sFilterConfig);
	HAL_Status = HAL_CAN_Start(&hcan1); //����CAN
	if (HAL_Status != HAL_OK)
	{
		printf("����CANʧ��\r\n");
	}
	HAL_Status = HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	if (HAL_Status != HAL_OK)
	{
		printf("���������ж�����ʧ��\r\n");
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
