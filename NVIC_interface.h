/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 9/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/* Groub Sub Distribution */
#define NVIC_GROUP_4_SUB_0            0x5FA00300
#define NVIC_GROUP_3_SUB_1            0x5FA00400
#define NVIC_GROUP_2_SUB_2            0x5FA00500
#define NVIC_GROUP_1_SUB_3            0x5FA00600
#define NVIC_GROUP_0_SUB_4            0x5FA00700

void MNVIC_voidInit(void);

void MNVIC_EnableInterrupt(u8 Copy_u8InterruptID);
void MNVIC_DisableInterrupt(u8 Copy_u8InterruptID);

void MNVIC_SetPendingFlag(u8 Copy_u8InterruptID);
void MNVIC_ClearPendingFlag(u8 Copy_u8InterruptID);

u8 MNVIC_GetActiveFlag(u8 Copy_u8InterruptID);

void MNVIC_voidSetPriority(u8 Copy_u8InterruptID,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority,u32 Copy_u32GroubSubDistribution);

#endif
