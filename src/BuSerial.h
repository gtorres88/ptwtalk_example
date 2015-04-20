/************************************************************************//**
 *
 * \file BuSerial.h
 * 
 * \brief   This module describes a general interface for serial devices.
 *          Implementations of serial devices should provide Create and
 *          Destroy methods that return a pointer to a SerialDevice instance.
 * 
 * \note   
 *
 * \author Spencer Russell (Bulogics, Inc.)
 * \date 2011-05-12
 * 
 ****************************************************************************/

#ifndef _BUSERIAL_H
#define _BUSERIAL_H

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "types.h"

/****************************************************************************
 *                     EXPORTED TYPES and DEFINITIONS                       *
 ****************************************************************************/
typedef void (*CharReceivedCallback)(uint8_t, void *param);

typedef struct SerialDevice
{
   void (*PutChar)(uint8_t);
   uint8_t (*GetChar)(void);
   void (*RegisterCharReceivedCallback)(CharReceivedCallback, void*);
   uint8_t (*GetPutChar)(uint8_t);
} SerialDevice;

/****************************************************************************
 *                              EXPORTED DATA                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DECLARATIONS                       *
 ****************************************************************************/

#endif /* _BUSERIAL_H */

/* End of File */
