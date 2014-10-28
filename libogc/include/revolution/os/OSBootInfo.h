/*---------------------------------------------------------------------------*
  Project:  Dolphin OS Boot info structure
  File:     OSBootInfo.h

  Copyright 1998, 1999 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: OSBootInfo.h,v $
  Revision 1.2  2006/02/04 11:56:47  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    3     4/05/00 7:31p Shiki
    Added comment.

    2     2/01/00 8:16p Tian
    Added comment about consoleType's position.

    7     11/16/99 9:48a Hashida
    Added a magic number for JTAG boot.

    6     8/11/99 11:18a Tian
    Added magic definition and consoleType field.

    5     8/05/99 3:12p Tian
    Moved DVDDiskID to start of structure so BS2 can load the disk ID
    directly into it.

    4     8/05/99 11:10a Hashida
    Added FSTMaxLength again!

    3     7/21/99 9:32p Hashida
    Added arenaHi, arenaLo
    Removed FSTMaxSize

    2     7/13/99 12:59p Hashida
    changed the types of FSTLocation and DVDDiskID

    1     7/13/99 11:52a Tian
    Initial check-in.  First cut of OSBootInfo structure.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <revolution/types.h>
#include <revolution/dvd.h>

#ifndef __OSBOOTINFO_H__
#define __OSBOOTINFO_H__

#define OS_BOOTINFO_MAGIC       0x0D15EA5E
#define OS_BOOTINFO_MAGIC_JTAG  0xE5207C22

// The location of this structure is in OSLowMem.h
// This structure must be 32 byte aligned (BS2 will load
// the disk ID directly into here).  As a result, DVDDiskID
// MUST BE THE FIRST MEMBER OF THIS STRUCTURE.

typedef struct OSBootInfo_s
{
    DVDDiskID  DVDDiskID;       // This must ALWAYS be the first member
    u32        magic;
    u32        version;

    u32        memorySize;      // NOTE: BS2 updates this.  Since BS2 is on the
                                // boot rom, you cannot change the position of
                                // this field.
    u32        consoleType;     // NOTE: BS2 updates this.  Since BS2 is on the
                                // boot rom, you cannot change the position of
                                // this field.

    void*      arenaLo;         // if non NULL, overrides __ArenaLo
    void*      arenaHi;         // if non NULL, overrides FSTLocation
    void*      FSTLocation;     // Start address of "FST area"
    u32        FSTMaxLength;    // Length of "FST area"
} OSBootInfo;


#endif // __OSBOOTINFO_H__
