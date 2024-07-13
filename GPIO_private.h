/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 6/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#define GPIOA_BASE_ADDRESS              (u32)0x40010800
#define GPIOB_BASE_ADDRESS              (u32)0x40010C00
#define GPIOC_BASE_ADDRESS              (u32)0x40011000

typedef struct
{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;

}GPIO_t;

#define GPIOA                    ((volatile GPIO_t*)GPIOA_BASE_ADDRESS)
#define GPIOB                    ((volatile GPIO_t*)GPIOB_BASE_ADDRESS)
#define GPIOC                    ((volatile GPIO_t*)GPIOC_BASE_ADDRESS)

#endif
