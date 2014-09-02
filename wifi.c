#include "wifi.h"

void delay(uint32_t n);
void NVIC_Config()
{
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannel  = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        
    NVIC_Init(&NVIC_InitStructure);//USART1 configuration 
    

    
}
void NVIC2_Config()
{
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannel  = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        
    NVIC_Init(&NVIC_InitStructure);//USART1 configuration 
    

    
}
void USART1_Gpio_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB  , ENABLE);
    
    //PB6->TX  PB7->Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
        
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
}
void USART2_Gpio_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA  , ENABLE);
    
    //PA2->TX  PA3->Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
}
void USART1_Config(void)
{
        USART1_Gpio_Config();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    USART_InitTypeDef USART_InitStructure;
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART1,&USART_InitStructure);   
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    USART_Cmd(USART1,ENABLE);
    
}
void USART2_Config(void)
{
        USART2_Gpio_Config();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    
    USART_InitTypeDef USART_InitStructure;
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART2,&USART_InitStructure);   
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    
    USART_Cmd(USART2,ENABLE);
    
}


