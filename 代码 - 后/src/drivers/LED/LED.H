#ifndef __LED_H__
#define __LED_H__

#include "common.h"
#include "gpio.h"

//配置开发板的LED硬件
#define   LED_PORT      PORTD     //LED所在的端口
typedef enum LEDn
{
  LED1    =      3,               //对应的引脚号
  LED2    =      4,
  LED3    =      5,
  LED4    =      6,
}LEDn;

//LED亮灭状态宏定义
typedef enum LED_status
{
  LED_ON  =   0,         //灯亮(对应低电平)
  LED_OFF =   1           //灯暗(对应高电平)
}LED_status;

void    LED_init(void);                                                 // LED初始化    函数
#define LED_INIT()             gpio_init(LED_PORT,LED1,GPO,LED_OFF);\
                               gpio_init(LED_PORT,LED2,GPO,LED_OFF);\
                               gpio_init(LED_PORT,LED3,GPO,LED_OFF);\
                               gpio_init(LED_PORT,LED4,GPO,LED_OFF)       // LED初始化    宏定义   效率高

void    LED_turn(LEDn);
#define LED_TURN(LEDn)         gpio_turn(LED_PORT,LEDn)                   // LED反转
#define LED(LEDn,LED_status)   GPIO_SET_1bit(LED_PORT,LEDn,LED_status)    // LED亮灭
void    led(LEDn,LED_status);                                             // LED亮灭
void    water_lights(void);                                               // 流水灯
void    LED_test(void);                                                   // LED测试，闪烁LED0(死循环)

//定义延时,方便流水灯的延时
#include "delay.h"
#define   LED_DELAY           delay()
#define   LED_DELAY_MS(x)     delayms(x)

#endif  //__LED_H__