/*---------------------------------------------------------------------------*
  Project:  SC library
  File:     sc.h

  Copyright 2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: sc.h,v $
  Revision 1.6  08/08/2006 12:42:00  kawaset
  Added SCGetWpadMotorMode, SCGetWpadSensorBarPosition, SCGetWpadSpeakerVolume, SCSetWpadMotorMode, SCSetWpadSensorBarPosition, and SCSetWpadSpeakerVolume.
  Deleted SCEmuSetAspectRatio and SCEmuSetLanguage.

  Revision 1.5  06/01/2006 11:08:35  kawaset
  Deleted timezone.

  Revision 1.4  05/26/2006 12:39:58  kawaset
  Full model change.

  Revision 1.3  02/09/2006 07:26:43  kawaset
  Changed defines.

  Revision 1.2  02/09/2006 01:59:32  kawaset
  Changed SCTimeZoneInfo.

  Revision 1.1  02/03/2006 12:57:04  kawaset
  Initial check-in.


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __SC_H__
#define __SC_H__

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void SCInit(void);

#define SC_STATUS_OK        0
#define SC_STATUS_BUSY      1
#define SC_STATUS_ERROR     2
#define SC_STATUS_INTERNAL3 3 // not returned by SCCheckStatus()

extern u32 SCCheckStatus(void);

typedef void (*SCFlushCallback)(u32 result);

extern u32  SCFlush(void);
extern void SCFlushAsync(SCFlushCallback callback);

#define SC_SOUND_MODE_MONO          0u
#define SC_SOUND_MODE_STEREO        1u
#define SC_SOUND_MODE_SURROUND      2u
#define SC_SOUND_MODE_DEFAULT       SC_SOUND_MODE_STEREO

extern u8 SCGetSoundMode(void);
extern BOOL SCSetSoundMode(u8 mode);

#define SC_LANG_JAPANESE            0u
#define SC_LANG_ENGLISH             1u
#define SC_LANG_GERMAN              2u
#define SC_LANG_FRENCH              3u
#define SC_LANG_SPANISH             4u
#define SC_LANG_ITALIAN             5u
#define SC_LANG_DUTCH               6u

extern u8 SCGetLanguage(void);

#define SC_ASPECT_RATIO_4x3         0u
#define SC_ASPECT_RATIO_16x9        1u
#define SC_ASPECT_RATIO_DEFAULT     SC_ASPECT_RATIO_4x3

extern u8 SCGetAspectRatio(void);

#define SC_PROGRESSIVE_MODE_OFF     0u
#define SC_PROGRESSIVE_MODE_ON      1u
#define SC_PROGRESSIVE_MODE_DEFAULT SC_PROGRESSIVE_MODE_OFF

extern u8 SCGetProgressiveMode(void);
extern BOOL SCSetProgressiveMode(u8 mode);

#define SC_EURGB60_MODE_OFF           0u
#define SC_EURGB60_MODE_ON            1u
#define SC_EURGB60_MODE_DEFAULT       SC_EURGB60_MODE_OFF // temporary

extern u8 SCGetEuRgb60Mode(void);
extern BOOL SCSetEuRgb60Mode(u8 mode);

#define SC_WPAD_MOTOR_MODE_OFF        0u
#define SC_WPAD_MOTOR_MODE_ON         1u
#define SC_WPAD_MOTOR_MODE_DEFAULT    SC_WPAD_MOTOR_MODE_ON

extern u8 SCGetWpadMotorMode(void);
extern BOOL SCSetWpadMotorMode(u8 mode);

#define SC_WPAD_SENSOR_BAR_POSITION_LOWER   0u
#define SC_WPAD_SENSOR_BAR_POSITION_UPPER   1u
#define SC_WPAD_SENSOR_BAR_POSITION_DEFAULT SC_WPAD_SENSOR_BAR_POSITION_LOWER

extern u8 SCGetWpadSensorBarPosition(void);
extern BOOL SCSetWpadSensorBarPosition(u8 position);

#define SC_WPAD_SPEAKER_VOLUME_MIN     0u
#define SC_WPAD_SPEAKER_VOLUME_MAX     127u
#define SC_WPAD_SPEAKER_VOLUME_DEFAULT SC_WPAD_SPEAKER_VOLUME_MAX

extern u8 SCGetWpadSpeakerVolume(void);
extern BOOL SCSetWpadSpeakerVolume(u8 volume);

//////////////////////////////////////////////////////////////////////
// Emulated API (OBSOLETE; they do nothing and return FALSE)
//////////////////////////////////////////////////////////////////////

extern BOOL SCEmuSetAspectRatio(u8 ratio);
extern BOOL SCEmuSetLanguage(u8 language);

#ifdef __cplusplus
}
#endif

#endif // __SC_H__
