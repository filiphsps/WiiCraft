/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXDraw.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXDraw.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    2     02/07/24 9:06 Hirose
    Resolved version conflicts.
    
    4     9/23/99 5:37p Alligator
    added GenNormalTable func
    
    3     7/20/99 6:30p Alligator
    added new models, all models are normalized, no vtxfmt needed
    
    2     7/16/99 2:04p Alligator
    
    1     7/16/99 1:06p Alligator
    procedural models used in tests
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXDRAW_H__
#define __GXDRAW_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>

void GXDrawCylinder(u8 numEdges);
void GXDrawTorus(f32 rc, u8 numc, u8 numt);
void GXDrawSphere(u8 numMajor, u8 numMinor);
void GXDrawCube(void);
void GXDrawDodeca(void);
void GXDrawOctahedron( void );
void GXDrawIcosahedron( void );
void GXDrawSphere1( u8 depth );
u32  GXGenNormalTable( u8 depth, f32* table );

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif // __GXDRAW_H__
