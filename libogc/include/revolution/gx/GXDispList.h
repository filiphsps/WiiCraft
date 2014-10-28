/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXDispList.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXDispList.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    4     02/07/24 9:06 Hirose
    Resolved version conflicts.
    
    5     02/04/10 13:12 Hirose
    constantized GXFastCallDisplayList also.
    
    4     02/04/09 15:14 Hirose
    const type specifier support. (worked by hiratsu@IRD)
    
    3     6/11/01 9:08p Tian
    Made GXFastCallDisplayList static inline
    
    2     5/22/01 8:08p Carl
    Added GXFastCallDisplayList.
    
    4     11/10/99 3:59p Tian
    Updated GXEndDisplayList API
    
    3     9/02/99 11:04a Ryan
    
    2     7/28/99 4:07p Alligator
    update header files and emulator for hw changes
    
    1     7/14/99 4:20p Alligator
    split gx.h into individual header files for each major section of API
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXDISPLIST_H__
#define __GXDISPLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
#include <revolution/types.h>

/*---------------------------------------------------------------------------*/
void GXBeginDisplayList		( void *list, u32 size );
u32  GXEndDisplayList		( void );
void GXCallDisplayList		( const void *list, u32 nbytes );

#ifndef EMU
// Note: GXCommandList.h and GXVert.h must be #included first

// Note: This function can only be used in certain situations.
//       There must be no dirty state pending.  Thus this function
//       is safe when called after a GXCallDisplayList or GXEnd call
//       (without any other GX calls in between).  It is also safe to
//       call this function multiple times in a row.
//       Please refer to the online man page for complete details.

// Note: No error checking is done; be careful!

static inline void GXFastCallDisplayList ( const void *list, u32 nbytes )
    {
        GXWGFifo.u8  = (u8) GX_CMD_CALL_DL;
        // XXX UNSAFE: Assumes GP ignores all extra padding/unused bits.
        GXWGFifo.u32 = (u32) list;
        GXWGFifo.u32 = (u32) nbytes;
    }
#else
static inline void GXFastCallDisplayList ( const void *list, u32 nbytes )
    { GXCallDisplayList( list, nbytes ); }
#endif

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif // __GXDISPLIST_H__
