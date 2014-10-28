/*---------------------------------------------------------------------------*
  Project:  Dolphin VI library
  File:     vifuncs.h

  Copyright 1998 - 2001 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: vifuncs.h,v $
  Revision 1.6  06/06/2006 14:05:28  urata
  Renamed VI[Set/Get]ProgressiveTest to VI[Set/Get]VSyncTimingTest.

  Revision 1.5  06/06/2006 13:04:27  urata
    Change the return's type of VISetProgressiveTest from "VIRetraceCallback"
    to "void".

  Revision 1.4  06/05/2006 00:21:51  urata
  Change the return's type of VISetProgressiveTest to "VIRetraceCallback"
  from "void".

  Revision 1.3  05/29/2006 13:26:14  urata
  Added VISetProgressiveTest and VIGetProgressiveTest.

  Revision 1.2  2006/02/04 11:56:48  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    10    03/11/19 11:57 Hashida
    Added VIGetScanMode.
    
    9     8/05/02 15:53:00 Shiki
    Added const keyword to the VIConfigure() function prototype.

    8     02/03/14 18:50 Hashida
    Added VIGetNextFrameBuffer and VIGetCurrentFrameBuffer.

    7     7/11/01 5:10p Hashida
    Updated header.

    6     6/25/01 3:29p Hashida
    Added VIGetDTVStatus.

    5     4/28/00 4:26p Carl
    Changed set callback routines to return old callback.

    4     2/25/00 11:30a Hashida
    Added VISetPreRetraceCallback and VISetPostRetraceCallback

    3     2/17/00 4:17p Hashida
    Added VIGetTvFormat

    2     1/28/00 11:01p Hashida
    Added VIFlush().

    1     1/26/00 3:51p Hashida
    initial revision

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __VIFUNCS_H
#define __VIFUNCS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/types.h>
#include <revolution/vi/vitypes.h>
#include <revolution/gx/GXStruct.h>     // for GXRenderModeObj structure


#define VIPadFrameBufferWidth(width)     ((u16)(((u16)(width) + 15) & ~15))

void VIInit                  ( void );
void VIFlush                 ( void );
void VIWaitForRetrace        ( void );

void VIConfigure             ( const GXRenderModeObj* rm );
void VIConfigurePan          ( u16 PanPosX, u16 PanPosY,
                               u16 PanSizeX, u16 PanSizeY );
void VISetNextFrameBuffer    ( void *fb );

void *VIGetNextFrameBuffer   ( void );
void *VIGetCurrentFrameBuffer( void );

VIRetraceCallback VISetPreRetraceCallback  (VIRetraceCallback callback);
VIRetraceCallback VISetPostRetraceCallback (VIRetraceCallback callback);

void VISetBlack              ( BOOL black );
u32  VIGetRetraceCount       ( void );
u32  VIGetNextField          ( void );
u32  VIGetCurrentLine        ( void );
u32  VIGetTvFormat           ( void );
u32  VIGetScanMode           ( void );

u32  VIGetDTVStatus          ( void );

// For test of switch to Progressive from Interlace
void  VISetVSyncTimingTest ( void );
u32   VIGetVSyncTimingTest ( void );


/********************************/
#ifdef __cplusplus
}
#endif

#endif
