#ifndef __ISR_H
#define __ISR_H

#include "common.h"
#include "include.h"
#include "define.h"

#undef  VECTOR_084
#define VECTOR_084    PIT0_IRQHandler

#undef  VECTOR_067
#define VECTOR_067    USART3_IRQHandler

#undef  VECTOR_105
#define VECTOR_105    PORTC_IRQHandler

#undef  VECTOR_016
#define VECTOR_016    DMA0_IRQHandler



void PIT0_IRQHandler(void);
void USART3_IRQHandler(void);

void PORTC_IRQHandler();
void DMA0_IRQHandler();
#endif /*__ISC_H*/