/*************************************************************************/
/*       Auther: Ahmed Samir       */
/*       version: V01              */
/*       Date: 5/11/2022           */

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

/* Timers options */
#define TIMER_2         0
#define TIMER_3         1


void MTIM_voidInit(void);

void MTIM_voidPWMUPCh1(u32 Copy_u32CRRValue);
void MTIM_voidPWMUPCh2(u32 Copy_u32CRRValue);
void MTIM_voidPWMUPCh3(u32 Copy_u32CRRValue);
void MTIM_voidPWMUPCh4(u32 Copy_u32CRRValue);

#endif
