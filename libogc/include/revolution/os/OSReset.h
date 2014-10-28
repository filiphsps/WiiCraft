/*---------------------------------------------------------------------------*
  Project:  Dolphin OS Reset API
  File:     OSReset.h

  Copyright 2001-2003 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: OSReset.h,v $
  Revision 1.6  08/10/2006 13:48:37  urata
  Added OS_SHUTDOWN_PRIO_VI.

  Revision 1.5  07/24/2006 06:14:34  hirose
  Cleanup.

  Revision 1.4  07/24/2006 00:23:34  hirose
  Changes due to new reset/shutdown architecture.

  Revision 1.3  06/16/2006 12:45:42  ooizumi
  Commented out definition of OSExec.

  Revision 1.2  2006/02/04 11:56:47  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    20    04/01/30 16:42 Hashida
    Added OSExec.
    
    
    19    11/28/03 19:04 Shiki
    Removed OSGetRestartCode().

    18    11/13/03 16:57 Shiki
    Fixed OSIsRestart() macro for new OSGetResetCode().

    17    11/13/03 14:20:00 Shiki
    Added support for OSGetRestartCode().

    16    10/24/03 9:33 Shiki
    Defined OS_RESETCODE_NETCONFIG.

    15    7/10/03 14:38 Shiki
    Defined OS_RESET_PRIO_ALARM.

    14     03/04/16 22:32:00 Hashida
    Added OSSetBootDol.

    13    3/12/03 11:28 Shiki
    Defined OS_RESET_PRIO_SO and OS_RESET_PRIO_IP.

    12    2/13/03 14:24 Shiki
    Defined OS_RESET_TIMEOUT.

    11    02/11/19 14:55 Hirose
    Added OS_RESET_PRIO_GX.

    10    02/10/28 20:28 Hashida
    Added OSIsRestart().

    9     02/04/11 17:59 Hashida
    Added OSGetSavedRegion

    8     9/15/01 3:31a Hashida
    Added OS_RESET_SHUTDOWN

    7     9/07/01 5:30a Hashida
    Added OSSet/GetSaveRegion.

    6     7/18/01 10:55p Hashida
    Changed definitions.

    5     7/11/01 10:19p Hashida
    Added code definition for restarting.

    4     5/17/01 8:20p Shiki
    Modified priority from s32 to u32.

    3     5/17/01 7:58p Shiki
    Revised.

    2     01/04/23 16:31:00 Shiki
    Added menu param to OSResetSystem().

    1     01/04/09 13:52 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __OSRESET_H__
#define __OSRESET_H__

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_RESETCODE_RESTART    0x80000000      // not by cold/hot reset
#define OS_RESETCODE_SYSTEM     0x40000000      // reserved by system

#define OS_RESETCODE_EXEC       0xC0000000
#define OS_RESETCODE_NETCONFIG  0xC0010000

#define OS_RESET_TIMEOUT        OSMillisecondsToTicks(1000)

#define OS_RESET_RESTART        0
#define OS_RESET_HOTRESET       1
#define OS_RESET_SHUTDOWN       2

#define OS_SHUTDOWN_PRIO_SO         110     // SO API
#define OS_SHUTDOWN_PRIO_IP         111     // IP API
#define OS_SHUTDOWN_PRIO_MIDI       126     // MIDI API
#define OS_SHUTDOWN_PRIO_CARD       127     // CARD API
#define OS_SHUTDOWN_PRIO_PAD        127     // PAD API
#define OS_SHUTDOWN_PRIO_STEERING   127     // SI Steering
#define OS_SHUTDOWN_PRIO_GX         127     // GX API
#define OS_SHUTDOWN_PRIO_MEMPROT    127     // OS Memory Protection
#define OS_SHUTDOWN_PRIO_ALARM      4294967295  // OSAlarm
#define OS_SHUTDOWN_PRIO_VI         127     // VI API

// Event types for __OSShutdownDevices()
#define OS_SD_FATALERR          0
#define OS_SD_REBOOT            1
#define OS_SD_SHUTDOWN          2
#define OS_SD_IDLE              3
#define OS_SD_RESTART           4
#define OS_SD_RETURNTOMENU      5
#define OS_SD_EXEC              6


typedef BOOL (* OSShutdownFunction )( BOOL final, u32 event );
typedef struct OSShutdownFunctionInfo OSShutdownFunctionInfo;

struct OSShutdownFunctionInfo
{
    // public
    OSShutdownFunction      func;
    u32                     priority;

    // private
    OSShutdownFunctionInfo* next;
    OSShutdownFunctionInfo* prev;
};

void OSRegisterShutdownFunction     ( OSShutdownFunctionInfo* info );
void OSUnregisterShutdownFunction   ( OSShutdownFunctionInfo* info );


void OSRebootSystem         ( void );
void OSShutdownSystem       ( void );
void OSRestart              ( u32 resetCode );
void OSReturnToMenu         ( void );


u32  OSGetResetCode         ( void );
void OSGetSaveRegion        ( void** start, void** end );
void OSGetSavedRegion       ( void** start, void** end );
void OSSetSaveRegion        ( void* start, void* end );


// Obsolete (implemented as stubs)
void OSResetSystem          ( int reset, u32 resetCode, BOOL forceMenu );
u32  OSSetBootDol           ( u32 dolOffset );

// Obsolete
#if 0
typedef BOOL (* OSResetFunction )(BOOL final);
typedef struct OSResetFunctionInfo OSResetFunctionInfo;

struct OSResetFunctionInfo
{
    // public
    OSResetFunction      func;
    u32                  priority;

    // private
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

void OSRegisterResetFunction  ( OSResetFunctionInfo* info );
void OSUnregisterResetFunction( OSResetFunctionInfo* info );
#endif

// Hidden temporary
// void OSExecv                  ( const char* dolfile, char* const argv[] );
// void OSExecl                  ( const char* dolfile,
//                                const char* arg0, .../*, (char*)NULL */ );

/*---------------------------------------------------------------------------*
  Name:         OSIsRestart

  Description:  Check to see if it's restarted

  Arguments:    None

  Returns:      True if restarted, False if cold-started
 *---------------------------------------------------------------------------*/
#define OSIsRestart()   \
            ((OSGetResetCode() & OS_RESETCODE_RESTART) ? TRUE : FALSE)

#ifdef __cplusplus
}
#endif

#endif  // __OSRESET_H__
