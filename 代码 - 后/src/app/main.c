#include "include.h"

//陀螺仪加速度计
struct CarThreeNum  Acc_ADC_Data={0,0,0},Acc_ADC={0,0,0},Acc_Offset={0,0,0};
struct CarThreeNum  Gyro_dps={0,0,0},Gyro_ADC={0,0,0},Gyro_Offset={0,0,0};
struct CarFourNum  Q={1,0,0,0};
struct CarThreeNum      Gravity={0,0,0};

struct CarAngle Angle={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,{0},{0},{0},0,0,0,0,0,0,0};
struct CarSpeed         Speed = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
struct CarDirection     Direction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,{1,1,1,0},0,0,0};
struct CarInductor      Inductor ={{0,0},{0},0,0};
float all_PWM_R,all_PWM_L;
float speed_Delta,His_speed_Delta;
int Time_1ms;
int test1,test2,test3;

extern unsigned char Image_fire[CAMERA_H+1][CAMERA_DMA_NUM];

void SCI_Send_Datas(UARTn uratn);
void SCI_Send_fireImage(UARTn uratn);
extern u8 Image_Flag;

int middle_test;
extern int test_gro;

int stop_flag;//用于紧急停车

void main()
{
  DisableInterrupts;
  delayms(100);
  All_init();
  delayms(100);
  /*****摄像头开始采集，因为初始化的时候关闭了摄像头****/
  img_flag = IMG_START;		       //开始采集图像
  PORTC_ISFR=~0;			//写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
  enable_irq(89); 			//允许PTC的中断
  test1=100;
  EnableInterrupts;
  
  while(1)
  {
    //SCI_Send_Datas(UART3);
    Send_Image_to_LCD(Image_fire);
    Draw_single_line('L',last_center,Red);
    //Draw_single_line('H',test1,Red);
    //LED3_ON;
  }
}

extern int halfwid;

  void SCI_Send_Datas(UARTn uratn)
{
  static unsigned short int send_data[3][4] = { { 0 }, { 0 }, { 0 } };
  short int checksum=0;
  unsigned char xorsum=0,high,low;
  
  send_data[0][0] = (unsigned short int)(Direction.Gyro);
  //	send_data[0][1] = (unsigned short int)(0);
  //	send_data[0][2] = (unsigned short int)(0);
  //	send_data[0][3] = (unsigned short int)(0);
  
  //	send_data[1][0] = (unsigned short int)(0);
  send_data[1][1] = (unsigned short int)(1);
  //	send_data[1][2] = (unsigned short int)(0);
  //	send_data[1][3] = (unsigned short int)(0);
  
  //	send_data[2][0] = (unsigned short int)(0);
  //	send_data[2][1] = (unsigned short int)(0);
  send_data[2][2] = (unsigned short int)(0);
  send_data[2][3] = (unsigned short int)(0);
  
  uart_putchar(uratn, 'S');
  uart_putchar(uratn, 'T');
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 4; j++)
    {
      low=(unsigned char)(send_data[i][j] & 0x00ff);
      high=(unsigned char)(send_data[i][j] >> 8u);
      uart_putchar(uratn,low ); uart_putchar(uratn, high);
      checksum+=low; checksum+=high;
      xorsum^=low; xorsum^= high;
    }
  uart_putchar(uratn, (unsigned char)(checksum & 0x00ff));
  uart_putchar(uratn,xorsum);
}     
     


void SCI_Send_fireImage(UARTn uratn)
{
  int H = 240, L = 320;
  //send "CAMERA"
  uart_putchar(uratn, 'C');
  uart_putchar(uratn, 'A');
  uart_putchar(uratn, 'M');
  uart_putchar(uratn, 'E');
  uart_putchar(uratn, 'R');
  uart_putchar(uratn, 'A');
  uart_putchar(uratn, (unsigned char)(H >> 8));//send Hang
  uart_putchar(uratn, (unsigned char)(H & 0x00FF));
  uart_putchar(uratn, (unsigned char)(L >> 8));//send Lie
  uart_putchar(uratn, (unsigned char)(L & 0x00FF));
  //send all data
  for (int i = 0; i < H; i++)
    for (int j = 0; j < L / 8; j++)
      uart_putchar(uratn, Image_fire[i][j]);
}     
