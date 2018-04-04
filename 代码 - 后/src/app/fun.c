#include "include.h"

void road_display(void)
{
  cal[0]=160-last_center;//舵机误差值
}

float P_servo,D_servo;
void servo_PID(void)//舵机PID
{
  static int D_var=0;
  now_err=cal[0];
  P_servo=Di_Pservo[0];
  D_servo=Di_Dservo[0];
  D_var=(int)((now_err-last_err)*D_servo);
  servo_OUT =(int)(now_err * P_servo + D_var); 
  
  last_err=now_err;//保留上个误差
  
  Servo_output = (int)(-servo_OUT+1200);
  if(Servo_output<=800)//输出限幅
    Servo_output = 800;
  else if(Servo_output>= 2000)
    Servo_output = 2000;
}

void get_target()
{
     int i=0;
     while(!(get_rowcenter(Image_fire[i])!=0
              &&get_rowcenter(Image_fire[i+1])!=0
              &&get_rowcenter(Image_fire[i+2])!=0
              &&get_rowcenter(Image_fire[i+3])!=0)
              &&i<237)
     i++;
     if(i>=237)
     {
        last_center=160;
     }
     else
     {
        last_center=get_rowcenter(Image_fire[i]);
     }
}

unsigned char ImageData_row[320]={0};  //赛道解压后的记录值
int get_rowcenter(unsigned char *ImageData_in)
{
  int BtoW_flag=0,WtoB_flag=0,cursor=0;
  
  for(int i=0;i<40;i++)
    for(int k=0;k<8;k++)
      ImageData_row[i*8+k] = (ImageData_in[i]>>(7-k))&0x01;
  
  cursor=0;
  if(ImageData_row[cursor+2]==WHITE
     && ImageData_row[cursor+1]==WHITE
     && ImageData_row[cursor]==WHITE)
  {
     BtoW_flag=cursor;
  }
  else
  {
     while(!(ImageData_row[cursor+3]==WHITE
              &&ImageData_row[cursor+2]==WHITE
              &&ImageData_row[cursor+1]==BLACK
              &&ImageData_row[cursor]==BLACK)
              &&cursor<320)
     cursor++;
     BtoW_flag=min(cursor+2,320);
  }
  if(BtoW_flag==320)
  {
     return 0;
  }
  
  cursor=BtoW_flag;
  while(!(ImageData_row[cursor+3]==BLACK
         &&ImageData_row[cursor+2]==BLACK
         &&ImageData_row[cursor+1]==WHITE
         &&ImageData_row[cursor]==WHITE)
         &&cursor<320)
  cursor++;
  WtoB_flag=min(cursor+2,320);
  
  return (int)(WtoB_flag+BtoW_flag)/2;
}

int max(int x,int y)
{
   return x>y?x:y;
}

int min(int x,int y)
{
    return x<y?x:y;
}

int abs(int x)
{
    return x>0?x:-x;
}








