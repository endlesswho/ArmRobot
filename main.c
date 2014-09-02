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

extern void Delay_us(__IO uint32_t nTime);//��ʱus����



int main(void)
{
       NVIC_Config();
       USART1_Config();

       //��ʼ������1���жϷ�ʽ����
      

        int pitch=90,roll=90,yaw=0, radius=500;
         sendInstruction(9,roll);
         sendInstruction(8,pitch);
         sendInstruction(7,yaw);
         sendInstruction(6,0);
         sendInstruction(5,0);//��ʼ״̬
        while(1){
   
     
         int *data;
         if(ready==1){
         USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);//��ʱ�رս����ж�
         data=GetIntData();
         pitch=*data;
         roll=*(data+1);
         yaw=*(data+2);
         radius=*(data+3);
         sendInstruction(9,roll);//�����������
         sendInstruction(8,pitch);//�������Ǻ͸���
         sendInstruction(7,yaw);//���Ƴ���
         if(radius<40) sendInstruction(10,1600);//��צ��
         else sendInstruction(10,900);//��צ��
         ready=0;
         length=0;
         free(data);//�ͷ��ڴ�
        
         USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�򿪽����ж�
          }
        }
        
        
      
}
/*�ú������������ڵ�����ת��Ϊint���ͣ�Ȼ��int�����ָ�뷵��*/
int *GetIntData()
{
 
  
  int beginPos[dataNum],endPos[dataNum];//��¼ÿ�����ݵĿ�ʼ�ͽ�����λ��
  beginPos[0]=0;
  int num=0;
  for(int x=0;x<length;x++)
  {
    if(USART1_RECV_BUF[x]==' '||USART1_RECV_BUF[x]=='\0')
    {
      endPos[num]=x-1;
      
      num++;
      if(num==dataNum ) break;//��dataNum������
      beginPos[num]=x+1;
    
    }
  }
  num=0;
  char temp[10];//��ʱ��ŷָ�õ��ַ���
  int *Data=(int*)calloc(dataNum,sizeof(int));//���ڴ洢ת���������
  for(int x=0;x<dataNum;x++)
  {

    for(int y=beginPos[x];y<=endPos[x];y++)
    {
      if((USART1_RECV_BUF[y]<48&&USART1_RECV_BUF[y]!=45)||USART1_RECV_BUF[y]>57) continue;//�����Ƿ��ַ�
      temp[num]=USART1_RECV_BUF[y];
      num++;
      if(y==endPos[x])
      {
        temp[num]='\0';// ���һλ������
        num=0;
      }
    }
    (*(Data+x))=atoi(temp); //ת��Ϊ����
    
 
  }
  return Data;

}

void sendInstruction(int servo,int degree)//��leapmotion�ĽǶ�����ת��Ϊ������ư������
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

