/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	key.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2016-11-23
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		����IO��ʼ�������������ж�
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//����ͷ�ļ�
#include <string.h>
#include "key.h"
//Ӳ������
#include "delay.h"
#include "beep.h"
#include "sht20.h"
#include "stdio.h"
#include "nbiot.h"
#include "platform.h"
#include "utils.h"
/*
************************************************************
*	�������ƣ�	Key_Init
*
*	�������ܣ�	����IO��ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		SW2-PD2		SW3-PC11	SW4-PC12	SW5-PC13	
*				����Ϊ�͵�ƽ		�ͷ�Ϊ�ߵ�ƽ
************************************************************
*/
void Key_Init(void)
{
	GPIO_InitTypeDef gpioInitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;  
  NVIC_InitTypeDef NVIC_InitStruct;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);	//��GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
	
	gpioInitStructure.GPIO_Mode = GPIO_Mode_IPU;									//����Ϊ��������ģʽ
	gpioInitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;			//��ʼ��Pin11��12��13
	gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//���ص����Ƶ��
	
	GPIO_Init(GPIOC, &gpioInitStructure);											//��ʼ��GPIOC
	
    NVIC_InitStruct.NVIC_IRQChannel =EXTI15_10_IRQn;  
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;  
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4;  
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  
      
    NVIC_Init(&NVIC_InitStruct);  
	
    EXTI_ClearITPendingBit(EXTI_Line11);  
	//	EXTI_DeInit();
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);  
    EXTI_InitStructure.EXTI_Line=EXTI_Line11;  
    EXTI_InitStructure.EXTI_LineCmd =ENABLE;  
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;  
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;  
  
    EXTI_Init(&EXTI_InitStructure);  
	
}

/*
************************************************************
*	�������ƣ�	KeyScan
*
*	�������ܣ�	������ƽɨ��
*
*	��ڲ�����	GPIOX����Ҫɨ���GPIO��	NUM����GPIO���ڵı��
*
*	���ز�����	IO��ƽ״̬
*
*	˵����		
************************************************************
*/
_Bool KeyScan(GPIO_TypeDef* GPIOX, unsigned int NUM)
{
	
	if(GPIOX == GPIOC)
	{
		if(!GPIO_ReadInputDataBit(GPIOC, NUM))	//����  Ϊ��
		{
			return KEYDOWN;
		}
		else									//����  Ϊ��
		{
			return KEYUP;
		}
	}

		
	return KEYUP;								//Ĭ�Ϸ��ذ����ͷ�
	
}

/*
************************************************************
*	�������ƣ�	Keyboard
*
*	�������ܣ�	�������ܼ��
*
*	��ڲ�����	
*
*	���ز�����	IO��ƽ״̬
*
*	˵����		
************************************************************
*/
unsigned char Keyboard(void)
{
	
	if(KeyScan(GPIOC, KEY0) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY0) != KEYUP);		//�ȴ��ͷ�
		return KEY0DOWN;
	}
	
	if(KeyScan(GPIOC, KEY1) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY1) != KEYUP);		//�ȴ��ͷ�
		return KEY1DOWN;
	}
	
	if(KeyScan(GPIOC, KEY2) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY2) != KEYUP);		//�ȴ��ͷ�
		return KEY2DOWN;
	}
	
	if(KeyScan(GPIOC, KEY3) == KEYDOWN)
	{
		while(KeyScan(GPIOC, KEY3) != KEYUP);		//�ȴ��ͷ�
		return KEY3DOWN;
	}
	
	return KEYNONE;
	
}

/*
************************************************************
*	�������ƣ�	Key_test
*
*	�������ܣ�	��������
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		SW0-PC0		SW1-PC1	SW2-PC2	SW3-PC3	
*				����Ϊ�͵�ƽ		�ͷ�Ϊ�ߵ�ƽ
************************************************************
*/
extern nbiot_value_t dicr;
void Key_test(void)
{

			 // printf("hello\r\n");
	     if(!(dicr.flag&NBIOT_UPDATED)){
			  dicr.flag |= NBIOT_UPDATED;
        nbiot_free(dicr.value.as_buf.val);
				dicr.value.as_buf.len = strlen("trigger");
        dicr.value.as_buf.val = nbiot_strdup("trigger", dicr.value.as_buf.len);
			}	 

}

