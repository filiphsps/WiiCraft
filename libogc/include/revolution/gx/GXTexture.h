/*---------------------------------------------------------------------------*
  Project:  Dolphin GX library
  File:     GXTexture.h

  Copyright 1998-2003 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: GXTexture.h,v $
  Revision 1.2  2006/02/04 11:56:46  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    12    03/04/10 21:08 Hirose
    Added const specifier to texture-load related functions.
    
    10     02/07/24 09:07:00 Hirose
    Resolved version conflicts.
    
    11    02/04/09 15:15 Hirose
    const type specifier support. (worked by hiratsu@IRD)
    
    10    02/03/01 17:11 Hirose
    Added new independent GXInitTexObj* functions.
    
    9     1/24/01 4:28p Carl
    New texture init and get functions added.
    
    8     1/18/01 12:21p Carl
    Changes related to __GXSetSUTexRegs modifications.
    Added GXSetTexCoordBias.
    
    7     7/14/00 3:01p Carl
    Added GXSetTexCoordCylWrap
    
    6     5/03/00 3:41p Carl
    Added GXSetTexCoordScaleManually prototype.
    
    5     4/26/00 4:53p Carl
    CallBacks are now Callbacks.  Set callback routines now return old
    callbacks.  Added gets for fifo objects.
    
    4     1/13/00 5:55p Alligator
    integrate with ArtX GX library code
    
    3     12/07/99 7:44p Hirose
    added GXInitTexCacheRegion and GXInitTexPreloadRegion
    
    2     99/12/02 8:13p Hirose
    changed prototype of GXTexRegionCallBack
    
    13    10/13/99 5:21p Alligator
    add 32b mipmap flag to GXInitTexRegion
    
    12    10/12/99 11:14a Hirose
    deleted TlutObjUserData functions
    
    11    10/04/99 6:47p Yasu
    Rename -Sz to -Size
    
    10     9/30/99 10:40p Yasu
    Renamed some GX functions and enums
    
    9     9/22/99 10:38p Hirose
    added prototype of GXGetTexBufferSize
    
    8     9/21/99 9:10p Hirose
    deleted t_obj parameter of GXTlutRegionCallBack
    
    7     9/21/99 5:50p Hirose
    changed return value type of GXLoadTlut to void from u32
    
    6     9/17/99 6:35p Hirose
    changed parameters of GXInitTlutObj and GXLoadTlut
    
    5     9/01/99 2:49p Ryan
    
    3     8/17/99 12:02p Alligator
    updated to reflect arbitrary tlut size
    
    2     8/11/99 9:01p Hirose
    added GXInvalidateTexAll()
    
    1     7/14/99 4:20p Alligator
    split gx.h into individual header files for each major section of API
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __GXTEXTURE_H__
#define __GXTEXTURE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>

typedef GXTexRegion*  (*GXTexRegionCallback) (const GXTexObj* t_obj, GXTexMapID id);
typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 idx);

/*---------------------------------------------------------------------------*/
void GXInitTexObj(
         GXTexObj*      obj,
         void*          image_ptr,
         u16            width,
         u16            height,
         GXTexFmt       format,
         GXTexWrapMode  wrap_s,
         GXTexWrapMode  wrap_t,
         GXBool         mipmap);

void GXInitTexObjCI(
         GXTexObj*      obj,
         void*          image_ptr,
         u16            width,
         u16            height,
         GXCITexFmt     format,
         GXTexWrapMode  wrap_s,
         GXTexWrapMode  wrap_t,
         GXBool         mipmap,
         u32            tlut_name);

void GXInitTexObjLOD(
         GXTexObj*      obj,
         GXTexFilter    min_filt,
         GXTexFilter    mag_filt,
         f32            min_lod,
         f32            max_lod,
         f32            lod_bias,
         GXBool         bias_clamp,
         GXBool         do_edge_lod,
         GXAnisotropy   max_aniso );

void  GXInitTexObjData     ( GXTexObj* obj, void* image_ptr );
void  GXInitTexObjWrapMode ( GXTexObj* obj, GXTexWrapMode s, GXTexWrapMode t );
void  GXInitTexObjTlut     ( GXTexObj* obj, u32 tlut_name );
void  GXInitTexObjFilter   ( GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt );
void  GXInitTexObjMaxLOD   ( GXTexObj* obj, f32 max_lod );
void  GXInitTexObjMinLOD   ( GXTexObj* obj, f32 min_lod );
void  GXInitTexObjLODBias  ( GXTexObj* obj, f32 lod_bias );
void  GXInitTexObjBiasClamp( GXTexObj* obj, GXBool bias_clamp );
void  GXInitTexObjEdgeLOD  ( GXTexObj* obj, GXBool do_edge_lod );
void  GXInitTexObjMaxAniso ( GXTexObj* obj, GXAnisotropy max_aniso );


void  GXInitTexObjUserData ( GXTexObj* obj, void* user_data );
void* GXGetTexObjUserData  ( const GXTexObj* obj );

void  GXLoadTexObj         ( const GXTexObj* obj, GXTexMapID id );

u32   GXGetTexBufferSize(
          u16           width,
          u16           height,
          u32           format,
          GXBool        mipmap,
          u8            max_lod );

void GXInitTlutObj(
         GXTlutObj* tlut_obj,
         void*      lut,
         GXTlutFmt  fmt,
         u16        n_entries );

void GXLoadTlut             ( const GXTlutObj* tlut_obj, u32 tlut_name );

void GXInitTexCacheRegion(
         GXTexRegion*      region,
         GXBool            is_32b_mipmap,
         u32               tmem_even,
         GXTexCacheSize    size_even,
         u32               tmem_odd,
         GXTexCacheSize    size_odd );

void GXInitTexPreLoadRegion(
         GXTexRegion*      region,
         u32               tmem_even,
         u32               size_even,
         u32               tmem_odd,
         u32               size_odd );

void GXInitTlutRegion(
         GXTlutRegion*     region,
         u32               tmem_addr,
         GXTlutSize        tlut_size );

void GXInvalidateTexRegion  ( const GXTexRegion* region );
void GXInvalidateTexAll     ( void );
void GXPreLoadEntireTexture ( const GXTexObj* tex_obj, const GXTexRegion* region );

GXTexRegionCallback  GXSetTexRegionCallback ( GXTexRegionCallback f );
GXTlutRegionCallback GXSetTlutRegionCallback( GXTlutRegionCallback f );

void GXLoadTexObjPreLoaded(
         const GXTexObj*    obj, 
         const GXTexRegion* region, 
         GXTexMapID         id );

void GXSetTexCoordScaleManually(GXTexCoordID coord,
                                GXBool enable,
                                u16 ss, u16 ts);

void GXSetTexCoordCylWrap(GXTexCoordID coord,
                          GXBool s_enable,
                          GXBool t_enable);

void GXSetTexCoordBias(GXTexCoordID coord,
                       GXBool s_enable,
                       GXBool t_enable);

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif // __GXTEXTURE_H__
