/**************************************************************************************************
  Filename:       MHMS.c
  Revised:        Date: May 16 2013
  Mobile Health Monitoring System Group Members: Travis Fary, Masaru Ho, Kris Monpetit

  Description:

  This file contains various defines for the flags for the event handler.  It also contains many
  of the defines relating to setting payloads, event timers, command flags, etc.
  
  Please note that Texas Instruments TVSA coding was used as a frame work
  to develop the MHMS coding. TI's licencing agreement is stated below. 


    Copyright 2009 Texas Instruments Incorporated. All rights reserved.

    IMPORTANT: Your use of this Software is limited to those specific rights
    granted under the terms of a software license agreement between the user
    who downloaded the software, his/her employer (which must be your employer)
    and Texas Instruments Incorporated (the "License").  You may not use this
    Software unless you agree to abide by the terms of the License. The License
    limits your use, and you acknowledge, that the Software may not be modified,
    copied or distributed unless embedded on a Texas Instruments microcontroller
    or used solely and exclusively in conjunction with a Texas Instruments radio
    frequency transceiver, which is integrated into your product.  Other than for
    the foregoing purpose, you may not use, reproduce, copy, prepare derivative
    works of, modify, distribute, perform, display or sell this Software and/or
    its documentation for any purpose.

    YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
    PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
    INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
    NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
    TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
    NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
    LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
    OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
    OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

    Should you have any questions regarding your right to use this Software,
    contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/
#ifndef MHMS_H
#define MHMS_H

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */

#include "hal_board_cfg.h"
#include "ZComDef.h"

/* ------------------------------------------------------------------------------------------------
 *                                          Constants
 * ------------------------------------------------------------------------------------------------
 */

#if MHMS_SRC_RTG 
// Source routing requires special builds of the ZNP with the following settings:
// #define ZIGBEE_SOURCE_ROUTING
// #define ZIGBEE_MANY_TO_ONE
// SRC_RTG_EXPIRY_TIME must be greater than MHMS_DLY_DAT.
// #if MHMS_DONGLE
// #define CONCENTRATOR_ENABLE  TRUE
// CONCENTRATOR_DISCOVERY_TIME must be globally defined to be less than or equal to MHMS_DLY_DAT.
// #endif
#endif


//MHMS task event flags defines
//#define SYS_EVENT_MSG            0x8000   //already defined in comdef.h  used for other tasks
#define MHMS_EVT_ANN               0x4000
#define MHMS_EVT_REQ               0x2000
#define MHMS_EVT_DAT               0x1000
#define MHMS_EVT_CHECKIN           0x0800
   
// Expanding on a TI proprietary Profile Id used for Z-Accel / ZASA / CC2480.
#if !defined MHMS_DEVICE_ID
// Master for CC2480 ZASA reports sets to zero.
#if defined HAL_BOARD_CC2430BB
#define MHMS_DEVICE_ID             0x0001
#elif defined HAL_BOARD_CC2430DB
#define MHMS_DEVICE_ID             0x0002
#elif defined HAL_BOARD_CC2430EB
#define MHMS_DEVICE_ID             0x0003
#elif defined HAL_BOARD_CC2530EB_REV13
#define MHMS_DEVICE_ID             0x0004
#elif defined HAL_BOARD_CC2530EB_REV17
#define MHMS_DEVICE_ID             0x0005
#elif defined HAL_BOARD_F5438
#define MHMS_DEVICE_ID             0x0006  //MHMS this is defined for our particular experimenter's board
#elif defined HAL_BOARD_F2618
#define MHMS_DEVICE_ID             0x0007
#else

#error Unexpected HAL_BOARD - need specific Temp/Volt conversion from specific A2D channel.
#endif
#endif

#define MHMS_PROFILE_ID            0x0F10
#define MHMS_CLUSTER_ID            0x0002
#define MHMS_CLUSTER_CNT           1
#define MHMS_DEVICE_VERSION        0
#define MHMS_FLAGS                 0
 
#define MHMS_ENDPOINT              3

// MHMS Command set.
#define MHMS_CMD_DAT 0                  // MHMS data message.
#define MHMS_CMD_BEG 1                  // Start reporting Pulse data.
#define MHMS_CMD_END 2                  // Stop reporting Pulse data.   
#define MHMS_CMD_DAT_TEST 3             // Used for testing different payload sizes

//MHMSDat (uint8) array defines 
#define MHMS_DAT_LEN                           22      //Bytes
// Testing Data length and transmission interval
#define MHMS_TEST_PAYLOAD_LEN                   90     //Bytes  
#define TEST_DLY_PAYLOAD_TX                     1000
   
#define MHMS_TEST_BUFF_LEN          MHMS_TEST_PAYLOAD_LEN+MHMS_DAT_OFF
#define MHMS_FCS_IDX                MHMS_TEST_BUFF_LEN-1
   
   
// Defines for over the air data buffer   
#define	 MHMS_CMD_IDX	0
#define	 MHMS_IEE_IDX	1
#define	 MHMS_PAR_LSB	9
#define	 MHMS_PAR_MSB	10
#define	 MHMS_CHECK_IN	11
#define	 MHMS_BPM_CHAR	12
#define	 MHMS_BPM	13
#define	 MHMS_RAW_CHAR	14
#define	 MHMS_RAW_LSB	15
#define	 MHMS_RAW_MSB	16
#define	 MHMS_IBI_CHAR	17
#define	 MHMS_IBI	18
#define	 MHMS_TYP_IDX 	19
#define	 MHMS_OPT_IDX	20
#define	 MHMS_RTG_IDX	21

#define MHMS_ADR_LSB               1
#define MHMS_ADR_MSB               2

// Bit values for the MHMS_OPT_IDX.
#define MHMS_OPT_SRC_RTG           0x01  
  
// Flag value for MHMS_CHECK_IN
#define CHECK_IN_ACTIVE                 1
#define CHECK_IN_INACTIVE               2

#define MHMS_SOP_VAL               0xFE
#define MHMS_PORT                  0            //USB port
#define SOP_STATE                  0
#define CMD_STATE                  1
#define FCS_STATE                  2

#define MHMS_SOP_IDX               0
#define MHMS_DAT_OFF               MHMS_ADR_MSB+1
// Not adding +1 for FCS because 1st byte of message is skipped - CMD is always 0 for data.
#define MHMS_BUF_LEN               MHMS_DAT_LEN+MHMS_DAT_OFF
#define MHMS_FCS_IDX               MHMS_BUF_LEN-1

// Defined constants for MHMS task event timers
#define MHMS_DLY_DAT               2             //MHMS every 2ms MHMS calc interrupt
#define MHMS_DLY_DATAREQ           500          //MHMS every 500ms MHMS datareq interrupt 
#define MHMS_DLY_ANN               5000        //MHMS announce event from coordinator
#define MHMS_DLY_CHECKIN           10000       //MHMS send checkin packet to coordinator at 10s intervals

 // Defined Flag bits for MHMS Event handler  
//#define SYS_EVENT_MSG            0x8000       //already defined in comdef.h  used for other tasks
#define MHMS_EVT_ANN               0x4000      //Announce event
#define MHMS_EVT_REQ               0x2000      //Data request event (transmitting data)
#define MHMS_EVT_DAT               0x1000      //Collect data and generate report event
#define MHMS_EVT_CHECKIN           0x0800      //Node sends dummy packet to coordinator
#define TEST_EVT_PAYLOAD_TX         0x0400      //Starts sending the Test payload to coordinator
   
// Attempt to randomly stagger reports within the reporting window.
#define MHMS_STG_DAT               ((uint16)(((uint32)MHMS_DLY_DAT * Onboard_rand()) / 65536))
#define MHMS_DLY_MIN               5000  // Minimum delay (also in case MHMS_STG_DAT returns 0).

#if !defined MHMS_SRC_RTG  
#define MHMS_SRC_RTG               FALSE
#endif
 
/* ------------------------------------------------------------------------------------------------
 *                                           Global Variables
 * ------------------------------------------------------------------------------------------------
 */

extern uint8 MHMSCnfErrCnt;
extern uint8 MHMSTaskId;
extern uint8 EnableUSBPulseSketchTxFlag; 
/* ------------------------------------------------------------------------------------------------
 *                                          Functions
 * ------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 * @fn          MHMSAppInit
 *
 * @brief       This function is the application's task initialization.
 *
 * input parameters
 *
 * None.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void MHMSAppInit(uint8 id);

/**************************************************************************************************
 * @fn          MHMSAppEvt
 *
 * @brief       This function is called to process the OSAL events for the task.
 *
 * input parameters
 *
 * @param       id - OSAL task Id.
 * @param       evts - OSAL events bit mask of pending events.
 *
 * output parameters
 *
 * None.
 *
 * @return      evts - OSAL events bit mask of unprocessed events.
 **************************************************************************************************
 */
uint16 MHMSAppEvt(uint8 id, uint16 evts);

#endif
