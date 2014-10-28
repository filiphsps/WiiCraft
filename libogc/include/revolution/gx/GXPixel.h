/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXPixel.h

  Copyright 1998-2003 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXPixel.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    6     03/09/26 16:56 Hirose
    Added GXSetFogColor().
    
    5     02/07/24 09:07:00 Hirose
    Resolved version conflicts.
    
    5     02/04/09 15:15 Hirose
    const type specifier support. (worked by hiratsu@IRD)
    
    4     4/26/00 4:09p Alligator
    add parameter to GXSetFieldMode
    
    3     4/19/00 2:38p Carl
    Added GXSetFieldMode (ArtX update).
    
    2     12/10/99 4:53p Carl
    Fixed Z compare stuff.
    
    10    10/13/99 5:19p Alligator
    change GXSetMotionComp to GXSetFieldMask
    
    9     10/04/99 2:42p Yasu
    Add GXInitFogAdjTable
    
    8     9/30/99 10:40p Yasu
    Renamed some GX functions and enums
    
    7     9/29/99 6:29p Alligator
    added width parameter to GXSetFogRangeAdj
    
    6     9/02/99 10:57a Ryan
    
    5     9/01/99 5:45p Ryan
    
    4     8/27/99 2:25p Yasu
    Change a parameter of GXSetBlendMode, GXSetZMode.
    Append GXSetZUpdate, GXSetAlphaUpdate and GXSetDither.
    
    3     8/26/99 2:37p Yasu
    Delete a parameter of density in GXSetFog().
    Change a function name GXSetColorMode -> GXSetBlendMode
    
    2     7/28/99 4:07p Alligator
    update header files and emulator for hw changes
    
    1     7/14/99 4:20p Alligator
    split gx.h into individual header files for each major section of API
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXPIXEL_H__
#define __GXPIXEL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>

/*---------------------------------------------------------------------------*/
void GXSetFog(	GXFogType	type,
		f32		startz,
		f32		endz,
		f32		nearz,
		f32		farz,
		GXColor		color );

void GXSetFogColor( GXColor color );

void GXInitFogAdjTable( GXFogAdjTable* table, u16 width, const f32 projmtx[4][4] );

void GXSetFogRangeAdj( GXBool enable, u16 center, const GXFogAdjTable* table );

void GXSetBlendMode (	GXBlendMode	type,
			GXBlendFactor	src_factor, 
			GXBlendFactor	dst_factor, 
			GXLogicOp	op );

void GXSetColorUpdate( GXBool update_enable );
void GXSetAlphaUpdate( GXBool update_enable );
void GXSetZMode(	GXBool		compare_enable,
			GXCompare	func,
			GXBool		update_enable );

void GXSetZCompLoc( GXBool before_tex );
void GXSetPixelFmt ( GXPixelFmt pix_fmt, GXZFmt16 z_fmt );
void GXSetDither( GXBool dither );
void GXSetDstAlpha( GXBool enable, u8 alpha );
void GXSetFieldMask( GXBool odd_mask, GXBool even_mask );
void GXSetFieldMode( GXBool field_mode, GXBool half_aspect_ratio );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __GXPIXEL_H__

#endif
