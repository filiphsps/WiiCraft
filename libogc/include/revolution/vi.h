/*---------------------------------------------------------------------------*
  Project:  Dolphin VI library
  File:     vi.h

  Copyright 1998, 1999 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: vi.h,v $
  Revision 1.3  02/25/2006 09:59:26  urata
  Added "vi3in1.h" and "vi3in1types.h".

  Revision 1.2  2006/02/04 11:56:44  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:27  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    2     1/26/00 3:51p Hashida
    Divided into two header files, one if for define's and the other for
    function prototypes.
    
    15    11/17/99 5:04p Hashida
    Added a debug mode.
    
    14    11/17/99 3:30p Hashida
    Added a debug mode.
    
    13    11/12/99 5:21p Hashida
    Added VIGetCurrentLine().
    
    12    10/06/99 11:02a Hashida
    Removed the old enum and prototypes.
    
    11    9/29/99 6:17p Hashida
    Changed the definition of VI_TVMODE_* so that it can be used easily.
    
    10    9/16/99 11:09a Hashida
    Removed VISetRetraceCount stub.
    
    9     9/15/99 9:06p Hashida
    Changed a function name (VIGetCurrentFieldCount -> VIGetRetraceCount).
    Added VIGetNextField.
    
    8     9/13/99 3:21p Hashida
    Added VISetBlack and VIGetCurrentFieldCount
    
    7     9/10/99 11:20a Hashida
    Added VIPadFrameBufferWidth, VIConfigurePan, VISetNextFrameBuffer and
    VISetRetraceCount
    
    6     9/10/99 10:26a Hashida
    Changed VIDispMode to VITVMode
    
    5     9/09/99 11:04p Hashida
    Added VIConfigureTVScreen and VIConfigureXFrameBuffer.
    
    4     7/20/99 2:14p Rod
    Added an enum value for the VI_COUNT to make the app run a max frame
    rate ( no clamping )
    
    3     7/20/99 2:11p Rod
    Added a function ( VISetCount) to clamp the refresh rate to a set
    maximum
    
    2     6/07/99 4:34p Alligator
    change fn name to VISetFrameBuffer
    
    1     6/01/99 2:04p Ryan

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __VI_H
#define __VI_H

#include <revolution/vi/vitypes.h>
#include <revolution/vi/vifuncs.h>
#include <revolution/vi/vi3in1.h>
#include <revolution/vi/vi3in1types.h>

#endif
