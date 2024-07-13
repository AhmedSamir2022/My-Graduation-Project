/*************************************************************************/
/*       Auther: Ahmed Samir       */
/*       version: V01              */
/*       Date: 2/9/2022            */

#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

#define STK_BASE_ADDRESS        (u32)0xE000E010

typedef struct
{
        volatile u32 CTRL;
        volatile u32 LOAD;
        volatile u32 VAL;
        volatile u32 CALIB;

}STK_MemoryMap;

#define STK          ((volatile STK_MemoryMap*)STK_BASE_ADDRESS)

#endif
