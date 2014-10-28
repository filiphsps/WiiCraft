/*---------------------------------------------------------------------------*
  Project: ENC library
  File:    enc.h

  Copyright 2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: enc.h,v $
  Revision 1.4  08/14/2006 04:30:37  yoshioka_yasuhiro
  Added ENCConvertStringJisToUnicode and ENCConvertStringUnicodeToJis.

  Revision 1.2  08/09/2006 10:36:55  yoshioka_yasuhiro
  Specification change.
  ENCConverString* functions returns a result code,
  and read/write dstlen and srclen.

  Revision 1.1  08/07/2006 09:13:42  yoshioka_yasuhiro
  Initial commit.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef REVOLUTION_ENC_H__
#define REVOLUTION_ENC_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/types.h>

typedef enum
{
    ENC_OK = 0,
    ENC_ERR_NO_BUF_LEFT = -1,
    ENC_ERR_NO_MAP_RULE = -2,
    ENC_ERR_INVALID_PARAM = -3,
    ENC_ERR_INVALID_FORMAT = -4
} ENCResult;

ENCResult ENCSetUnicodeBOM(u16 *dst, s32 dstlen);
ENCResult ENCSetUnicodeBOM32(u32 *dst, s32 dstlen);
ENCResult ENCSetUnicodeBOM16(u16 *dst, s32 dstlen);
ENCResult ENCSetUnicodeBOM8(u8 *dst, s32 dstlen);

ENCResult ENCConvertStringUtf32ToUtf16(u16 *dst, s32 *dstlen, const u32 *src, s32 *srclen);
ENCResult ENCConvertStringUtf16ToUtf32(u32 *dst, s32 *dstlen, const u16 *src, s32 *srclen);

ENCResult ENCConvertStringUtf32ToUtf8(u8 *dst, s32 *dstlen, const u32 *src, s32 *srclen);
ENCResult ENCConvertStringUtf8ToUtf32(u32 *dst, s32 *dstlen, const u8 *src, s32 *srclen);

ENCResult ENCConvertStringUtf16ToUtf8(u8 *dst, s32 *dstlen, const u16 *src, s32 *srclen);
ENCResult ENCConvertStringUtf8ToUtf16(u16 *dst, s32 *dstlen, const u8 *src, s32 *srclen);

ENCResult ENCConvertStringSjisToUnicode(u16 *dst, s32 *dstlen, const u8 *src, s32 *srclen);
ENCResult ENCConvertStringUnicodeToSjis(u8 *dst, s32 *dstlen, const u16 *src, s32 *srclen);

ENCResult ENCConvertStringJisToUnicode(u16 *dst, s32 *dstlen, const u8 *src, s32 *srclen);
ENCResult ENCConvertStringUnicodeToJis(u8 *dst, s32 *dstlen, const u16 *src, s32 *srclen);

ENCResult ENCConvertStringJisToSjis(u8 *dst, s32 *dstlen, const u8 *src, s32 *srclen);
ENCResult ENCConvertStringSjisToJis(u8 *dst, s32 *dstlen, const u8 *src, s32 *srclen);

ENCResult ENCConvertStringLatin1ToUnicode(u16 *dst, s32 *dstlen, const u8 *src, s32 *srclen);
ENCResult ENCConvertStringUnicodeToLatin1(u8 *dst, s32 *dstlen, const u16 *src, s32 *srclen);

#ifdef __cplusplus
} /* extern "C"*/
#endif
#endif /* REVOLUTION_ENC_H__*/
