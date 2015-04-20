/************************************************************************//**
 *
 * \file FakeSerial.c
 * \addtogroup FakeSerial FakeSerial
 *
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

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "FakeSerial.h"
#include "CommonDefines.h"

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/
#define MAX_SERIALS 2
#define DEVICE_NOT_FOUND 0xff
#define GET_CHAR_BUF_SIZE 255

/****************************************************************************
 *                              PRIVATE DATA                                *
 ****************************************************************************/

//output buffer
static OutputBuffer FakeOutputBuffer[MAX_SERIALS];

static CharReceivedCallback SerialCharReceived[MAX_SERIALS];
static void * CallbackParam[MAX_SERIALS];
static uint8_t UsedSerials[] = {FALSE, FALSE};
static uint8_t GetCharBuf[MAX_SERIALS][GET_CHAR_BUF_SIZE];
static uint8_t GetCharBufReadIndex[MAX_SERIALS];
static uint8_t GetCharBufWriteIndex[MAX_SERIALS];
static GetCharCallback GetCharPassthrough[MAX_SERIALS];
static void *GetCharPassthroughParam[MAX_SERIALS];

/****************************************************************************
 *                             EXTERNAL DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DECLARATIONS                        *
 ****************************************************************************/

/*
 * yes, yes, this is gross. But until we have the ability to pass param
 * pointers to the getchar, putchar, etc. functions there's no way to
 * re-use the same function for multiple instances of a device within
 * a compilation unit.
 */

static void fakePutChar0(uint8_t byte);
static uint8_t fakeGetChar0(void);
static uint8_t fakeGetPutChar0(uint8_t byte);
static void fakeRegisterSerialCallback0(CharReceivedCallback callback,
        void *params);

static void fakePutChar1(uint8_t byte);
static uint8_t fakeGetChar1(void);
static uint8_t fakeGetPutChar1(uint8_t byte);
static void fakeRegisterSerialCallback1(CharReceivedCallback callback,
        void *params);

static void fakePutChar(uint8_t byte, uint8_t index);
static uint8_t fakeGetChar(uint8_t index);
static uint8_t fakeGetPutChar(uint8_t byte, uint8_t index);
static void fakeRegisterSerialCallback(CharReceivedCallback callback,
        void *params, uint8_t index);

static uint8_t getDeviceIndex(SerialDevice *dev);

static SerialDevice FakeSerial[MAX_SERIALS] = {
    {fakePutChar0, fakeGetChar0, fakeRegisterSerialCallback0, fakeGetPutChar0},
    {fakePutChar1, fakeGetChar1, fakeRegisterSerialCallback1, fakeGetPutChar1}
};
/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/

SerialDevice *FakeSerial_Create(void)
{
    uint8_t i;
    for (i = 0; i < MAX_SERIALS; ++i)
    {
        if (! UsedSerials[i])
        {
            UsedSerials[i] = TRUE;
            //reset output buffer to 0
            FakeSerial_ResetOutputBuffer(&FakeSerial[i]);
            GetCharBufReadIndex[i] = 0;
            GetCharBufWriteIndex[i] = 0;
            SerialCharReceived[i] = NULL;
            CallbackParam[i] = NULL;
            GetCharPassthrough[i] = NULL;
            GetCharPassthroughParam[i] = NULL;
            return &FakeSerial[i];
        }
    }
    return NULL;
}

void FakeSerial_Destroy(SerialDevice *dev)
{
    uint8_t index = getDeviceIndex(dev);
    if (DEVICE_NOT_FOUND != index)
    {
        UsedSerials[index] = FALSE;
    }
}

OutputBuffer FakeSerial_GetOutputBuffer(SerialDevice *dev)
{
    uint8_t index = getDeviceIndex(dev);
    if (DEVICE_NOT_FOUND != index)
    {
        return FakeOutputBuffer[index];
    }
    /* how should we handle this? just return the data from index 0 */
    return FakeOutputBuffer[0];
}


void FakeSerial_ResetOutputBuffer(SerialDevice *dev)
{
    uint8_t i;
    uint8_t index = getDeviceIndex(dev);

    if (DEVICE_NOT_FOUND != index)
    {
        for (i = 0; i < MAX_BUFFER_LENGTH; i++)
        {
            FakeOutputBuffer[index].buffer[i] = 0;
        }
    FakeOutputBuffer[index].bufferLength = 0;
    }
}

void FakeSerial_ReceiveFakeData(uint8_t *inputData, uint8_t len, SerialDevice *dev)
{
    while(len--)
    {
        FakeSerial_ReceiveFakeByte(*(inputData++), dev);
    }
}

/* if there's a byte received callback registered, use it. Otherwise
 * buffer up the data for a future GetChar */
void FakeSerial_ReceiveFakeByte(uint8_t byte, SerialDevice *dev)
{
    uint8_t index = getDeviceIndex(dev);

    if (DEVICE_NOT_FOUND != index)
    {
        if(SerialCharReceived[index])
        {
            SerialCharReceived[index](byte, CallbackParam[index]);
        }
        else if(GetCharBufWriteIndex[index] < GET_CHAR_BUF_SIZE)
        {
            GetCharBuf[index][GetCharBufWriteIndex[index]++] = byte;
        }
    }
}

void FakeSerial_RegisterGetCharCallback(GetCharCallback callback, void *param,
        SerialDevice *dev)
{
    uint8_t index = getDeviceIndex(dev);
    if (DEVICE_NOT_FOUND != index)
    {
        GetCharPassthrough[index] = callback;
        GetCharPassthroughParam[index] = param;
    }
}

/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/

static void fakePutChar0(uint8_t byte)
{
    fakePutChar(byte, 0);
}

static uint8_t fakeGetChar0(void)
{
    return fakeGetChar(0);
}

static uint8_t fakeGetPutChar0(uint8_t byte)
{
    return fakeGetPutChar(byte, 0);
}

static void fakeRegisterSerialCallback0(CharReceivedCallback callback,
        void *params)
{
    fakeRegisterSerialCallback(callback, params, 0);
}

static void fakePutChar1(uint8_t byte)
{
    fakePutChar(byte, 1);
}

static uint8_t fakeGetChar1(void)
{
    return fakeGetChar(1);
}

static uint8_t fakeGetPutChar1(uint8_t byte)
{
    return fakeGetPutChar(byte, 1);
}

static void fakeRegisterSerialCallback1(CharReceivedCallback callback,
        void *params)
{
    fakeRegisterSerialCallback(callback, params, 1);
}

static void fakePutChar(uint8_t byte, uint8_t index)
{
    if(FakeOutputBuffer[index].bufferLength < MAX_BUFFER_LENGTH)
    {
        uint8_t bufIndex = FakeOutputBuffer[index].bufferLength++;
        FakeOutputBuffer[index].buffer[bufIndex] = byte;
    }
}

/* if the test code has registered a callback, call it, otherwise read
 * from the buffer
 */
static uint8_t fakeGetChar(uint8_t index)
{
    if(GetCharPassthrough[index])
    {
        return GetCharPassthrough[index](GetCharPassthroughParam[index]);
    }
    else if(GetCharBufReadIndex[index] < GetCharBufWriteIndex[index])
    {
        return GetCharBuf[index][GetCharBufReadIndex[index]++];
    }
    else
    {
        return 0xff;
    }
}

static uint8_t fakeGetPutChar(uint8_t byte, uint8_t index)
{
    if(FakeOutputBuffer[index].bufferLength < MAX_BUFFER_LENGTH)
    {
        FakeOutputBuffer[index].buffer[FakeOutputBuffer[index].bufferLength++] = byte;
    }
    return fakeGetChar(index);
}

static void fakeRegisterSerialCallback(CharReceivedCallback callback,
        void *param, uint8_t index)
{
    SerialCharReceived[index] = callback;
    CallbackParam[index] = param;
}

static uint8_t getDeviceIndex(SerialDevice *dev)
{
    uint8_t i;
    for (i = 0; i < MAX_SERIALS; ++i)
    {
        if (&FakeSerial[i] == dev)
        {
            return i;
        }
    }
    return DEVICE_NOT_FOUND;
}

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

/** \}*/
