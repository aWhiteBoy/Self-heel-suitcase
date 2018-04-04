
#include "include.h"
#include  "PIT_own.h"     //�����жϼ�ʱ��


/*! 
 *  @brief      PITn��ʱ
 *  @param      PITn        ģ��ţ�PIT0~PIT3��
 *  @param      cnt         ��ʱʱ��(��λΪbusʱ������)
 *  @since      v5.0      
 *  Sample usage:       
                    pit_delay(PIT0, 1000);                         //��ʱ 1000 ��busʱ��
 */
void pit_delay(PITn pitn, uint32 cnt)
{
    //PIT �õ��� Bus Clock ����Ƶ��
    //������� = ����Ƶ�� * ʱ��
  
    ASSERT( cnt > 0 );              //�ö��Լ�� ʱ����벻��Ϊ 0
    
    SIM_SCGC6       |= SIM_SCGC6_PIT_MASK;                          //ʹ��PITʱ��

    PIT_MCR         &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );    //ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������
    
    PIT_TCTRL(pitn) &= ~( PIT_TCTRL_TEN_MASK );                     //����PIT ���Ա����ü���ֵ��Ч
    
    PIT_LDVAL(pitn)  = cnt - 1;                                     //��������ж�ʱ��
    
    PIT_Flag_Clear(pitn);                                           //���жϱ�־λ

    PIT_TCTRL(pitn) &= ~ PIT_TCTRL_TEN_MASK;                        //��ֹPITn��ʱ����������ռ���ֵ��
    PIT_TCTRL(pitn)  = ( 0
                        | PIT_TCTRL_TEN_MASK                        //ʹ�� PITn��ʱ��
                        //| PIT_TCTRL_TIE_MASK                      //��PITn�ж�
                        ); 
    
    while( !(PIT_TFLG(pitn)& PIT_TFLG_TIF_MASK));
    
    PIT_Flag_Clear(pitn);                                           //���жϱ�־λ
}

/*! 
 *  @brief      PITn��ʱ��ʼ
 *  @param      PITn        ģ��ţ�PIT0~PIT3��
 *  @since      v5.0      
 *  Sample usage:       
                    pit_time_start(PIT0);                          //PIT0��ʱ��ʼ
 */
void pit_time_start(PITn pitn)
{
    //PIT �õ��� Bus Clock ����Ƶ��
    //������� = ����Ƶ�� * ʱ��
      
    SIM_SCGC6       |= SIM_SCGC6_PIT_MASK;                          //ʹ��PITʱ��

    PIT_MCR         &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );    //ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������
    
    PIT_TCTRL(pitn) &= ~( PIT_TCTRL_TEN_MASK );                     //����PIT ���Ա����ü���ֵ��Ч
    
    PIT_LDVAL(pitn)  = ~0;                                          //��������ж�ʱ��

    PIT_Flag_Clear(pitn);                                           //���жϱ�־λ

    PIT_TCTRL(pitn) &= ~ PIT_TCTRL_TEN_MASK;                        //��ֹPITn��ʱ����������ռ���ֵ��
    PIT_TCTRL(pitn)  = ( 0
                        | PIT_TCTRL_TEN_MASK                        //ʹ�� PITn��ʱ��
                        //| PIT_TCTRL_TIE_MASK                      //��PITn�ж�
                        ); 
}

/*! 
 *  @brief      ��ȡ PITn��ʱʱ�䣬���ر�PIT��ʱ
 *  @param      PITn        ģ��ţ�PIT0~PIT3��
 *  @since      v5.0      
 *  Sample usage:       
                        pit_time_get(PIT0);                         //��ȡ PITn��ʱʱ�䣬���ر�PIT��ʱ
 */
uint32 pit_time_get(PITn pitn)
{
    uint32 val;
    
    val = (~0) - PIT_CVAL(pitn);
    
    if(PIT_TFLG(pitn)& PIT_TFLG_TIF_MASK)                           //�ж��Ƿ�ʱ�䳬ʱ
    {
        PIT_Flag_Clear(pitn);                                       //���жϱ�־λ
        PIT_TCTRL(pitn) &= ~ PIT_TCTRL_TEN_MASK;                    //��ֹPITn��ʱ����������ռ���ֵ��
        return ~0;
    }
    
    if(val == (~0))
    {
        val--;              //ȷ�� ������ ~0
    }
    PIT_TCTRL(pitn) &= ~ PIT_TCTRL_TEN_MASK;                        //��ֹPITn��ʱ����������ռ���ֵ��
    return val;
}
