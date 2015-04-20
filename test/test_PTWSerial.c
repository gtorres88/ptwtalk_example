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

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/

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

void test_SendMessageShouldPrependSOF(void)
{
    TEST_FAIL_MESSAGE("NOT IMPLEMENTED");
}

void test_SendMessageShouldIncludeLength(void)
{
    TEST_FAIL_MESSAGE("NOT IMPLEMENTED");
}

void test_SendMessageShouldIncludeCMD(void)
{
    TEST_FAIL_MESSAGE("NOT IMPLEMENTED");
}

void test_SendMessageShouldIncludeEOF(void)
{
    TEST_FAIL_MESSAGE("NOT IMPLEMENTED");
}

void test_SendMessageShouldIncludePayload(void)
{
    TEST_FAIL_MESSAGE("NOT IMPLEMENTED");
}


void tearDown(void)
{
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
