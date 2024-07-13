/* Auther: AHMED SAMIR */
/* Date: 27/9/2022 */
/* Version: V02 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char          u8 ;
typedef unsigned short int     u16 ;
typedef unsigned long int      u32 ;

typedef signed char          s8 ;
typedef signed short int     s16 ;
typedef signed long int      s32 ;

typedef unsigned char                   uint8 ;
typedef unsigned short                  uint16;
typedef unsigned long                   uint32;
typedef unsigned long long 				 uint64;

typedef signed char             sint8 ;
typedef signed short                    sint16;
typedef signed long                     sint32;
typedef signed long long        sint64;

typedef float                                                   float32;
typedef double                                                  float64;

#define NULL                   (void*)0

/* for compiler use weak in can driver*/

#ifndef   __weak
  #define __weak                                   __attribute__((weak))
#endif



#endif
