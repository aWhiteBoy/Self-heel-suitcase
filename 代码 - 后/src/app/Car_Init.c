#include "Car_Init.h"
#include "common.h"

void All_init(void)
{
  gpio_init(PORTE,6,GPO,0);//蜂鸣器模块
  //Buzzer_Ring_ms(100);
  
  LCD_init(FALSE);//TRUE 为正着刷屏
  Disp_single_colour(Yellow);
   
  Ov7725_Init();
  pit_init_ms(PIT0,5);
  //gpio_init(PORTE, 24, GPO, 0);//PWM模块  
  gpio_init(PORTD, 3, GPO, 0);//DIR_R(方向)
  gpio_init(PORTD, 1, GPO, 1);//使能
  FTM_PWM_init(FTM0,CH4,1000,0);//PA4 PWM_R 精度4000
  FTM_PWM_init(FTM1,CH0,200,1200);//PA8 
  //FTM_PWM_freq(FTM1,50);
  //FTM_PWM_init(FTM1,CH0,50,0);//PA8 
  //MPU6050_Init(1000,42);//姿态测量模块
  //Switch_init();//拨码模块
  //uart_init(UART3,115200);//串口通信模块
  //uart_irq_EN(UART3);
  //Parameters_init();  //控制参数模块
  //set_vector_handler(DMA0_VECTORn,DMA0_IRQHandler);      //设置LPTMR的中断复位函数为 PORTA_IRQHandler   
  //Decoder_init();
}


/************************************************
*  函数名称：Switch_init
*  功能说明：拨码开关8个引脚初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2014-1-14    已经测试
*************************************************/
void Switch_init(void)
{
  gpio_init(PORTB, 0, GPI, 1);  
  gpio_init(PORTB, 1, GPI, 1);
  gpio_init(PORTB, 2, GPI, 1);     
  gpio_init(PORTB, 3, GPI, 1); 
  gpio_init(PORTB, 4, GPI, 1);  
  gpio_init(PORTB, 5, GPI, 1);
  gpio_init(PORTB, 6, GPI, 1);
  gpio_init(PORTB, 7, GPI, 1);
}


/************************************************
*  函数名称：Buzzer_Ring_ms
*  功能说明：蜂鸣器叫
*  参数说明：unsigned i nt n，n为n毫秒
*  函数返回：无
*  修改时间：2014-1-14    已经测试
*************************************************/
void Buzzer_Ring_ms(unsigned int n)
{
  buzzer = 1;
  delayms(n);
  buzzer = 0;
}
///************************************************
//*  函数名称：Decoder_init
//*  功能说明：两路测速初始化,FTM1对应硬件A8，A9，FTM1对应硬件A10，A11，
//*  参数说明：无
//*  函数返回：无
//*  修改时间：2014-1-14    已经测试
//*************************************************/
void Decoder_init(void)
{
  /*************FTM1******************/
  SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTA_MASK;   //使能PortB的时钟
  SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_FTM1_MASK;    //使能FlexTimer0(FTM1)的时钟
  PORTA_PCR8 |= PORT_PCR_MUX(0x6);              //复用PortB0的引脚功能为FTM1_QD_PHA
  PORTA_PCR9 |= PORT_PCR_MUX(0x6);              //复用PortB1的引脚功能为FTM1_QD_PHB
  
  FTM1_CNT = 0;
  FTM1_MOD = 10000;
  FTM1_CNTIN = 0;
  FTM1_CNT = 0;
  FTM1_MODE |= FTM_MODE_WPDIS_MASK;
  FTM1_MODE |= FTM_MODE_FTMEN_MASK;
  FTM1_QDCTRL |= FTM_QDCTRL_QUADEN_MASK;
  FTM1_CONF |= FTM_CONF_BDMMODE(3);
  FTM1_SC |= FTM_SC_PS(0);                      //计时器时钟预分频因子为 1
  FTM1_SC |= FTM_SC_TOIE_MASK;
  (void)FTM1_SC;
  FTM1_SC &= ~FTM_SC_TOF_MASK;
  FTM1_SC |= FTM_SC_CLKS(1);     //设置参考时钟为总线时钟并使能输出
  
  /***********FTM2*************/
  //SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK; //使能PortB的时钟
  SIM_BASE_PTR->SCGC3 |= SIM_SCGC3_FTM2_MASK;//使能FlexTimer2(FTM2)的时钟
  PORTA_PCR10 |= PORT_PCR_MUX(0x6);    //复用PortB18的引脚功能为FTM2_QD_PHA
  PORTA_PCR11 |= PORT_PCR_MUX(0x6);   //复用PortB19的引脚功能为FTM2_QD_PHB
  
  FTM2_CNT = 0;
  FTM2_MOD = 10000;
  FTM2_CNTIN = 0;
  FTM2_CNT = 0;
  FTM2_MODE |= FTM_MODE_WPDIS_MASK;
  FTM2_MODE |= FTM_MODE_FTMEN_MASK;
  FTM2_QDCTRL |= FTM_QDCTRL_QUADEN_MASK;
  FTM2_CONF |= FTM_CONF_BDMMODE(3);
  FTM2_SC |= FTM_SC_PS(0);
  FTM2_SC |= FTM_SC_TOIE_MASK;//计时器时钟预分频因子为 1
  (void)FTM2_SC;
  FTM2_SC &= ~FTM_SC_TOF_MASK;
  FTM2_SC |= FTM_SC_CLKS(1);//设置参考时钟为总线时钟并使能输出
}




