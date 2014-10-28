/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXGeometry.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXGeometry.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    14    02/08/20 9:58 Hirose
    Included os.h instead of defining prototype of OSPanic locally.
    
    13     02/07/24 09:07:00 Hirose
    Resolved version conflicts.
    
    13    02/04/09 15:15 Hirose
    const type specifier support. (worked by hiratsu@IRD)
    
    12    4/17/01 5:29p Tian
    Changed all inlines to static inline
    
    11    4/04/01 1:10p Carl
    Latest XF bug fix.
    
    10    3/16/01 7:22p Carl
    Changes for XF stall bug.
    
    9     10/18/00 5:44p Hirose
    modified definition rule of GXSetTexCoordGen
    
    8     10/18/00 4:05p Carl
    Latest round of HW2 modifications and minor updates.
    
    7     10/03/00 7:55p Hirose
    Update for HW2(Rev.B) GX API extensions
    
    6     9/29/00 9:51p Hirose
    replaced "MAC" flag by better alternatives
    
    5     7/07/00 6:00p Dante
    PC Compatibility
    
    4     3/27/00 4:59p Danm
    Made GXEnd inline in non-debug builds
    
    3     3/14/00 1:36p Alligator
    changed GXSetTexCoordGen matrix type to u32 so developers can override
    matrix memory map without spurious warnings.
    
    2     3/03/00 4:21p Alligator
    integrate with ArtX source
    
    7     10/29/99 3:35p Hirose
    added GXSetNumTexGens(u8)
    
    6     10/13/99 4:32p Alligator
    change GXSetViewport, GXSetScissor to use xorig, yorig, wd, ht
    
    5     9/30/99 10:40p Yasu
    Renamed some GX functions and enums
    
    4     1/05/98 2:39p Ryan
    routine update to match header file to man pages
    
    3     8/17/99 1:33p Alligator
    added GXSetTexGenEnables function, modified GXTexCoordID enumeration for
    bitwise OR of enables.
    
    2     7/28/99 4:07p Alligator
    update header files and emulator for hw changes
    
    1     7/14/99 4:20p Alligator
    split gx.h into individual header files for each major section of API
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXGEOMETRY_H__
#define __GXGEOMETRY_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
#include <revolution/types.h>
#include <revolution/os.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>

void GXSetVtxDesc           ( GXAttr attr, GXAttrType type );
void GXSetVtxDescv          ( const GXVtxDescList *attrPtr );
void GXClearVtxDesc         ( void );

void GXSetVtxAttrFmt( 
    GXVtxFmt       vtxfmt, 
    GXAttr         attr, 
    GXCompCnt      cnt, 
    GXCompType     type, 
    u8             frac );

void GXSetVtxAttrFmtv       ( GXVtxFmt vtxfmt, const GXVtxAttrFmtList *list );
void GXSetArray             ( GXAttr attr, const void *base_ptr, u8 stride );
void GXBegin                ( GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts );

#if defined(EMU) || defined(WIN32)
void GXEnd                  ( void );
#else // !EMU
static inline void GXEnd           ( void )
{
#ifdef _DEBUG
    extern GXBool __GXinBegin;
    if (!__GXinBegin)
        OSPanic(__FILE__, __LINE__, "GXEnd: called without a GXBegin");
    __GXinBegin = GX_FALSE;
#endif
}
#endif // EMU

#if ( GX_REV != 1 ) // GX revision 2 or later only
void GXSetTexCoordGen2(
    GXTexCoordID     dst_coord,
    GXTexGenType     func,
    GXTexGenSrc      src_param,
    u32              mtx,
    GXBool           normalize,
    u32              postmtx );
#endif // ( GX_REV != 1 )

#if ( GX_REV == 1 || defined(EMU) ) // GX revision 1 or emulator
void GXSetTexCoordGen( 
    GXTexCoordID     dst_coord,
    GXTexGenType     func,
    GXTexGenSrc      src_param,
    u32              mtx );
#else // GX revision 2 or later and real hardware
static inline void GXSetTexCoordGen ( 
    GXTexCoordID    dst_coord,
    GXTexGenType    func,
    GXTexGenSrc     src_param,
    u32             mtx )
{
    GXSetTexCoordGen2(dst_coord, func, src_param, mtx, 
                      GX_FALSE, GX_PTIDENTITY);
}
#endif // ( GX_REV == 1 || defined(EMU) )


void GXSetNumTexGens        ( u8 nTexGens );

void GXInvalidateVtxCache   ( void );
void GXSetLineWidth         ( u8 width, GXTexOffset texOffsets );
void GXSetPointSize         ( u8 pointSize, GXTexOffset texOffsets );
void GXEnableTexOffsets	    ( GXTexCoordID coord, GXBool line_enable, 
			      GXBool point_enable );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif // __GXGEOMETRY_H__
