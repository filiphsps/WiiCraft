/*---------------------------------------------------------------------------*
  Project:  Dolphin Debugger stubs
  File:     db.h

  Copyright 1998, 1999 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: db.h,v $
  Revision 1.2  2006/02/04 11:56:44  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:27  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to
  transitioned from the Dolphin source tree

    
    5     7/13/99 6:37p Tian
    Added DBPrintf...lower level printf that is more robust with EPPC
    serial out.
    
    4     7/08/99 8:05p Tian
    Mods for new debugger/kernel integration
    
    3     5/11/99 4:42p Shiki
    Refreshed include tree.

    1     4/30/99 12:49p Tianli01

    3     4/15/99 2:43p Tianli01
    Beautified.

    2     3/31/99 4:58p Tianli01
    Renamed OSException to __OSException

    1     3/26/99 2:15p Tianli01
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __DB_H__
#define __DB_H__

#include <revolution/types.h>
#include <revolution/os.h>

#ifdef __cplusplus
extern "C" {
#endif

BOOL    DBIsDebuggerPresent         ( void );
void    DBPrintf                    ( char * str, ...);
    

#include <revolution/db/DBInterface.h>

#ifdef __cplusplus
}
#endif

#endif  // __DB_H__
