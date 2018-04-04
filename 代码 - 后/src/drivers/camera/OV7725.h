#ifndef __OV7725_H
#define __OV7725_H 


#define OV7725_Delay_ms(time)  DELAY_MS(time)
#define OV7725_ID           0x21

#define	CAMERA_DMA_CH 	    DMA_CH0	//��������ͷ��DMA�ɼ�ͨ��
#define CAMERA_W            320         //��������ͷͼ����
#define CAMERA_H            240		//��������ͷͼ��߶�
#define CAMERA_INTERLACE    1           //����ͷ����ɼ����� n - 1,����1��ʾ�����вɼ���2��ʾ���вɼ�
#define CAMERA_DMA_NUM      (CAMERA_W /8 )    //DMA�ɼ�����
#define CAMERA_SIZE         (CAMERA_W * CAMERA_H /8)        //ͼ��ռ�ÿռ��С
#define CAMERA_DMA_LINE     (CAMERA_H/CAMERA_INTERLACE)     //ʵ�ʲɼ�����


extern unsigned char Image_fire[CAMERA_H+1][CAMERA_DMA_NUM];
extern volatile unsigned char img_flag;//ͼ��״̬


//����ͼ��ɼ�״̬
typedef enum 
{
    IMG_NOTINIT=0,
    IMG_FINISH,			        //ͼ��ɼ����
    IMG_FAIL,				//ͼ��ɼ�ʧ��(�ɼ���������)
    IMG_GATHER,				//ͼ��ɼ���
    IMG_START,				//��ʼ�ɼ�ͼ��
    IMG_STOP,				//��ֹͼ��ɼ�
    
}IMG_STATE;


typedef struct
{
    u8 Address;			       /*�Ĵ�����ַ*/
    u8 Value;		           /*�Ĵ���ֵ*/
}Register_Info;



unsigned char Ov7725_reg_Init(void);
extern unsigned char Ov7725_Init();
extern void Ov7725_exti_Init();
extern void ov7725_get_img();
extern int OV7725_ReadReg(u8 LCD_Reg,u16 LCD_RegValue);
extern int OV7725_WriteReg(u8 LCD_Reg,u16 LCD_RegValue);

extern unsigned char Image_fire[CAMERA_H+1][CAMERA_DMA_NUM];
#endif























