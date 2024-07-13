/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 11/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_config.h"
#include "AFIO_private.h"

void MAFIO_voidEXTIConfiguration(u8 Copy_u8EXTIn , u8 Copy_u8Port)
{
	if(Copy_u8EXTIn <= 3)
	{
		AFIO->EXTICR[0] &= ~ (0b1111 << (Copy_u8EXTIn * 4));
		AFIO->EXTICR[0] |= (Copy_u8Port << (Copy_u8EXTIn * 4));
	}
	else if(Copy_u8EXTIn <= 7)
	{
		AFIO->EXTICR[1] &= ~ (0b1111 << ((Copy_u8EXTIn-4) * 4));
		AFIO->EXTICR[1] |= (Copy_u8Port << ((Copy_u8EXTIn-4) * 4));
	}
	else if(Copy_u8EXTIn <= 11)
	{
		AFIO->EXTICR[2] &= ~ (0b1111 << ((Copy_u8EXTIn-8) * 4));
		AFIO->EXTICR[2] |= (Copy_u8Port << ((Copy_u8EXTIn-8) * 4));
	}
	else if(Copy_u8EXTIn <= 15)
	{
		AFIO->EXTICR[3] &= ~ (0b1111 << ((Copy_u8EXTIn-12) * 4));
		AFIO->EXTICR[3] |= (Copy_u8Port << ((Copy_u8EXTIn-12) * 4));
	}
}

void MAFIO_voidCAN1Remapping(void)
{
	AFIO->MAPR &= ~(0b11 << 13);
	AFIO->MAPR |= (CAN_REMAP << 13);
}
