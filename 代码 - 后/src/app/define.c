#include "define.h"

int last_center;
int cal[5]={0};//舵机的误差值
int last_err=0,now_err=0;
int servo_OUT=0;
float Di_Pservo[2]={4,0},Di_Dservo[2]={16,0};//舵机P,D
int Servo_output=0;
