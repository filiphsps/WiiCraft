/*---------------------------------------------------------------------------*
  Project:  Dolphin OS
  File:     dvd.h

  Copyright 1998-2004 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: dvd.h,v $
  Revision 1.9  06/07/2006 02:21:23  ooizumi
  Deleted DVDCheckDisk.

  Revision 1.8  06/05/2006 00:21:27  ooizumi
  Enabled DVDCheckDiskAsync for RVL0 target.

  Revision 1.7  05/17/2006 22:16:20  ooizumi
  Added DVD_STATE_NO_INPUT state.

  Revision 1.6  04/24/2006 05:23:16  ooizumi
  Changed a header file for WIN32 target.

  Revision 1.5  03/20/2006 10:24:33  ooizumi
  Deleted APIs for hardware streaming.

  Revision 1.4  2006/03/12 03:03:29  craig
  Added GC and RVL magic number locations to disk id structure.

  Revision 1.3  03/10/2006 22:44:58  ooizumi
  Chenged DVDGetStartAddr's return value u32 to u64.

  Revision 1.2  2006/02/04 11:56:44  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:27  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to
  transitioned from the Dolphin source tree

    
    54    04/03/31 20:27 Hashida
    Updated copyright info.
    
    53    03/09/10 14:37 Ooshima
    Modified DVDDirEntry and DVDRewindDir to remove DVDETH definition.
    
    51    03/04/22 11:29 Hashida
    Modified DVDGetFileInfoStatus to refer fileinfo's member instead of
    just casting to DVDCommandBlock structure.
    
    50    03/02/28 5:30p Ooshima
    Changed DVDCommandBlock and DVDDirEntry structure for DVDETH again
    
    49    03/01/09 10:34a Ooshima
    Changed DVDCommandBlock and DVDDirEntry structure for DVDETH
    
    47     8/22/02 12:00:00 Shiki
    Clean up.

    46     8/20/02 21:38:00 Shiki
    Added DVDSetAutoFatalMessaging().

    45     8/05/02 16:19:00 Shiki
    Added const keywords to relevant function prototypes.

    44    02/02/07 16:04 Hashida
    Change the return value of DVDGenerateDiskID from void to DVDDiskID*

    43    1/02/02 5:00p Hashida
    Added DVDCompareDiskID and DVDGenerateDiskID.

    42    8/10/01 3:04p Hashida
    Added DVDFastOpenDir

    41    7/06/01 1:20a Hashida
    Resurrected function version of DVDGetFileInfoStatus().

    40    6/29/01 11:43a Hashida
    Added DVDCheckDisk().

    39    6/26/01 9:18a Hashida
    Modified so that DVDGetFileInfoStatus is properly prototype'd for MAC
    build.

    38    6/15/01 10:35p Hashida
    Deleted obsolete result codes.

    37    6/15/01 9:01p Hashida
    Changed DVDGetFileInfoStatus to a macro.

    36    5/29/01 11:52a Hashida
    Removed duplicated DVDPause and DVDResume prototypes.

    35    5/10/01 2:24p Hashida
    Added DVDDumpWaitingQueue.

    34    5/01/01 2:49p Hashida
    Removed DVDGetStreamStartAddr & DVDGetStreamLength.

    33    4/19/01 5:40p Hashida
    Added DVDGetCurrentDiskID

    32    3/22/01 6:10p Hashida
    Added DVDCancelAll and DVDCancelAllAsync.
    Moved DVDCommandBlock structure in DVDFileInfo to the first member.

    31    3/02/01 5:48p Hashida
    Modified error code handling (fatal error, internal retry and retry)

    30    3/02/01 11:35a Hashida
    Added DVDCancel, DVDPause, DVDResume, DVDGetTransferredSize.

    29    2/08/01 3:46p Hashida
    Added DVDPause and DVDResume prototypes.

    28    1/08/01 7:02p Hashida
    Added DVDSet/GetUserData macros.

    27    11/13/00 5:30p Hashida
    Added streamingBufSize member to diskid.


    26    10/27/00 2:24p Hashida
    Added a check code so that audio streaming command will not be issued
    while a track is auto finishing.

    25    10/10/00 11:28a Hashida
    Fixed a problem that MAC target won't be built.

    24    10/09/00 6:53p Hashida
    Added prioritized queuing.

    23     9/29/00 9:51p Hirose
    replaced "MAC" flag by better alternatives

    22    9/26/00 3:38p Hashida
    Added DVDChangeDisk (synchronous version)

    21    9/25/00 3:32p Hashida
    Changed API names that don't follow the convention (sync, async)

    20    7/21/00 11:15a Hashida
    Added DVD_STATE_PAUSING.

    19    7/20/00 12:32p Hashida
    Removed DVDConvertEntrynumToPath

    18    7/20/00 9:46a Hashida
    Added DVDFastOpen(), DVDConvertPathToEntrynum and
    DVDConvertEntrynumToPath.

    17     7/07/00 6:00p Dante
    PC Compatibility

    16    5/14/00 8:06p Hashida
    Added DVDGetCurrentDir

    15     3/28/00 5:40p Hashida
    Removed relocate FST function.

    14    4/13/00 5:21p Hashida
    Added DVD_RESULT_* definitions for streaming commands.
    Added more streaming APIs' prototypes.

    13    4/12/00 3:58p Hashida
    Added audio streaming stuffs.

    12    4/12/00 1:31p Hashida
    Misc. change.

    11    3/29/00 2:29p Hashida
    Added DVDGetDirEntryName and DVDDirEntryIsDir

    10    3/28/00 3:42p Hashida
    Added directory accessing functions to MAC build.

    9     3/13/00 2:46p Hashida
    Added DVDGetFSTLocation.

    8     3/10/00 2:38p Hashida
    Added DVDRelocateFST

    7     3/02/00 3:00p Ryan
    Added DVDChangeDir to MAC build

    6     3/01/00 1:13p Hashida
    Renamed DVDDirEntry->filename to name.

    5     2/29/00 7:57p Hashida
    Added directory access support.

    4     2/02/00 6:28p Tian
    Halved size of DVD_FST_MAX_SIZE

    3     1/13/00 12:14p Hashida
    Added directory access functions for future use.

    21    10/06/99 10:33a Hashida
    Changed the filename length limit to 200 chars.

    20    9/09/99 5:55p Hashida
    Removed warnings.

    19    8/26/99 5:37p Hashida
    Added DVDSetAutoInvalidation

    18    7/21/99 11:52p Hashida
    Added DVD_MIN_TRANSFER_SIZE

    17    7/21/99 9:47p Hashida
    Added DVDSeek(), DVDChangeDir(), DVDChangeDisk()

    16    7/20/99 2:37p Hashida
    Changed DVDFileInfo structure for EPPC
    Removed DVD_RESULT_GOOD

    15    7/19/99 11:45p Hashida
    changed the value for fatal error to -1

    14    7/19/99 4:29p Hashida
    Added DVDCommandBlockStatus and DVDDriveStatus.

    13    7/19/99 2:58p Hashida
    added DVD_FST_MAX_SIZE, DVD_STATE*, DVD_RESULT* and DVDCommandBlock.

    12    7/09/99 9:59p Hashida
    added DVDDiskID structure

    9     6/12/99 12:11a Hashida
    Added DVDSetRoot()

    8     6/11/99 3:04p Shiki
    Added DVDGetFileInfoStatus().

    7     6/04/99 3:14p Hashida
    fixed small mistakes

    6     5/28/99 1:34p Shiki
    Fixed DVDReadAll() and DVDReadAllAsync() macros.

    5     5/11/99 4:42p Shiki
    Refreshed include tree.

    3     4/30/99 4:22p Shiki
    Added DVDInit() declaration.

    2     4/30/99 4:02p Shiki
    Supported DVDReadAsync().

    1     4/29/99 2:51p Shiki

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __DVD_H__
#define __DVD_H__

#ifdef  MACOS
#include <OSUtils.h>
#include <Gestalt.h>
#include <Files.h>
#endif  // MACOS

#ifdef WIN32
#include <windows.h>
#endif

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MACOS
// the following is a restriction that only exists on Mac emulator
#define DVD_PATH_MAX    200  // The number of bytes in an absolute pathname
                             // excluding terminating '\0'.
#endif

typedef struct DVDDiskID DVDDiskID;

struct DVDDiskID
{
    char      gameName[4];
    char      company[2];
    u8        diskNumber;
    u8        gameVersion;
    u8        streaming;
    u8        streamingBufSize; // 0 = default
    u8        padding[14];      // 0's are stored
    u32       rvlMagic;         // Revolution disk magic number
    u32       gcMagic;          // GC magic number is here
};

typedef struct DVDCommandBlock DVDCommandBlock;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock* block);

struct DVDCommandBlock
{
    DVDCommandBlock* next;
    DVDCommandBlock* prev;
    u32              command;
    s32              state;
    u32              offset;
    u32              length;
    void*            addr;
    u32              currTransferSize;
    u32              transferredSize;
    DVDDiskID*       id;
    DVDCBCallback    callback;
    void*            userData;
};

typedef struct DVDFileInfo  DVDFileInfo;

/*---------------------------------------------------------------------------*
  Name:         DVDCallback

  Description:  DVD callback function

  Arguments:    result      If the function that set the callback succeeds,
                            it is the number of bytes transferred. If that
                            function fails, it is -1.

  Returns:      None.
 *---------------------------------------------------------------------------*/
typedef void (*DVDCallback)(s32 result, DVDFileInfo* fileInfo);

struct DVDFileInfo
{
#ifndef MACOS
    DVDCommandBlock cb;
#endif

    u32             startAddr;      // disk address of file
    u32             length;         // file size in bytes

#ifdef MACOS
    DVDFileInfo*    next;
#endif  // MACOS
    DVDCallback     callback;

#ifdef WIN32
    FILE * file;
#endif

#ifdef  MACOS
    IOParam         pb;
#endif  // MACOS

};

typedef struct
{
    u32         entryNum;
    u32         location;
    u32         next;
} DVDDir;

typedef struct
{
    u32         entryNum;
    BOOL        isDir;
    char*       name;
} DVDDirEntry;


// FST maximum size
#ifndef MINNOW
#define DVD_FST_MAX_SIZE          0x00100000
#else // MINNOW
#define DVD_FST_MAX_SIZE          0x00080000
#endif

#define DVD_MIN_TRANSFER_SIZE     32

#define DVD_STATE_FATAL_ERROR     -1
#define DVD_STATE_END             0
#define DVD_STATE_BUSY            1
#define DVD_STATE_WAITING         2
#define DVD_STATE_COVER_CLOSED    3         // internal state. never returns.
#define DVD_STATE_NO_DISK         4
#define DVD_STATE_COVER_OPEN      5
#define DVD_STATE_WRONG_DISK      6
#define DVD_STATE_MOTOR_STOPPED   7
#define DVD_STATE_PAUSING         8
#define DVD_STATE_IGNORED         9
#define DVD_STATE_CANCELED        10
#define DVD_STATE_RETRY           11
#define DVD_STATE_NO_INPUT        12

#define DVD_FILEINFO_READY        0
#define DVD_FILEINFO_BUSY         1

#define DVD_RESULT_GOOD           0
#define DVD_RESULT_FATAL_ERROR    -1
#define DVD_RESULT_IGNORED        -2
#define DVD_RESULT_CANCELED       -3

#define DVD_AIS_SUCCESS           0x0

#define DVDGetStartAddr(fileInfo)                               \
        ((u64)((u64)(fileInfo)->startAddr) << 2)

#define DVDGetLength(fileInfo)                                  \
        ((fileInfo)->length)

void DVDInit             ( void );

BOOL DVDOpen             ( const char* fileName, DVDFileInfo* fileInfo );
BOOL DVDFastOpen         ( s32 entrynum, DVDFileInfo* fileInfo );

#ifndef MACOS
s32  DVDReadPrio         ( DVDFileInfo* fileInfo, void* addr, s32 length,
                           s32 offset, s32 prio );

BOOL DVDReadAsyncPrio    ( DVDFileInfo* fileInfo, void* addr, s32 length,
                           s32 offset,
                           DVDCallback callback, s32 prio );

#define DVDRead(fileInfo, addr, length, offset)                 \
                         DVDReadPrio((fileInfo), (addr), (length), (offset), 2)
#define DVDReadAsync(fileInfo, addr, length, offset, callback)  \
                         DVDReadAsyncPrio((fileInfo), (addr), (length), (offset), (callback), 2)
#else
s32  DVDRead             ( DVDFileInfo* fileInfo, void* addr, s32 length,
                           s32 offset );

BOOL DVDReadAsync        ( DVDFileInfo* fileInfo, void* addr, s32 length,
                           s32 offset,
                           DVDCallback callback );
#endif

BOOL DVDClose            ( DVDFileInfo* fileInfo );

#ifndef MACOS
BOOL DVDGetCurrentDir    ( char* path, u32 maxlen );
#endif

BOOL DVDChangeDir        ( const char* dirName );

#ifdef MACOS
BOOL DVDMovePickup       ( DVDFileInfo* fileInfo,
                           s32 offset,
                           DVDCallback callback );
#else  // EPPC
s32  DVDSeekPrio         ( DVDFileInfo* fileInfo,
                           s32 offset, s32 prio );

BOOL DVDSeekAsyncPrio    ( DVDFileInfo* fileInfo,
                           s32 offset,
                           DVDCallback callback, s32 prio );

#define DVDSeek(fileInfo, offset)                               \
                         DVDSeekPrio((fileInfo), (offset), 2)
#define DVDSeekAsync(fileInfo, offset, callback)                \
                         DVDSeekAsyncPrio((fileInfo), (offset), (callback), 2)

s32  DVDChangeDisk       ( DVDCommandBlock* block, DVDDiskID* id );

BOOL DVDChangeDiskAsync  ( DVDCommandBlock* block, DVDDiskID* id,
                           DVDCBCallback callback );
#endif

s32  DVDGetCommandBlockStatus
                         ( const DVDCommandBlock* block );

s32  DVDGetFileInfoStatus( const DVDFileInfo* fileInfo );

#define DVDGetFileInfoStatus(fileinfo)                          \
                         DVDGetCommandBlockStatus(&(fileinfo)->cb)

s32  DVDGetDriveStatus   ( void );

BOOL DVDSetAutoInvalidation
                         ( BOOL autoInval );

void* DVDGetFSTLocation  ( void );

#ifdef MACOS
void DVDSetRoot          ( const char *rootPath );
#endif
#ifdef WIN32
void DVDSetRoot          ( const char *rootPath );
#endif

s32  DVDConvertPathToEntrynum
                         ( const char* pathPtr );

// Directory access functions
BOOL DVDOpenDir          ( const char* dirName, DVDDir* dir );
BOOL DVDFastOpenDir      ( s32 entrynum, DVDDir* dir );
BOOL DVDReadDir          ( DVDDir* dir, DVDDirEntry* dirent );
BOOL DVDCloseDir         ( DVDDir* dir );

void DVDPause            ( void );
void DVDResume           ( void );

/*---------------------------------------------------------------------------*
  Name:         DVDTellDir

  Description:  Returns the current location associated with the directory

  Arguments:    dir         Pre-opened DVDDir* structure

  Returns:      current location
 *---------------------------------------------------------------------------*/
#define DVDTellDir(dir)             ((dir)->location)

/*---------------------------------------------------------------------------*
  Name:         DVDSeekDir

  Description:  Sets the position of the next DVDReadDir on the directory

  Arguments:    dir         Pre-opened DVDDir* structure
                loc         location to set

  Returns:      None
 *---------------------------------------------------------------------------*/
#define DVDSeekDir(dir, loc)        ((dir)->location = loc)

/*---------------------------------------------------------------------------*
  Name:         DVDRewindDir

  Description:  Resets the position of the directory to the beginning

  Arguments:    dir         Pre-opened DVDDir* structure

  Returns:      None
 *---------------------------------------------------------------------------*/
void DVDRewindDir(DVDDir* dir);

#define DVDGetDirEntryName(dirent)  ((dirent)->name)
#define DVDDirEntryIsDir(dirent)    ((dirent)->isDir)

/*---------------------------------------------------------------------------*
  Name:         DVDSetUserData

  Description:  Set user data in command block

  Arguments:    block       Command block
                data        Data to set

  Returns:      None
 *---------------------------------------------------------------------------*/
#define DVDSetUserData(block, data) ((block)->userData = (data))

/*---------------------------------------------------------------------------*
  Name:         DVDGetUserData

  Description:  Get user data in command block

  Arguments:    block       Command block

  Returns:      data (void * type)
 *---------------------------------------------------------------------------*/
#define DVDGetUserData(block)       ((block)->userData)

#ifndef EMU

BOOL DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDCancel(DVDCommandBlock* block);
BOOL DVDCancelAllAsync(DVDCBCallback callback);
s32 DVDCancelAll(void);

s32 DVDGetTransferredSize(DVDFileInfo* fileinfo);

DVDDiskID* DVDGetCurrentDiskID(void);

void DVDDumpWaitingQueue(void);

BOOL DVDCheckDiskAsync(DVDCommandBlock* block, DVDCBCallback callback);

BOOL DVDCompareDiskID(const DVDDiskID* id1, const DVDDiskID* id2);

DVDDiskID* DVDGenerateDiskID(DVDDiskID* id, const char* game, const char* company,
                             u8 diskNum, u8 version);

BOOL DVDSetAutoFatalMessaging(BOOL enable);

#endif

#ifdef __cplusplus
}
#endif

#endif  // __DVD_H__
