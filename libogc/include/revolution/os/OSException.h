/*---------------------------------------------------------------------------*
  Project:  Dolphin OS Exception table
  File:     OSException.h

  Copyright 1998, 1999 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: OSException.h,v $
  Revision 1.2  2006/02/04 11:56:47  hashida
  (none)

  Revision 1.1.1.1  2005/12/29 06:53:28  hiratsu
  Initial import.

  Revision 1.1.1.1  2005/05/12 02:41:07  yasuh-to
  transitioned from the Dolphin source tree

    
    2     01/03/16 17:41 Shiki
    Moved GQR1 to GQR7 to general register context.
    
    9     8/02/99 2:36p Shiki
    Added __OSGetExceptionHandler().

    8     99/07/26 4:01p Shiki
    Removed #include <dolphin/base/PPCArch.h>.

    7     99/07/21 2:29p Shiki
    Removed OS_EXCEPTION_CALLBACK_EXIT macro since it is not necessary any
    more.

    6     99/07/20 10:13p Shiki
    Cleanup.

    5     7/08/99 8:08p Tian
    All exceptions save and restore LR now.

    4     5/11/99 4:43p Shiki
    Refreshed include tree.

    2     5/03/99 5:26p Tianli01
    PPC->EPPC

    1     4/30/99 12:49p Tianli01

    8     4/21/99 8:11p Shiki
    Moved to _DEBUG (avoid DEBUG).

    7     4/21/99 8:10p Shiki
    Detabbed.

    6     4/13/99 5:50p Tianli01
    Added PPCArch.h, added MSR[RI] management to exception handling.

    5     4/12/99 7:46p Tianli01
    Added OSExceptionNames for debugging

    4     4/02/99 5:30p Tianli01
    Fixed minor bug in OS_EXCEPTION_CALLBACK_EXIT.  It now assumes that R4
    is the context pointer and does not clobber it.

    3     4/01/99 7:54p Tianli01
    Added OS_EXCEPTION_CALLBACK_EXIT for easy returns from exceptions that
    invoked callbacks.

    2     3/31/99 6:08p Tianli01
    Changed OSException to __OSException.  Added basic context saving
    helper macros.

    1     3/26/99 2:08p Tianli01
    Broken up from previous OS.h.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __OSEXCEPTION_H__
#define __OSEXCEPTION_H__

#include <revolution/types.h>
#include <revolution/os/OSContext.h>

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
    Exception Handler API
 *---------------------------------------------------------------------------*/

typedef u8   __OSException;
typedef void (*__OSExceptionHandler)(
    __OSException           exception,
    OSContext*              context
);

#define __OS_EXCEPTION_SYSTEM_RESET         0
#define __OS_EXCEPTION_MACHINE_CHECK        1
#define __OS_EXCEPTION_DSI                  2
#define __OS_EXCEPTION_ISI                  3
#define __OS_EXCEPTION_EXTERNAL_INTERRUPT   4
#define __OS_EXCEPTION_ALIGNMENT            5
#define __OS_EXCEPTION_PROGRAM              6
#define __OS_EXCEPTION_FLOATING_POINT       7
#define __OS_EXCEPTION_DECREMENTER          8
#define __OS_EXCEPTION_SYSTEM_CALL          9
#define __OS_EXCEPTION_TRACE                10
#define __OS_EXCEPTION_PERFORMACE_MONITOR   11
#define __OS_EXCEPTION_BREAKPOINT           12
#define __OS_EXCEPTION_SYSTEM_INTERRUPT     13
#define __OS_EXCEPTION_THERMAL_INTERRUPT    14
#define __OS_EXCEPTION_MAX                  \
        (__OS_EXCEPTION_THERMAL_INTERRUPT+1)

// Updates OS exception table, NOT first-level exception vector.
__OSExceptionHandler    __OSSetExceptionHandler(
    __OSException           exception,
    __OSExceptionHandler    handler
);

__OSExceptionHandler    __OSGetExceptionHandler(
    __OSException           exception
);

// Context saving helpers
// For now, use stmw.  Theoretically on 750 it has the same latency
// as pipelined stores.
#ifdef GEKKO
#define OS_EXCEPTION_SAVE_GPRS(context)                 \
    stw     r0, OS_CONTEXT_R0(context)              ;   \
    stw     r1, OS_CONTEXT_R1(context)              ;   \
    stw     r2, OS_CONTEXT_R2(context)              ;   \
    stmw    r6, OS_CONTEXT_R6(context)              ;   \
    /* Save GQR1 to GQR7. GQR0 must always be zero */   \
    mfspr   r0, GQR1                                ;   \
    stw     r0, OS_CONTEXT_GQR1(context)            ;   \
    mfspr   r0, GQR2                                ;   \
    stw     r0, OS_CONTEXT_GQR2(context)            ;   \
    mfspr   r0, GQR3                                ;   \
    stw     r0, OS_CONTEXT_GQR3(context)            ;   \
    mfspr   r0, GQR4                                ;   \
    stw     r0, OS_CONTEXT_GQR4(context)            ;   \
    mfspr   r0, GQR5                                ;   \
    stw     r0, OS_CONTEXT_GQR5(context)            ;   \
    mfspr   r0, GQR6                                ;   \
    stw     r0, OS_CONTEXT_GQR6(context)            ;   \
    mfspr   r0, GQR7                                ;   \
    stw     r0, OS_CONTEXT_GQR7(context)            ;
#else   // !GEKKO                  
#define OS_EXCEPTION_SAVE_GPRS(context)                 \
    stw     r0, OS_CONTEXT_R0(context)              ;   \
    stw     r1, OS_CONTEXT_R1(context)              ;   \
    stw     r2, OS_CONTEXT_R2(context)              ;   \
    stmw    r6, OS_CONTEXT_R6(context)              ;
#endif  // GEKKO

#ifdef __cplusplus
}
#endif

#endif  // __OSEXCEPTION_H__
