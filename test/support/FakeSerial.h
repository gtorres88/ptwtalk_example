/************************************************************************//**
 *
 * \file FakeSerial.h
 *
 * \addtogroup FakeSerial FakeSerial
 * \{
 *
 * \brief
 *
 * \note
 *
 * \author gtorres (BuLogics, Inc.)
 * \date 2013-02-12
 *
 ****************************************************************************/

#ifndef _FAKESERIAL_H
#define _FAKESERIAL_H

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "BuSerial.h"
/****************************************************************************
 *                     EXPORTED TYPES and DEFINITIONS                       *
 ****************************************************************************/
#define MAX_BUFFER_LENGTH 255

typedef struct
{
    uint8_t bufferLength;
    uint8_t buffer[MAX_BUFFER_LENGTH];
} OutputBuffer;

typedef uint8_t (*GetCharCallback)(void *);
/****************************************************************************
 *                              EXPORTED DATA                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DECLARATIONS                       *
 ****************************************************************************/
SerialDevice *FakeSerial_Create(void);
void FakeSerial_Destroy(SerialDevice *dev);
OutputBuffer FakeSerial_GetOutputBuffer(SerialDevice *dev);
void FakeSerial_ResetOutputBuffer(SerialDevice *dev);
void FakeSerial_ReceiveFakeData(uint8_t *data, uint8_t len, SerialDevice *dev);
void FakeSerial_ReceiveFakeByte(uint8_t byte, SerialDevice *dev);
void FakeSerial_RegisterGetCharCallback(GetCharCallback callback, void *param,
        SerialDevice *dev);
#endif /* _FAKESERIAL_H */

/** \}*/
