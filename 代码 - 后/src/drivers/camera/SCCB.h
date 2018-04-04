#ifndef __SCCB_H
#define __SCCB_H


#define SCL_H()         PTB22_OUT = 1
#define SCL_L()         PTB22_OUT = 0
#define	SCL_DDR_OUT() 	DDRB22 = 1
#define	SCL_DDR_IN() 	DDRB22 = 0

#define SDA_H()         PTB18_OUT = 1
#define SDA_L()         PTB18_OUT = 0
#define SDA_IN()      	PTB18_IN
#define SDA_DDR_OUT()	DDRB18 = 1
#define SDA_DDR_IN()	DDRB18 = 0

#define ADDR_OV7725   0x42

#define SCCB_DELAY()	SCCB_delay(100)	


void SCCB_GPIO_init(void);
int SCCB_WriteByte( u16 WriteAddress , u8 SendByte);
int SCCB_ReadByte(u8* pBuffer,   u16 length,   u8 ReadAddress);
static void SCCB_delay(u16 i);


#endif 
