/*************************************************************************/
/*       Auther: Ahmed Samir       */
/*       version: V01              */
/*       Date: 5/11/2022            */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"


void MTIM_voidInit(void)
{
		TIMER2->PSC = TIM_PSC;

		TIMER2->CR1 &= ~(0b11 << 5);
		TIMER2->CR1 |= (TIM_CMS << 5);

		TIMER2->CR1 &= ~(1 << 4);
		TIMER2->CR1 |= (TIM_DIR << 4);

		TIMER2->DIER &= ~(1 << 0);
		TIMER2->DIER |= (TIM_UIE << 0);

		/* the prescaler is clocked directly by the internal
	clock */
		TIMER2->SMCR &= ~((0b111 << 0));

}

void MTIM_voidPWMUPCh1(u32 Copy_u32CRRValue)
{
		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CR1 |= (1 << 7);

		/* CC1 channel is configured as output */
		TIMER2->CCMR1 &= ~((0b11) << 0);

		/*  OC1 active high */
		TIMER2->CCER &= ~(1 << 1);

		/*  PWM mode 1  */
		TIMER2->CCMR1 &= ~((0b111) << 4);
		TIMER2->CCMR1 |= ((0b110) << 4);

		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CCMR1 |= (1 << 3);

		/* Write CCxE = 1 to enable the output on channel 1 */
		TIMER2->CCER |= (1 << 0);

		TIMER2->ARR = 60000;
		TIMER2->CCR[0] = Copy_u32CRRValue;

		/* before starting the counter, the user has to initialize all the registers by setting the
	UG bit in the TIMx_EGR register */
		TIMER2->EGR |= (1 << 0);

		/* Enable Counter */
		TIMER2->CR1 |= (1 << 0);

}

void MTIM_voidPWMUPCh2(u32 Copy_u32CRRValue)
{
		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CR1 |= (1 << 7);

		/* CC2 channel is configured as output */
		TIMER2->CCMR1 &= ~((0b11) << 8);

		/*  OC2 active high */
		TIMER2->CCER &= ~(1 << 5);

		/*  PWM mode 1  */
		TIMER2->CCMR1 &= ~((0b111) << 12);
		TIMER2->CCMR1 |= ((0b110) << 12);

		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CCMR1 |= (1 << 11);

		/* Write CCxE = 1 to enable the output on channel 2*/
		TIMER2->CCER |= (1 << 4);

		TIMER2->ARR = 60000;
		TIMER2->CCR[1] = Copy_u32CRRValue;

		/* before starting the counter, the user has to initialize all the registers by setting the
	UG bit in the TIMx_EGR register */
		TIMER2->EGR |= (1 << 0);

		/* Enable Counter */
		TIMER2->CR1 |= (1 << 0);

}

void MTIM_voidPWMUPCh3(u32 Copy_u32CRRValue)
{
		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CR1 |= (1 << 7);

		/* CC3 channel is configured as output */
		TIMER2->CCMR2 &= ~((0b11) << 0);

		/*  OC3 active high */
		TIMER2->CCER &= ~(1 << 9);

		/*  PWM mode 1  */
		TIMER2->CCMR2 &= ~((0b111) << 4);
		TIMER2->CCMR2 |= ((0b110) << 4);

		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CCMR2 |= (1 << 3);

		/* Write CCxE = 1 to enable the output on channel 3 */
		TIMER2->CCER |= (1 << 8);

		TIMER2->ARR = 60000;
		TIMER2->CCR[2] = Copy_u32CRRValue;

		/* before starting the counter, the user has to initialize all the registers by setting the
	UG bit in the TIMx_EGR register */
		TIMER2->EGR |= (1 << 0);

		/* Enable Counter */
		TIMER2->CR1 |= (1 << 0);

}

void MTIM_voidPWMUPCh4(u32 Copy_u32CRRValue)
{
		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CR1 |= (1 << 7);

		/* CC1 channel is configured as output */
		TIMER2->CCMR2 &= ~((0b11) << 8);

		/*  OC4 active high */
		TIMER2->CCER &= ~(1 << 13);

		/*  PWM mode 1  */
		TIMER2->CCMR2 &= ~((0b111) << 12);
		TIMER2->CCMR2 |= ((0b110) << 12);

		/* Preload register on TIMx_CCR1 enabled */
		TIMER2->CCMR1 |= (1 << 11);

		/* Write CCxE = 1 to enable the output on channel 4 */
		TIMER2->CCER |= (1 << 12);

		TIMER2->ARR = 60000;
		TIMER2->CCR[3] = Copy_u32CRRValue;

		/* before starting the counter, the user has to initialize all the registers by setting the
	UG bit in the TIMx_EGR register */
		TIMER2->EGR |= (1 << 0);

		/* Enable Counter */
		TIMER2->CR1 |= (1 << 0);

}
