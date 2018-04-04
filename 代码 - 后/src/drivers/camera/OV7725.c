#include "define.h"
#include "common.h"
#include "gpio.h"
#include "port.h"
#include "dma.h"
#include "SCCB.h"
#include "OV7725.h"
#include "OV7725_REG.h"

unsigned char Image_fire[CAMERA_H+1][CAMERA_DMA_NUM]={{0}};
volatile u8 img_flag = IMG_FINISH;		//ͼ��״̬

void Ov7725_exti_Init()
{
    //FIFO�˿ڳ�ʼ��
    gpio_init(PORTC,0, GPI, HIGH);
    gpio_init(PORTC,1, GPI, HIGH);
    gpio_init(PORTC,2, GPI, HIGH);
    gpio_init(PORTC,3, GPI, HIGH);
    gpio_init(PORTC,4, GPI, HIGH);
    gpio_init(PORTC,5, GPI, HIGH);
    gpio_init(PORTC,6, GPI, HIGH);
    gpio_init(PORTC,7, GPI, HIGH);
    //DMAͨ��0��ʼ����PTC12�����ش���DMA���䣬Դ��ַΪPTC_BYTE0_IN��Ŀ�ĵ�ַΪ��BUFF ��ÿ�δ���1Byte������CAMERA_SIZE�κ�ֹͣ����
    DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTC_BYTE0_IN, (void *)(Image_fire), PTC12, DMA_BYTE1, CAMERA_SIZE , DMA_falling);//KEEPON
    port_init(PTC12,DMA_RISING | PULLUP );    //PCLK
    DMA_IRQ_EN(DMA_CH0);
    port_init(PTC10, IRQ_RISING| PULLUP | PF);    //���жϣ��������½��ش����жϣ����˲�
    disable_irq(89); 			          //�ر�PTA���ж�
}

void ov7725_get_img()
{
    img_flag = IMG_START;		//��ʼ�ɼ�ͼ��
    PORTC_ISFR=~0;			//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
    enable_irq(89); 			//����PTA���ж�
    while(img_flag != IMG_FINISH)       //�ȴ�ͼ��ɼ����
    {
        if(img_flag == IMG_FAIL)        //����ͼ��ɼ����������¿�ʼ�ɼ�
        {
            img_flag = IMG_START;	//��ʼ�ɼ�ͼ��
            PORTC_ISFR=~0;		//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
            enable_irq(89); 		//����PTA���ж�
        }
    }
}


/*OV7725��ʼ�����ñ�*/
Register_Info ov7727_reg[] =
{
    //�Ĵ������Ĵ���ֵ��
    {COM4         ,0xC1},
    {CLKRC        ,0x00}, 
    {COM2         ,0x03}, 
    {COM3         ,0xD0}, 
    {COM7         ,0x40},  
    {HSTART       ,0x3F},
    {HSIZE        ,0x50}, 
    {VSTRT        ,0x03},
    {VSIZE        ,0x78},
    {HREF         ,0x00}, 
    {SCAL0        ,0x0A},
    {AWB_Ctrl0    ,0xE0},
    {DSPAuto      ,0xff},
    {DSP_Ctrl2    ,0x0C}, 
    {DSP_Ctrl3    ,0x00}, 
    {DSP_Ctrl4    ,0x00},
    
#if (CAMERA_W == 80)
{HOutSize     ,0x14},
#elif (CAMERA_W == 160)  
{HOutSize     ,0x28},
#elif (CAMERA_W == 240)  
{HOutSize     ,0x3c},
#elif (CAMERA_W == 320)  
{HOutSize     ,0x50}, 
#else

#endif

#if (CAMERA_H == 60 )
{VOutSize     ,0x1E},
#elif (CAMERA_H == 120 )
{VOutSize     ,0x3c},
#elif (CAMERA_H == 180 )
{VOutSize     ,0x5a},
#elif (CAMERA_H == 240 )
{VOutSize     ,0x78},
#else

#endif 

{EXHCH        ,0x00},
{GAM1         ,0x0c},
{GAM2         ,0x16},
{GAM3         ,0x2a},
{GAM4         ,0x4e},
{GAM5         ,0x61},
{GAM6         ,0x6f},
{GAM7         ,0x7b},
{GAM8         ,0x86},
{GAM9         ,0x8e},
{GAM10        ,0x97},
{GAM11        ,0xa4},
{GAM12        ,0xaf},
{GAM13        ,0xc5},
{GAM14        ,0xd7},
{GAM15        ,0xe8},
{SLOP         ,0x20},
{LC_RADI      ,0x00},
{LC_COEF      ,0x13},
{LC_XC        ,0x08},
{LC_COEFB     ,0x14},
{LC_COEFR     ,0x17},
{LC_CTR       ,0x05},
{BDBase       ,0x99},
{BDMStep      ,0x03},
{SDE          ,0x04},
{BRIGHT       ,0x00},                              
{CNST         ,30},//�ڰ�ͼ����ֵ 150:¥��¥�¶����ܣ���һ�����ȣ�70
{SIGN         ,0x06},
{UVADJ0       ,0x11},
{UVADJ1       ,0x02},
};

u8 cfgnum = sizeof(ov7727_reg)/sizeof(ov7727_reg[0]);   /*�ṹ�������Ա��Ŀ*/



/************************************************
* ��������Ov7725_Init
* ����  ��Sensor��ʼ��
* ����  ����
* ���  ������1�ɹ�������0ʧ��
* ע��  ����
************************************************/
u8 Ov7725_Init()
{
    while(Ov7725_reg_Init() == 0);
    Ov7725_exti_Init();
    return 0;
}

/************************************************
* ��������Ov7725_reg_Init
* ����  ��Sensor �Ĵ��� ��ʼ��
* ����  ����
* ���  ������1�ɹ�������0ʧ��
* ע��  ����
************************************************/
u8 Ov7725_reg_Init(void)
{
    u16 i = 0;
    u8 Sensor_IDCode = 0;
    SCCB_GPIO_init();
    OV7725_Delay_ms(50);
    while( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) /*��λsensor */
    {
        i++;
        if(i == 20)
        {
            printf("����:SCCBд���ݴ���");
            //OV7725_Delay_ms(50);
            return 0 ;
        }
    }
    OV7725_Delay_ms(50);
    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 /* ��ȡsensor ID��*/
    {
        printf("����:��ȡIDʧ��");
        return 0;
    }
    printf("Get ID success��SENSOR ID is 0x%x", Sensor_IDCode);
    printf("Config Register Number is %d ", cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7727_reg[i].Address, ov7727_reg[i].Value) )
            {
                printf("����:д�Ĵ���0x%xʧ��", ov7727_reg[i].Address);
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    printf("OV7725 Register Config Success!");
    return 1;
}


