/**
  ******************************************************************************
  * @file    SPI/SPI_FLASH/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FLASH
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
  
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 
extern char USART1_RECV_BUF[100];
extern int ready;//判断一组数据传输是否完成
extern int length;
void USART1_IRQHandler(void)
{

  char temp;
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==SET)
  {

    temp=USART_ReceiveData(USART1);
    if(temp==0x00)//一组数据传输完成，可以进行处理
    {
      ready=1;
      USART1_RECV_BUF[length]=temp;
      length++;//增加的

      
    }

    else{
      USART1_RECV_BUF[length]=temp;
      length++;
      
    }

  }
  
  USART_ClearITPendingBit (USART1,USART_IT_RXNE );//清除中断标志位
  
  }//中断服务
void USART2_IRQHandler(void)
{


  
  USART_ClearITPendingBit (USART2,USART_IT_RXNE );//清除中断标志位
  
  }//中断服务
int status=1;
void EXTI15_10_IRQHandler(void) 
{
  if(EXTI_GetITStatus(EXTI_Line13) != RESET) 
  {
    if(status==1){ 
      TIM_SetCompare1 (TIM3, 0);
      status=0;
    }
    else 
    {
      TIM_SetCompare1 (TIM3, 10000);
      status=1; 
    }
    EXTI_ClearITPendingBit(EXTI_Line13);
  }
  
}
  


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
