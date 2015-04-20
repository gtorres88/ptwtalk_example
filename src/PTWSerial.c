/************************************************************************//**
 *
 * \file PTWSerial.c
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

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "PTWSerial.h"

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/

/****************************************************************************
 *                              PRIVATE DATA                                *
 ****************************************************************************/
static SerialDevice *MyDevice;
/****************************************************************************
 *                             EXTERNAL DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DECLARATIONS                        *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/
void PTW_Init(SerialDevice *dev)
{
    MyDevice = dev;
}


PTW_STATUS PTW_SendMessage(uint8_t cmd, uint8_t *payload, uint8_t len)
{

    MyDevice->PutChar(SOM); //send SOM
    MyDevice->PutChar(cmd); //send CMD
    MyDevice->PutChar(len); //send CMD

    return PTW_SUCCESS;
}

PTW_STATUS PTW_RegisterMessageHandler(MessageCallback *cb)
{

    return PTW_SUCCESS;
}


/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

/** \}*/
