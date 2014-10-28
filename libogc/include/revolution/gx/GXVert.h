/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXVert.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXVert.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    12     02/07/24 09:08:00 Hirose
    Resolved version conflicts.
    
    11     6/11/01 7:52p Tian
    Integrated SN changes
    
    10     5/07/01 6:45p Tian
    Fixes for SN compiler
    
    9     4/17/01 5:29p Tian
    Changed all inlines to static inline
    
    8     12/15/00 6:23p Stevera
    
    7     12/15/00 5:07p Stevera
    Divided some complex lines up in order to maintain compatibility with
    Visual C++.
    
    6    11/01/00 11:13a Hirose
    flag fix EPPC -> !EMU
    
    5     9/29/00 9:51p Hirose
    replaced "MAC" flag by better alternatives
    
    4     7/07/00 6:00p Dante
    PC Compatibility
    
    3     2/01/00 7:22p Alligator
    second GX update from ArtX
    
    2     1/18/00 1:51p Tian
    Updated GXFIFO_ADDR for MINNOW_MARLIN target
    
    22    11/18/99 3:35p Carl
    Added debug version definitions (for using non-inlined code).
    
    21    11/17/99 6:33p Carl
    Added support for emulator display list creation.
    
    20    11/03/99 6:41p Yasu
    Fix remaining macros
    
    19    11/03/99 6:21p Yasu
    Replace GX*1u8,u16 to GX*1x8,x16
    
    18    10/22/99 4:09p Yasu
    Activate all of Position 2D functions and TexCoord 1D functions 
    
    17    10/19/99 6:44p Yasu
    Delete GXNormal9* functions
    
    16    10/04/99 6:39p Hirose
    fixed GXPackedRGB5A3 to match 8-level alpha implementation
    
    15    9/23/99 4:12p Hirose
    added (u16) cast to GX Packed Color format macros
    
    14    9/21/99 4:59p Alligator
    added 9 element normals
    
    13    9/01/99 11:35a Ryan
    
    12    8/24/99 8:49p Yasu
    Add RGBA packing macros.
    
    11    8/21/99 2:55p Yasu
    Append entries of GXPosition2* and GXTexCoord1*.
    
    10    8/18/99 1:32a Shiki
    Changed fifo address to the final address (0xCC008000).

    9     7/29/99 3:52p Yasu
    Add GXMatrixIndex1u8(u8) in EPPC section.

    8     7/23/99 12:30p Alligator
    fixed pnmtx index per vertex emulation

    7     7/16/99 2:57p Alligator
    changed fifo address to 0xa0000000 to trap exceptions

    6     7/16/99 2:32p Alligator
    use GXVertex for debug and non-debug version of EPPC library for now.

    5     7/16/99 1:24p Alligator
    put wgpipe address depends only on EPPC flag

    4     7/14/99 9:19p Yoshya01
    Append inline Vertex API functions for EPPC.

    3     6/04/99 2:46p Ryan

    2     6/03/99 3:16p Ryan

    1     6/01/99 2:04p Ryan

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXVERT_H__
#define __GXVERT_H__

#ifdef WIN32
#include <win32/win32.h>
#endif

// NOTE:  This file closely mirrors GXVert.c.
//        Don't change this file without considering that one too,
//        and vice-versa.

/********************************/
#ifdef __cplusplus
extern "C" {
#endif

/*>*******************************(*)*******************************<*/
#ifndef EMU // real hardware
/*---------------------------------------------*
 * Write gather pipe for GFXFifo               *
 *---------------------------------------------*/
#ifndef MINNOW
#define   GXFIFO_ADDR   0xCC008000
#else // MINNOW
#define   GXFIFO_ADDR   0x1C008000
#endif// MINNOW

#include  <revolution/base/PPCWGPipe.h>
// SN-Phil: removed 'extern', added AT_ADDRESS
volatile PPCWGPipe GXWGFifo AT_ADDRESS(GXFIFO_ADDR) ;

#endif // !EMU
/*---------------------------------------------------------------------------*/

#if defined(EMU) || defined(WIN32)
/*---------------------------------------------*
 * Display list support for emulator           *
 *---------------------------------------------*/

#include <revolution/gx/GXEmVert.h>

extern u8* __EmBuffPtr;
extern u8* __EmBuffTop;
extern GXBool __EmDisplayListInProgress;

#endif // EMU

/*---------------------------------------------------------------------------*/
/*---------------------------------------------*
 * GXVertex functions                          *
 *---------------------------------------------*/
//-------------------------------
// Define gfx function templates
//-------------------------------
//
// Templates syntax:
//  __GXCDEF (function_prefix, num_of_components, component_type)
//  __GXCDEFX(function_name, num_of_comps, src_comp_type, dest_comp_type)
//
#define __GXCDEF(prfx,n,t)  __GXCDEF##n(prfx##n##t,t,t)
#define __GXCDEFX(func,n,t) __GXCDEF##n(func,t,t)

#ifdef _DEBUG

// 1 component
#define __GXCDEF1(func,ts,td) \
    void func(const ts x);

// 2 components
#define __GXCDEF2(func,ts,td) \
    void func(const ts x, const ts y);

// 3 components
#define __GXCDEF3(func,ts,td) \
    void func(const ts x, const ts y, const ts z);

// 4 components
#define __GXCDEF4(func,ts,td) \
    void func(const ts x, const ts y, const ts z, const ts w);


#else // ifdef _DEBUG
/*---------------------------------------------*
 * For emulator                                *
 *---------------------------------------------*/
#if defined(EMU)

// 1 component
#define __GXCDEF1(func,ts,td) \
    static inline void func(const ts x)  \
    {                             \
        if (__EmDisplayListInProgress) { \
			*((td *) __EmBuffPtr) = (td) x; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
        } else {                  \
            Em##func(x);          \
        }                         \
        return;                   \
    }

// 2 components
#define __GXCDEF2(func,ts,td) \
    static inline void func(const ts x, const ts y) \
    {                             \
        if (__EmDisplayListInProgress) { \
			*((td *) __EmBuffPtr) = (td) x; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
			*((td *) __EmBuffPtr) = (td) y; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
        } else {                  \
            Em##func(x, y);       \
        }                         \
        return;                   \
    }

// 3 components
#define __GXCDEF3(func,ts,td) \
    static inline void func(const ts x, const ts y, const ts z) \
    {                             \
        if (__EmDisplayListInProgress) { \
			*((td *) __EmBuffPtr) = (td) x; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
			*((td *) __EmBuffPtr) = (td) y; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
			*((td *) __EmBuffPtr) = (td) z; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
        } else {                  \
            Em##func(x, y, z);    \
        }                         \
        return;                   \
    }

// 4 components
#define __GXCDEF4(func,ts,td) \
    static inline void func(const ts x, const ts y, const ts z, const ts w) \
    {                             \
        if (__EmDisplayListInProgress) { \
			*((td *) __EmBuffPtr) = (td) x; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
			*((td *) __EmBuffPtr) = (td) y; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
			*((td *) __EmBuffPtr) = (td) z; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
			*((td *) __EmBuffPtr) = (td) w; \
			__EmBuffPtr = __EmBuffPtr + sizeof(td); \
        } else {                  \
            Em##func(x, y, z, w); \
        }                         \
        return;                   \
    }

#endif // ifdef EMU

/*---------------------------------------------*
 * For real hardware                           *
 *---------------------------------------------*/
#ifndef EMU

// 1 component
#define __GXCDEF1(func,ts,td) \
    static inline void func(const ts x) \
    {                         \
        GXWGFifo.td = (td) x; \
        return;               \
    }

// 2 components
#define __GXCDEF2(func,ts,td) \
    static inline void func(const ts x, const ts y) \
    {                         \
        GXWGFifo.td = (td) x; \
        GXWGFifo.td = (td) y; \
        return;               \
    }

// 3 components
#define __GXCDEF3(func,ts,td) \
    static inline void func(const ts x, const ts y, const ts z) \
    {                         \
        GXWGFifo.td = (td) x; \
        GXWGFifo.td = (td) y; \
        GXWGFifo.td = (td) z; \
        return;               \
    }

// 4 components
#define __GXCDEF4(func,ts,td) \
    static inline void func(const ts x, const ts y, const ts z, const ts w) \
    {                         \
        GXWGFifo.td = (td) x; \
        GXWGFifo.td = (td) y; \
        GXWGFifo.td = (td) z; \
        GXWGFifo.td = (td) w; \
        return;               \
    }

#endif // ifndef EMU

#endif // ifdef _DEBUG else

//---------------------------
// Generate inline functions
//---------------------------
//---- GXCmd[n][t] ----
__GXCDEF( GXCmd, 1, u8  )
__GXCDEF( GXCmd, 1, u16 )
__GXCDEF( GXCmd, 1, u32 )

//---- GXParam[n][t] ----
__GXCDEF( GXParam, 1, u8  )
__GXCDEF( GXParam, 1, u16 )
__GXCDEF( GXParam, 1, u32 )
__GXCDEF( GXParam, 1, s8  )
__GXCDEF( GXParam, 1, s16 )
__GXCDEF( GXParam, 1, s32 )
__GXCDEF( GXParam, 1, f32 )
__GXCDEF( GXParam, 3, f32 ) // for light
__GXCDEF( GXParam, 4, f32 ) // for matrix

//---- GXPosition[n][t] ----
  // for GX_POS_XYZ
__GXCDEF( GXPosition, 3, f32 )
__GXCDEF( GXPosition, 3, u8  )
__GXCDEF( GXPosition, 3, s8  )
__GXCDEF( GXPosition, 3, u16 )
__GXCDEF( GXPosition, 3, s16 )
  // for GX_POS_XY
__GXCDEF( GXPosition, 2, f32 )
__GXCDEF( GXPosition, 2, u8  )
__GXCDEF( GXPosition, 2, s8  )
__GXCDEF( GXPosition, 2, u16 )
__GXCDEF( GXPosition, 2, s16 )
  // for Index
__GXCDEFX( GXPosition1x16, 1, u16 )
__GXCDEFX( GXPosition1x8,  1, u8  )

//---- GXNormal[n][t] ----
  // for GX_NRM or GX_NBT
__GXCDEF( GXNormal, 3, f32 )
__GXCDEF( GXNormal, 3, s16 )
__GXCDEF( GXNormal, 3, s8  )
  // for Index
__GXCDEFX( GXNormal1x16, 1, u16 )
__GXCDEFX( GXNormal1x8,  1, u8  )

//---- GXColor[n][t] ----
  // for GX_CLR_RGBA8 or RGBX8
__GXCDEF( GXColor, 4, u8  )
__GXCDEF( GXColor, 1, u32 )
  // for GX_CLR_RGBA6 or RGB8
__GXCDEF( GXColor, 3, u8  )
  // for GX_CLR_RGBA4 or RGB565
__GXCDEF( GXColor, 1, u16 )
  // for Index
__GXCDEFX( GXColor1x16, 1, u16 )
__GXCDEFX( GXColor1x8,  1, u8  )

//---- GXTexCoord[n][t] ----
  // for GX_TEX_ST
__GXCDEF( GXTexCoord, 2, f32 )
__GXCDEF( GXTexCoord, 2, s16 )
__GXCDEF( GXTexCoord, 2, u16 )
__GXCDEF( GXTexCoord, 2, s8  )
__GXCDEF( GXTexCoord, 2, u8  )
  // for GX_TEX_S
__GXCDEF( GXTexCoord, 1, f32 )
__GXCDEF( GXTexCoord, 1, s16 )
__GXCDEF( GXTexCoord, 1, u16 )
__GXCDEF( GXTexCoord, 1, s8  )
__GXCDEF( GXTexCoord, 1, u8  )
  // for Index
__GXCDEFX( GXTexCoord1x16, 1, u16 )
__GXCDEFX( GXTexCoord1x8,  1, u8  )

//---- GXMatrixIndex* ----
// GXMatrixIndex1u8
__GXCDEF( GXMatrixIndex, 1, u8 )
#define GXMatrixIndex1x8    GXMatrixIndex1u8

//------------------------
// Undefine all templates
//------------------------
#undef  __GXCDEF
#undef  __GXCDEFX
#undef  __GXCDEF1
#undef  __GXCDEF2
#undef  __GXCDEF3
#undef  __GXCDEF4

/*---------------------------------------------------------------------------*/
// Packing macro for a several color format
#define	GXPackedRGB565(r,g,b)   \
	((u16)((((r)&0xf8)<<8)|(((g)&0xfc)<<3)|(((b)&0xf8)>>3)))
#define	GXPackedRGBA4(r,g,b,a)  \
	((u16)((((r)&0xf0)<<8)|(((g)&0xf0)<<4)|(((b)&0xf0)   )|(((a)&0xf0)>>4)))
#define	GXPackedRGB5A3(r,g,b,a) \
	((u16)((a)>=224 ? \
	((((r)&0xf8)<<7)|(((g)&0xf8)<<2)|(((b)&0xf8)>>3)|(1<<15)): \
	((((r)&0xf0)<<4)|(((g)&0xf0)   )|(((b)&0xf0)>>4)|(((a)&0xe0)<<7))))

#ifdef __cplusplus
}
#endif

#endif  // __GXVERT_H__
