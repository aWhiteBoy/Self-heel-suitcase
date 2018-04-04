#include "isr.h"

void PIT0_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);
  static unsigned long Time_motor=0,Time_servo=0,Time_getway=0;
  Time_motor++;Time_servo++;Time_getway++;
  if(Time_getway==3)
  {
    get_target();
    road_display();
    Time_getway=0;
  }
  if(Time_motor==2)
  {
    FTM_PWM_Duty(FTM0, CH4, 220);//׼���������(�����·��ʶ������)
    Time_motor=0;
  }
  if(Time_servo==4)
  {
    servo_PID();
    FTM_PWM_Duty(FTM1, CH0, Servo_output);//׼���������(�����·��ʶ������)
    Time_servo=0;
  }
}

/*
*  �������ƣ�USART3_IRQHandler
*  ����˵��������3 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѳ���
*  ��    ע��
*************************************************************************/
void USART3_IRQHandler(void)
{
  unsigned char uart_control_temp=0;
  uart_control_temp = uart_getchar (UART3);//���յ�һ������
  if(uart_control_temp==0)
    return;
  switch(uart_control_temp)
  {      
    case 'a': Angle.P+=1; SCISendFloat(UART3,Angle.P);Buzzer_Ring_ms(10);break;
    case 'b': Angle.P-=1; SCISendFloat(UART3,Angle.P);Buzzer_Ring_ms(10);break;
   
    case 'c': Angle.D+=0.1;SCISendFloat (UART3,Angle.D);Buzzer_Ring_ms(10);break;
    case 'd': Angle.D-=0.1;SCISendFloat (UART3,Angle.D);Buzzer_Ring_ms(10);break;
    
    case 'e': Direction.P+=1; SCISendFloat (UART3,Direction.P);  Buzzer_Ring_ms(10);break;
    case 'f': Direction.P-=1; SCISendFloat (UART3,Direction.P);Buzzer_Ring_ms(10);break;
    
    case 'g': Direction.D+=0.1;SCISendFloat (UART3,Direction.D);Buzzer_Ring_ms(10);break;
    case 'h': Direction.D-=0.1;SCISendFloat (UART3,Direction.D);Buzzer_Ring_ms(10);break;  
    
    
    case '+': Angle.OFFSET+=0.1;SCISendFloat (UART3,Angle.OFFSET);Buzzer_Ring_ms(10);break;

    case '-': Angle.OFFSET-=0.1;SCISendFloat (UART3,Angle.OFFSET);Buzzer_Ring_ms(10);break;    
   
              
    default: break;
  }
  uart_putchar(UART3,'\n');  
  uart_control_temp=0;
}

/*************************************************************************
*  �������ƣ�PORTA_IRQHandler
*  ����˵����PORTA�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѳ���
*  ��    ע��
*************************************************************************/
extern u8 Image_Flag;
void PORTC_IRQHandler()
{
    PORTC_ISFR  = ~0;              //���жϱ�־λ
    Image_Flag=0;
    if(img_flag == IMG_START)	//��Ҫ��ʼ�ɼ�ͼ��
    {
        DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTC_BYTE0_IN, (void *)(Image_fire), PTC12, DMA_BYTE1, CAMERA_SIZE , DMA_falling);//KEEPON
        DMA_EN(CAMERA_DMA_CH);            		//ʹ��ͨ��CHn Ӳ������
        DMA_DADDR(CAMERA_DMA_CH) = (u32)Image_fire; //�ָ���ַ
        img_flag = IMG_GATHER;		        //���ͼ��ɼ���
        disable_irq(89);  
    }
    else					//ͼ��ɼ�����
    {
        img_flag = IMG_START;	//��ʼ�ɼ�ͼ��
        PORTC_ISFR=~0;		//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
        enable_irq(89); 
    }
}

/*************************************************************************
*  �������ƣ�DMA0_IRQHandler
*  ����˵����DMA0�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѳ���
*  ��    ע��
*************************************************************************/
u8 Image_Flag=0;
void DMA0_IRQHandler()
{
    DMA_DIS(CAMERA_DMA_CH);            	//�ر�ͨ��CHn Ӳ������
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //���ͨ�������жϱ�־λ
    img_flag = IMG_FINISH;
    img_flag = IMG_START;		//��ʼ�ɼ�ͼ��
    PORTC_ISFR=~0;			//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
    enable_irq(89);  
    Image_Flag=1;
}