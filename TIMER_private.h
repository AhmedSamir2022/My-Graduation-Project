/*************************************************************************/
/*       Auther: Ahmed Samir       */
/*       version: V01              */
/*       Date: 5/11/2022           */

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

#define TIMER2_BASE_ADDRESS              0x40000000
#define TIMER3_BASE_ADDRESS              0x40000400

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 Reserved1;
	volatile u32 CCR[4];
	volatile u32 Reserved2;
	volatile u32 DCR;
	volatile u32 DMAR;

}timer_t;

#define TIMER2            ((volatile timer_t*)TIMER2_BASE_ADDRESS)
#define TIMER3            ((volatile timer_t*)TIMER3_BASE_ADDRESS)


#endif
