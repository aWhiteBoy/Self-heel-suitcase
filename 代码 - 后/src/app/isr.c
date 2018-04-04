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
    FTM_PWM_Duty(FTM0, CH4, 220);//准备留给电机(需放在路径识别后进行)
    Time_motor=0;
  }
  if(Time_servo==4)
  {
    servo_PID();
    FTM_PWM_Duty(FTM1, CH0, Servo_output);//准备留给舵机(需放在路径识别后进行)
    Time_servo=0;
  }
}

/*
*  函数名称：USART3_IRQHandler
*  功能说明：串口3 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-1-14    已测试
*  备    注：
*************************************************************************/
void USART3_IRQHandler(void)
{
  unsigned char uart_control_temp=0;
  uart_control_temp = uart_getchar (UART3);//接收到一个数据
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
*  函数名称：PORTA_IRQHandler
*  功能说明：PORTA中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-1-14    已测试
*  备    注：
*************************************************************************/
extern u8 Image_Flag;
void PORTC_IRQHandler()
{
    PORTC_ISFR  = ~0;              //清中断标志位
    Image_Flag=0;
    if(img_flag == IMG_START)	//需要开始采集图像
    {
        DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTC_BYTE0_IN, (void *)(Image_fire), PTC12, DMA_BYTE1, CAMERA_SIZE , DMA_falling);//KEEPON
        DMA_EN(CAMERA_DMA_CH);            		//使能通道CHn 硬件请求
        DMA_DADDR(CAMERA_DMA_CH) = (u32)Image_fire; //恢复地址
        img_flag = IMG_GATHER;		        //标记图像采集中
        disable_irq(89);  
    }
    else					//图像采集错误
    {
        img_flag = IMG_START;	//开始采集图像
        PORTC_ISFR=~0;		//写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
        enable_irq(89); 
    }
}

/*************************************************************************
*  函数名称：DMA0_IRQHandler
*  功能说明：DMA0中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-1-14    已测试
*  备    注：
*************************************************************************/
u8 Image_Flag=0;
void DMA0_IRQHandler()
{
    DMA_DIS(CAMERA_DMA_CH);            	//关闭通道CHn 硬件请求
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //清除通道传输中断标志位
    img_flag = IMG_FINISH;
    img_flag = IMG_START;		//开始采集图像
    PORTC_ISFR=~0;			//写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
    enable_irq(89);  
    Image_Flag=1;
}