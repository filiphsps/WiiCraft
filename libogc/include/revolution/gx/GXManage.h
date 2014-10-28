/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXManage.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXManage.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    11     02/07/24 09:07:00 Hirose
    Resolved version conflicts.
    
    10    3/16/01 7:22p Carl
    Changes for XF stall bug.
    
    9     2/19/01 6:37p Tian
    Added GXResetWriteGatherPipe to clear all extraneous data currently in
    the write gather buffers.
    
    8     10/26/00 2:59p Hirose
    deleted GXDisableBypassBug. Now the setting is automatically done by
    GXInit.
    
    7     10/26/00 10:37a Tian
    Detabbed.  Added GXDisableBypassBug to disable the buggy bypass logic
    on rev B chips.  For testing code that may be hitting the nefarious
    Bypass Bug.
    
    6     7/18/00 12:16p Tian
    Added GXSetResetWritePipe - set to TRUE only for code that requires
    critical fifo alignment
    
    5     4/26/00 4:53p Carl
    CallBacks are now Callbacks.  Set callback routines now return old
    callbacks.  Added gets for fifo objects.
    
    4     3/17/00 4:41p Tian
    Added DrawSync and DrawDone callbacks
    
    3     2/01/00 7:22p Alligator
    second GX update from ArtX
    
    2     12/10/99 4:53p Carl
    Added prototypes for new sync functions.
    
    6     10/26/99 8:05p Alligator
    added Get/Color10S/DrawDone functions
    
    5     10/20/99 11:51a Hirose
    fixed return type of GXReadDrawSync
    
    4     9/23/99 3:27p Tian
    Updated GXInit 
    
    3     9/03/99 2:43p Ryan
    routine update to match man pages
    
    2     8/30/99 11:06a Ryan
    
    1     7/14/99 4:20p Alligator
    split gx.h into individual header files for each major section of API
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXMANAGE_H__
#define __GXMANAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>
#include <revolution/gx/GXFifo.h>

typedef void (*GXDrawSyncCallback)(u16 token);
typedef void (*GXDrawDoneCallback)(void);

/*---------------------------------------------------------------------------*/
GXFifoObj*  GXInit                      ( void* base, u32 size );
void        GXAbortFrame                ( void );

void        GXSetDrawSync               ( u16 token );
u16         GXReadDrawSync              ( void );
GXDrawSyncCallback GXSetDrawSyncCallback( GXDrawSyncCallback cb );

void        GXDrawDone                  ( void );
void        GXSetDrawDone               ( void );
void        GXWaitDrawDone              ( void );
GXDrawDoneCallback GXSetDrawDoneCallback( GXDrawDoneCallback cb );

#ifdef BUG_INDX_ALIGN    
void        GXSetResetWritePipe         ( GXBool tf );
#endif    
void        GXFlush                     ( void );
void        GXResetWriteGatherPipe      ( void );
void        GXPixModeSync               ( void );
void        GXTexModeSync               ( void );

BOOL        IsWriteGatherBufferEmpty    ( void );

void        GXSetMisc                   ( GXMiscToken token, u32 val );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif // __GXMANAGE_H__
