/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 11/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

/* Line options */
#define AFIO_LINE0                   0
#define AFIO_LINE1                   1
#define AFIO_LINE2                   2
#define AFIO_LINE3                   3
#define AFIO_LINE4                   4
#define AFIO_LINE5                   5
#define AFIO_LINE6                   6
#define AFIO_LINE7                   7
#define AFIO_LINE8                   8
#define AFIO_LINE9                   9
#define AFIO_LINE10                  10
#define AFIO_LINE11                  11
#define AFIO_LINE12                  12
#define AFIO_LINE13                  13
#define AFIO_LINE14                  14
#define AFIO_LINE15                  15

/* Port Options */
#define AFIO_PortA                 0
#define AFIO_PortB                 1
#define AFIO_PortC                 2

void MAFIO_voidEXTIConfiguration(u8 Copy_u8EXTIn , u8 Copy_u8Port);
void MAFIO_voidCAN1Remapping(void);

#endif
