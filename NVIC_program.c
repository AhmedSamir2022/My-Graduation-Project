/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 9/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"

/* this function is a fucken mistake */
void MNVIC_voidInit(void)
{
#define SCB_AIRCR   *((volatile u32*)0xE000ED0C)

	SCB_AIRCR = NVIC_GROUP_SUB_DISTRIBUTION;
}

void MNVIC_EnableInterrupt(u8 Copy_u8InterruptID)
{
	NVIC->ISER[Copy_u8InterruptID/32] = 1 << Copy_u8InterruptID%32;
}

void MNVIC_DisableInterrupt(u8 Copy_u8InterruptID)
{
	NVIC->ICER[Copy_u8InterruptID/32] = 1 << Copy_u8InterruptID%32;
}

void MNVIC_SetPendingFlag(u8 Copy_u8InterruptID)
{
	NVIC->ISPR[Copy_u8InterruptID/32] = 1 << Copy_u8InterruptID%32;
}
void MNVIC_ClearPendingFlag(u8 Copy_u8InterruptID)
{
	NVIC->ICPR[Copy_u8InterruptID/32] = 1 << Copy_u8InterruptID%32;
}

u8 MNVIC_GetActiveFlag(u8 Copy_u8InterruptID)
{
	return GET_BIT( NVIC->IABR[Copy_u8InterruptID/32], Copy_u8InterruptID%32 );
}

void MNVIC_voidSetPriority(u8 Copy_u8InterruptID,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority,u32 Copy_u32GroubSubDistribution)
{

	if(Copy_u8InterruptID < 60)
	{
		u8 Local_u8Periority = Copy_u8SubPriority | (Copy_u8GroupPriority << ((Copy_u32GroubSubDistribution - 0xFA050300)/0x100));
		NVIC->IPR[Copy_u8InterruptID] = Local_u8Periority << 4;
	}
	else
	{
		//report error
	}
}
