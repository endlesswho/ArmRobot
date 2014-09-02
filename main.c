#include"pwm.h"
#include"wifi.h"
#include<stdio.h>
#include<stdlib.h>
#include<stm32f4xx_it.h>
#include<math.h>
#define dataNum 4
char USART1_RECV_BUF[100];
int ready=0;
int length=0;
int *GetIntData();
void sendInstruction(int servo,int degree);

extern void Delay_us(__IO uint32_t nTime);//延时us函数



int main(void)
{
       NVIC_Config();
       USART1_Config();

       //初始化串口1，中断方式接收
      

        int pitch=90,roll=90,yaw=0, radius=500;
         sendInstruction(9,roll);
         sendInstruction(8,pitch);
         sendInstruction(7,yaw);
         sendInstruction(6,0);
         sendInstruction(5,0);//初始状态
        while(1){
   
     
         int *data;
         if(ready==1){
         USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);//暂时关闭接收中断
         data=GetIntData();
         pitch=*data;
         roll=*(data+1);
         yaw=*(data+2);
         radius=*(data+3);
         sendInstruction(9,roll);//控制左右倾角
         sendInstruction(8,pitch);//控制仰角和俯角
         sendInstruction(7,yaw);//控制朝向
         if(radius<40) sendInstruction(10,1600);//合爪子
         else sendInstruction(10,900);//张爪子
         ready=0;
         length=0;
         free(data);//释放内存
        
         USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//打开接收中断
          }
        }
        
        
      
}
/*该函数将缓冲区内的数据转化为int类型，然后将int数组的指针返回*/
int *GetIntData()
{
 
  
  int beginPos[dataNum],endPos[dataNum];//记录每个数据的开始和结束的位置
  beginPos[0]=0;
  int num=0;
  for(int x=0;x<length;x++)
  {
    if(USART1_RECV_BUF[x]==' '||USART1_RECV_BUF[x]=='\0')
    {
      endPos[num]=x-1;
      
      num++;
      if(num==dataNum ) break;//有dataNum个数据
      beginPos[num]=x+1;
    
    }
  }
  num=0;
  char temp[10];//临时存放分割好的字符串
  int *Data=(int*)calloc(dataNum,sizeof(int));//用于存储转化后的数据
  for(int x=0;x<dataNum;x++)
  {

    for(int y=beginPos[x];y<=endPos[x];y++)
    {
      if((USART1_RECV_BUF[y]<48&&USART1_RECV_BUF[y]!=45)||USART1_RECV_BUF[y]>57) continue;//跳过非法字符
      temp[num]=USART1_RECV_BUF[y];
      num++;
      if(y==endPos[x])
      {
        temp[num]='\0';// 最后一位结束符
        num=0;
      }
    }
    (*(Data+x))=atoi(temp); //转化为整数
    
 
  }
  return Data;

}

void sendInstruction(int servo,int degree)//将leapmotion的角度数据转化为舵机控制板的命令
{
  char instruction[100];
  int position;
  switch (servo){
  case 9: position=degree*(-11.1)+1350;
           break;
  case 8: position=degree*11.1+1350;
           break;
  case 7: position=degree*(-11.1)+1350;
           break;
  case 10:position=degree;
           break;
  default:position=degree*11.1+1350;
           break;
  }
  
  sprintf(instruction,"#%d P%d T50\r\n",servo,position);
  for(int x=0;instruction[x]!='\n';x++)
  {
    
    USART_SendData(USART1,instruction[x]);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
 
  }
  USART_SendData(USART1, '\n');
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
  

  
}

