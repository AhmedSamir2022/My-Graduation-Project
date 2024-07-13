/*************************************************************************/
/*       Auther: Ahmed Samir       */
/*       version: V01              */
/*       Date: 2/9/2022            */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

u8 flag = 0;
/* Global Pointer to function */
void (*CallBack)(void);

void MSTK_voidInit(void)
{
        /* Disable Systick */
        STK->CTRL &= ~ (1 << 0);
        /* Disable Systick Interrupt */
        STK->CTRL &= ~ (1 << 1);
        /* Select STK clock from configuration file */
        STK->CTRL &= ~ (1 << 2);
        STK->CTRL |= ((STK_CLOCK) << 2);
}

void MSTK_voidSetBusyWait(u32 Copy_u8Ticks)
{
    /* Reset Timer value */
    STK->VAL = 0 ;
    /* load ticks to load register */
    STK->LOAD = Copy_u8Ticks;
    /* Enable STK_COUNTER */
    STK->CTRL |= (1 << 0);
    /* processor wait to flag be 1 */
    while(!(((STK->CTRL) >> 16) & 1));
    /* Stop the Timer */
    STK->CTRL &= ~(1 << 0);
    STK->VAL = 0;
    STK->LOAD =0;
}

void MSTK_voidSetBusyWaitSeconds(u8 Copy_u8Seconds)
{
	u8 Local_count = 0;
	for(Local_count=0;Local_count < (Copy_u8Seconds*3);Local_count++)
	{
	    /* Reset Timer value */
	    STK->VAL = 0 ;
	    /* load ticks to load register */
	    STK->LOAD = 3000000;
	    /* Enable STK_COUNTER */
	    STK->CTRL |= (1 << 0);
	    /* processor wait to flag be 1 */
	    while(!(((STK->CTRL) >> 16) & 1));
	    /* Stop the Timer */
	    STK->CTRL &= ~(1 << 0);
	    STK->VAL = 0;
	    STK->LOAD =0;

	}
}

void MSTK_voidSetIntervalSingle(u32 Copy_u8Ticks , void (*Copy_ptr)(void) )
{
    /* Disable Timer */
    STK->CTRL &= ~ (1 << 0);
    /* Reset Timer value */
    STK->VAL = 0 ;
    /* load ticks to load register */
    STK->LOAD = Copy_u8Ticks;
    /* Enable STK_COUNTER */
    STK->CTRL |= (1 << 0);
    /* Enable STK interrupt */
    STK->CTRL |= (1 << 1);

    flag = 1;
    CallBack = Copy_ptr;

}

void MSTK_voidSetIntervalPeriodic(u32 Copy_u8Ticks , void (*Copy_ptr)(void) )
{
    /* Reset Timer value */
    STK->VAL = 0 ;
    /* load ticks to load register */
    STK->LOAD = Copy_u8Ticks-1;
    /* Enable STK_COUNTER */
    STK->CTRL |= (1 << 0);
    /* Enable STK interrupt */
    STK->CTRL |= (1 << 1);

    flag = 2;
    CallBack = Copy_ptr;

}

/* ISR */
void SysTick_Handler(void)
{
        if(flag == 1)
        {
                STK->LOAD = 0;
                STK->VAL = 0;
        }

        CallBack();
}

void MSTK_voidStopTimer(void)
{
        /* Disable Systick */
        STK->CTRL &= ~ (1 << 0);
        /* Disable Systick Interrupt */
        STK->CTRL &= ~ (1 << 1);

        STK->LOAD = 0;
        STK->VAL = 0;
}

u32 MSTK_u32GetElapsedTime(void)
{
	return (STK->LOAD - STK->VAL);
}

u32 MSTK_u32GetRemainingTime(void)
{
    return (STK->VAL);
}


void STK_voidDelay_ms (uint32 Copy_u32Ticks)
{
	/* convert from ms to us as
	 * 1 ms = 1000 us for 8MHz
	 * 1 ms = 9000 us for 72MHz */
	Copy_u32Ticks *= 9000;
	MSTK_voidSetBusyWait(Copy_u32Ticks);
}
