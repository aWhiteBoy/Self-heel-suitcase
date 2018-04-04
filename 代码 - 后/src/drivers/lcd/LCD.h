#ifndef _LCD_H
#define _LCD_H


//��ɫ
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


//�������Ӷ���//SDO���ſ��Բ�����
#define  cs 	 PTE26_OUT       //Ƭѡ
#define  reset   PTE27_OUT       //��λ
#define  dcx     PTE28_OUT      //��ַ/�����л�
#define  sdi     PTE25_OUT      // SDI  MOSI
#define  scl     PTE24_OUT      //ʱ��


//λ��
#define GET_BITFIELD(addr) (volatile bit_field *)(&addr)//���ص���ָ��
typedef struct bit_S
{
	unsigned char bit0:1;
	unsigned char bit1:1;
	unsigned char bit2:1;
	unsigned char bit3:1;
	unsigned char bit4:1;
	unsigned char bit5:1;
	unsigned char bit6:1;
	unsigned char bit7:1;
}bit_field;



//Ӳ���ײ�
void LCD_PORT_init();
void LCD_Reset();
void LCD_init(unsigned char direction);

void write_command(unsigned char c);
void write_data(unsigned char  d); 
void write_word(unsigned int dat);

void RamAdressSet();
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);


//д����
void Send_Image_to_LCD(unsigned char img[CAMERA_H][CAMERA_DMA_NUM]);

void LCD_PutChar(unsigned int x, unsigned int y,unsigned char c, unsigned int fColor, unsigned int bColor);
void LCD_PutString(unsigned int x, unsigned int y, unsigned char *s, unsigned int fColor, unsigned int bColor);
void LCD_PutChar8x16(unsigned int x, unsigned int y,unsigned char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void PutGB3232(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void LCD_Put_Unsigned_Int(unsigned int x,unsigned int y,unsigned char s0[],unsigned int d,unsigned int fColor, unsigned int bColor);
void LCD_Put_Int(unsigned int x,unsigned int y,unsigned char s0[],int d,unsigned int fColor, unsigned int bColor);
void LCD_Put_Float(unsigned int x,unsigned int y,unsigned char s0[],float pnum,unsigned int fColor, unsigned int bColor);

void Disp_single_colour(unsigned int color);
void Draw_single_line(unsigned char axis,unsigned int line,unsigned int color);
void Print_child();
void Parameters_On_LCD();
void SCISendFloat(UARTn uratn,float f);
#endif