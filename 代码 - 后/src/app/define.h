#ifndef __DEFINE_H
#define __DEFINE_H

#define DIR_L PTE24_OUT
#define DIR_R PTE25_OUT
#define DIR_L_Forward  DIR_L=1
#define DIR_L_Backward DIR_L=0
#define DIR_R_Forward  DIR_R=1
#define DIR_R_Backward DIR_R=0

#define Measure_DirL PTA9_IN
#define Measure_DirR PTA11_IN

#define buzzer PTE6_OUT

#define LED1_ON PTD3_OUT=0
#define LED2_ON PTD4_OUT=0
#define LED3_ON PTD5_OUT=0
#define LED4_ON PTD6_OUT=0
#define LED1_OFF PTD3_OUT=1
#define LED2_OFF PTD4_OUT=1
#define LED3_OFF PTD5_OUT=1
#define LED4_OFF PTD6_OUT=1

#define sw1 PTB0_IN
#define sw2 PTB1_IN
#define sw3 PTB2_IN
#define sw4 PTB3_IN
#define sw5 PTB4_IN
#define sw6 PTB5_IN
#define sw7 PTB6_IN
#define sw8 PTB7_IN

//************************************��Ҫ���ݶ���****************************//

//ͼ��
#define Process_Hang    240
#define Lie             320
#define ImageCentre     160
#define WHITE           0
#define BLACK           1

#define StartLine_StartTime 2000

#define left_max      10
#define right_max     310

struct CarSpeed
{
    //��λ
    unsigned char Mode;
    //�ٶȲ��֣���������ٶ�
    int L_5ms;
    int R_5ms;
    int L_100ms;
    int R_100ms;
    float Car;
    float Goal;
    float Goal_init;
    //�ٶȲ��֣�pid����
    float Right_I_Error_Start;
    float P;              	//�ٶȿ���P����
    float I;              	//�ٶȿ���I����
    float D;              	//�ٶȿ���D����
    float PWM_Per;  		//�ٶ�ÿ������ֵ
    long double I_Error_Start;
    long double I_Limit_PWM_max;
    long double I_Limit_PWM_min;
    float PWM_Per_Limit;
    float PWM_Integral;	//�ٶȸ���PWM��ֵ���洢�Ļ���
    float PWM;        	//�ٶȸ���PWM��ֵ    	
    float PWM_MAX;
    float PWM_MIN;
    long int Distance;
};

struct CarDirection
{
    //����������ҽǶ�//7.18��������ӣ�ʵ��
    float m_angle;
    float G_angle;
    float speed;
    //���������ǵ�ֵ
    float Gyro;
    float centre_P;
    float cross_P;
    long int Right_distance;
    int RADelayTime1,RADelayTime2;
    float Delta;
    float PINIT;
    //pid����
    float P_init;//*****************dir����P��ʼ������****************
    float P;  	 //*****************dir����P����**********************
    float D;	 //*****************dir����D����**********************	
    float DD;
    float PWM_Per;  		//����ÿ������ֵ
    float PWM;
    unsigned char numb;
    unsigned char output_enable;
    unsigned char Weights[4];
    float PWM_MAX;
    float PWM_MIN;
    int runCcdID;
    
    
};

struct CarInductor  
{
  int data[2];
  int His_data[3];
  int get_error;   
  int His_error;
};

struct CarThreeNum
{
    float x;
    float y;
    float z;    
};
struct CarAngle 
{
    float roll;   //����
    float pitch;  //ƫ��
    float yaw;    
    float rotation;  //
    float vertical;
    
    float error;
    float Now;
    float Goal;
    float Gyro;
    float speed;
    //����ĽǶȣ�m_angleΪmma845x��õĽǶȣ�G_angleΪ�����ǻ��ֳ����ĽǶ�
    float m_angle;
    float G_angle;
    float OFFSET;//OFFSET_angleΪ��ֹʱ�ĽǶ�important    				
    
    int set;//��������
    int set_angle;
    int radius;
    float Rad[21];
    float angle_x[21];
    float angle_y[21];
    
    
    float P;              //�ٶȿ���P����
    float I;              //�ٶȿ���I����
    float D;              //�ٶȿ���I����
    float PWM;
    float Pwm_P;
    float Pwm_I;
    float Pwm_D;
};
struct CarFourNum
{
    float q1;
    float q2;
    float q3;
    float q4;    
};

extern struct CarThreeNum  Acc_ADC_Data,Acc_ADC,Acc_Offset;   //���ٶ�ֵ    
extern struct CarAngle Angle;
extern struct CarThreeNum  Gyro_dps,Gyro_ADC,Gyro_Offset;   //������
extern struct CarFourNum  Q;
extern struct CarThreeNum Gravity;

extern struct CarSpeed          Speed;
extern struct CarDirection      Direction;
extern struct CarInductor       Inductor;
extern float all_PWM_R,all_PWM_L;
extern float speed_Delta,His_speed_Delta;
extern int Time_1ms;
extern int test1,test2,test3;
extern int stop_flag;

extern float Tmp_Speed_P;
extern int middle_test;//����Ӻ�����ȡ����������ֵ

extern int last_center;
extern int cal[5];
extern int last_err;
extern int now_err;
extern int servo_OUT;
extern float Di_Pservo[2],Di_Dservo[2];//���P,D
extern int Servo_output;

#endif /*__DEFINE_H*/
