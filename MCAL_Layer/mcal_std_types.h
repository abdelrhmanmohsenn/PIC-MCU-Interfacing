/* 
 * File:   mcal_std_types.h
 * Author: mohsen
 *
 * Created on January 28, 2023, 12:02 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/******* section : Includes *******/
#include "xc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/******* section : macros Declarations *******/
#define STD_HIGH      0x00
#define STD_LOW       0x01

#define STD_ON        0x01
#define STD_OFF       0x00

#define STD_ACTIVE    0x01
#define STD_IDLE      0x00

#define E_OK          (Std_ReturnType)0x00
#define E_NOT_OK      (Std_ReturnType)0x01

#define PIN_MAX_NUMBER   8
#define PORT_MAX_NUMBER  5

/******* section : function-like macros Declarations *******/


/******* section : Data Types Declarations *******/
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef signed   char      sint8;
typedef signed   short     sint16;
typedef signed   int       sint32;

typedef uint8    Std_ReturnType;


/******* section : Function Declarations *******/



#endif	/* MCAL_STD_TYPES_H */

