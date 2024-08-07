/*************************************************************************/
/*       Auther: Ahmed Samir       */
/*       version: V01              */
/*       Date: 5/11/2022           */

#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

/* Prescaler Value from 0 to 65535
 -The counter clock frequency (CK_CNT) is equal to fCK_PSC / (PSC[15:0] + 1).
*/
#define TIM_PSC          0

/* Center-aligned mode selection */
#define TIM_CMS          0b00    // Edge-aligned mode

/* Direction of counting
 -0: Counter used as upcounter
 -1: Counter used as downcounter
  */
#define TIM_DIR          0

/* Update Interrupt Enable
 -0: Update interrupt disabled
 -1: Update interrupt enabled
 */
#define TIM_UIE          1



#endif
