/************************************************************************//**
 *
 * \file test_PTWSerial.c
 *
 * \brief Test scripts for module PTWSerial to be run with Unity
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
#include "unity.h"
#include "PTWSerial.h"
#include "FakeSerial.h"
#include "CommonDefines.h"

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/
#define TEST_COMMAND 0x0A //fake command id for testing
#define TEST_PAYLOAD {1,2,3} //fake payload for testing
/****************************************************************************
 *                              PRIVATE DATA                                *
 ****************************************************************************/
static SerialDevice *FakeSerial;
/****************************************************************************
 *                             EXTERNAL DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DECLARATIONS                        *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/

void setUp(void)
{
    //Create a fake serial device
    FakeSerial = FakeSerial_Create();

    //inject fake serial as a dependency to PTW module
    PTW_Init(FakeSerial);
}

void tearDown(void)
{
    //Reset the output buffer
    FakeSerial_ResetOutputBuffer(FakeSerial);
    FakeSerial_Destroy(FakeSerial);
}

void test_SendMessageShouldPrependSOF(void)
{
    TEST_IGNORE_MESSAGE("NOT IMPLEMENTED");
    //send message
    PTW_SendMessage(TEST_COMMAND, NULL, 0);

    //Get output buffer
    OutputBuffer fakeBuffer = FakeSerial_GetOutputBuffer(FakeSerial);

    //Check output buffer to make sure SOM was sent
    TEST_ASSERT_EQUAL(SOM, fakeBuffer.buffer[0]);

}


void test_SendMessageShouldIncludeCMD(void)
{
    TEST_IGNORE_MESSAGE("NOT IMPLEMENTED");

    //send message
    PTW_SendMessage(TEST_COMMAND, NULL, 0);

    //Get output buffer
    OutputBuffer fakeBuffer = FakeSerial_GetOutputBuffer(FakeSerial);

    //Check output buffer to make sure SOM was sent
    TEST_ASSERT_EQUAL(TEST_COMMAND, fakeBuffer.buffer[1]);
}

void test_SendMessageShouldIncludeLength(void)
{
    TEST_IGNORE_MESSAGE("NOT IMPLEMENTED");

    uint8_t payload[] = TEST_PAYLOAD;

    //send message
    PTW_SendMessage(TEST_COMMAND, NULL, 3);

    //Get output buffer
    OutputBuffer fakeBuffer = FakeSerial_GetOutputBuffer(FakeSerial);

    //Check output buffer to make sure SOM was sent
    TEST_ASSERT_EQUAL(3, fakeBuffer.buffer[2]);


}

void test_SendMessageShouldIncludeEOF(void)
{
    TEST_IGNORE_MESSAGE("NOT IMPLEMENTED");
}

void test_SendMessageShouldIncludePayload(void)
{
    TEST_IGNORE_MESSAGE("NOT IMPLEMENTED");
}


/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

// End of file.
