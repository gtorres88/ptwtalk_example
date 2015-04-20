/************************************************************************//**
 *
 * \file PTWSerial.h
 *
 * \addtogroup PTWSerial PTWSerial
 * \{
 *
 * \brief
 *
 * \note
 *
 * \author gtorres (BuLogics, Inc.)
 * \date 2015-04-19
 *
 ****************************************************************************/

#ifndef _PTWSERIAL_H
#define _PTWSERIAL_H

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "types.h"
#include "BuSerial.h"
/****************************************************************************
 *                     EXPORTED TYPES and DEFINITIONS                       *
 ****************************************************************************/
typedef enum
{
    PTW_SUCCESS = 0
} PTW_STATUS;

typedef void (*MessageCallback)(uint8_t cmd, uint8_t *payload, uint8_t len);

/****************************************************************************
 *                              EXPORTED DATA                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DECLARATIONS                       *
 ****************************************************************************/

void PTW_Init(SerialDevice *dev);

PTW_STATUS PTW_SendMessage(uint8_t cmd, uint8_t *payload, uint8_t len);
PTW_STATUS PTW_RegisterMessageHandler(MessageCallback *cb);



#endif /* _PTWSERIAL_H */

/** \}*/
