#include "Car_Init.h"
#include "common.h"

void All_init(void)
{
  gpio_init(PORTE,6,GPO,0);//������ģ��
  //Buzzer_Ring_ms(100);
  
  LCD_init(FALSE);//TRUE Ϊ����ˢ��
  Disp_single_colour(Yellow);
   
  Ov7725_Init();
  pit_init_ms(PIT0,5);
  //gpio_init(PORTE, 24, GPO, 0);//PWMģ��  
  gpio_init(PORTD, 3, GPO, 0);//DIR_R(����)
  gpio_init(PORTD, 1, GPO, 1);//ʹ��
  FTM_PWM_init(FTM0,CH4,1000,0);//PA4 PWM_R ����4000
  FTM_PWM_init(FTM1,CH0,200,1200);//PA8 
  //FTM_PWM_freq(FTM1,50);
  //FTM_PWM_init(FTM1,CH0,50,0);//PA8 
  //MPU6050_Init(1000,42);//��̬����ģ��
  //Switch_init();//����ģ��
  //uart_init(UART3,115200);//����ͨ��ģ��
  //uart_irq_EN(UART3);
  //Parameters_init();  //���Ʋ���ģ��
  //set_vector_handler(DMA0_VECTORn,DMA0_IRQHandler);      //����LPTMR���жϸ�λ����Ϊ PORTA_IRQHandler   
  //Decoder_init();
}


/************************************************
*  �������ƣ�Switch_init
*  ����˵�������뿪��8�����ų�ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
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
*  �������ƣ�Buzzer_Ring_ms
*  ����˵������������
*  ����˵����unsigned i nt n��nΪn����
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void Buzzer_Ring_ms(unsigned int n)
{
  buzzer = 1;
  delayms(n);
  buzzer = 0;
}
///************************************************
//*  �������ƣ�Decoder_init
//*  ����˵������·���ٳ�ʼ��,FTM1��ӦӲ��A8��A9��FTM1��ӦӲ��A10��A11��
//*  ����˵������
//*  �������أ���
//*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
//*************************************************/
void Decoder_init(void)
{
  /*************FTM1******************/
  SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTA_MASK;   //ʹ��PortB��ʱ��
  SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_FTM1_MASK;    //ʹ��FlexTimer0(FTM1)��ʱ��
  PORTA_PCR8 |= PORT_PCR_MUX(0x6);              //����PortB0�����Ź���ΪFTM1_QD_PHA
  PORTA_PCR9 |= PORT_PCR_MUX(0x6);              //����PortB1�����Ź���ΪFTM1_QD_PHB
  
  FTM1_CNT = 0;
  FTM1_MOD = 10000;
  FTM1_CNTIN = 0;
  FTM1_CNT = 0;
  FTM1_MODE |= FTM_MODE_WPDIS_MASK;
  FTM1_MODE |= FTM_MODE_FTMEN_MASK;
  FTM1_QDCTRL |= FTM_QDCTRL_QUADEN_MASK;
  FTM1_CONF |= FTM_CONF_BDMMODE(3);
  FTM1_SC |= FTM_SC_PS(0);                      //��ʱ��ʱ��Ԥ��Ƶ����Ϊ 1
  FTM1_SC |= FTM_SC_TOIE_MASK;
  (void)FTM1_SC;
  FTM1_SC &= ~FTM_SC_TOF_MASK;
  FTM1_SC |= FTM_SC_CLKS(1);     //���òο�ʱ��Ϊ����ʱ�Ӳ�ʹ�����
  
  /***********FTM2*************/
  //SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK; //ʹ��PortB��ʱ��
  SIM_BASE_PTR->SCGC3 |= SIM_SCGC3_FTM2_MASK;//ʹ��FlexTimer2(FTM2)��ʱ��
  PORTA_PCR10 |= PORT_PCR_MUX(0x6);    //����PortB18�����Ź���ΪFTM2_QD_PHA
  PORTA_PCR11 |= PORT_PCR_MUX(0x6);   //����PortB19�����Ź���ΪFTM2_QD_PHB
  
  FTM2_CNT = 0;
  FTM2_MOD = 10000;
  FTM2_CNTIN = 0;
  FTM2_CNT = 0;
  FTM2_MODE |= FTM_MODE_WPDIS_MASK;
  FTM2_MODE |= FTM_MODE_FTMEN_MASK;
  FTM2_QDCTRL |= FTM_QDCTRL_QUADEN_MASK;
  FTM2_CONF |= FTM_CONF_BDMMODE(3);
  FTM2_SC |= FTM_SC_PS(0);
  FTM2_SC |= FTM_SC_TOIE_MASK;//��ʱ��ʱ��Ԥ��Ƶ����Ϊ 1
  (void)FTM2_SC;
  FTM2_SC &= ~FTM_SC_TOF_MASK;
  FTM2_SC |= FTM_SC_CLKS(1);//���òο�ʱ��Ϊ����ʱ�Ӳ�ʹ�����
}




