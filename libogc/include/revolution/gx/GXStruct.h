/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXStruct.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXStruct.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    11    02/08/12 17:01 Hirose
    Turned off padding warnings in this header file.
    
    10     02/07/24 09:07:00 Hirose
    Resolved version conflicts.
    
    9     5/10/01 9:43p Hirose
    added tag for each structure definition
    
    8     1/24/01 5:09p Carl
    Fixed texobj, texregion for emulator.
    
    7     1/19/01 7:54p Carl
    Optimized TexObjs and TexRegions.
    
    6     10/30/00 6:26p Carl
    Had to enlarge GXTlutRegion to accommodate change in tlut data.
    
    5     4/04/00 11:17a Alligator
    moved constants from GXStruct.h to GXEnum.h since they are dependent on
    enumerated values.
    
    4     3/13/00 6:18p Danm
    Fixed AA sampling locations to use x,y pairs.
    
    3     1/26/00 4:06p Hashida
    Include vitypes.h instead of vi.h
    
    2     1/13/00 5:55p Alligator
    integrate with ArtX GX library code
    
    18    11/17/99 10:23p Hirose
    changed size of some structures
    
    17    11/16/99 6:17p Alligator
    
    16    11/15/99 4:42p Hirose
    changed size of GXTexObj and GXTexRegion
    
    15    10/26/99 8:04p Alligator
    added s10-bit color
    
    14    10/24/99 7:42a Yasu
    Add GX_MAX_TEXMAP
    
    13    10/22/99 4:07p Yasu
    Add definitions of HW information
    
    12    10/11/99 10:20a Hirose
    changed size of GXTexObj
    
    11     10/04/99 2:42p Yasu
    Add GXInitFogAdjTable
    
    10    9/21/99 2:33p Alligator
    add aa flag, if aa set 16b pix format
    
    9     9/21/99 11:49a Hirose
    changed GXTlutRegion size
    
    8     9/17/99 3:38p Hirose
    changed GXTlutObj size
    
    7     9/16/99 3:49p Alligator
    
    6     9/16/99 3:42p Alligator
    update render mode api
    
    5     9/09/99 3:04p Alligator
    move GXSetRenderMode to GX lib from emu
    
    4     9/02/99 3:18p Ryan
    Made Frame Buffer Api changes
    
    3     9/01/99 2:27p Ryan
    Added temp GXTesRegion and GXTlutRegion structs
    
    2     7/20/99 6:10p Alligator
    added GXGetVtxDescv, GXGetVtxAttrFmtv
    
    1     7/14/99 4:20p Alligator
    split gx.h into individual header files for each major section of API
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXSTRUCT_H__
#define __GXSTRUCT_H__

/********************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************************/
#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/vi/vitypes.h>

/*---------------------------------------------------------------------------*/

#ifdef __MWERKS__
#pragma warn_padding    off
#endif // __MWERKS__

/*---------------------------------------------------------------------------*/

/********************************/
typedef struct _GXColor
{
    u8  r,
        g, 
        b, 
        a;

} GXColor;

typedef struct _GXColorS10
{
    s16    r, g, b, a; // s10-bit components for Tev constant color
} GXColorS10;

/********************************/
typedef struct _GXTexObj
{
#ifdef EMU
    u32 dummy[16]; // emulator version
#else
    u32 dummy[8];  // real hardware version
#endif    
} GXTexObj;

/********************************/
typedef struct _GXTlutObj
{
    u32 dummy[3];
    
} GXTlutObj;

/********************************/
typedef struct _GXLightObj
{
    u32 dummy[16];
    
} GXLightObj;

/********************************/
typedef struct _GXVtxAttrFmtList
{
    GXAttr        attr;
    GXCompCnt     cnt;
    GXCompType    type;
    u8            frac;
    
} GXVtxAttrFmtList;

/********************************/
typedef struct _GXTexRegion
{
#ifdef EMU
    u32 dummy[8]; // emulator version
#else
    u32 dummy[4]; // real hardware version
#endif
} GXTexRegion;

/********************************/
typedef struct _GXTlutRegion
{
    u32 dummy[4];
    
} GXTlutRegion;

/********************************/
typedef struct _GXVtxDescList
{
    GXAttr        attr;
    GXAttrType    type;
    
} GXVtxDescList;

/********************************/
typedef struct _GXRenderModeObj
{
    VITVMode          viTVmode;
    u16               fbWidth;   // no xscale from efb to xfb
    u16               efbHeight; // embedded frame buffer
    u16               xfbHeight; // external frame buffer, may yscale efb
    u16               viXOrigin;
    u16               viYOrigin;
    u16               viWidth;
    u16               viHeight;
    VIXFBMode         xFBmode;   // whether single-field or double-field in 
                                 // XFB.
    u8                field_rendering;    // rendering fields or frames?
    u8                aa;                 // anti-aliasing on?
    u8                sample_pattern[12][2]; // aa sample pattern
    u8                vfilter[7];         // vertical filter coefficients
} GXRenderModeObj;

/********************************/
typedef struct _GXFogAdjTable
{
    u16			r[10];
} GXFogAdjTable;

/********************************/

/*---------------------------------------------------------------------------*/

#ifdef __MWERKS__
#pragma warn_padding    reset
#endif // __MWERKS__

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif
