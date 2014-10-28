/*---------------------------------------------------------------------------*
  Project:     compress/uncompress library
  File:        CXStreamingUncompression.h

  Copyright 2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: CXStreamingUncompression.h,v $
  Revision 1.11  07/27/2006 07:40:19  takano_makoto
  Add const modifier to CXIsFinishedUncompXXX parameter.

  Revision 1.10  07/27/2006 04:25:12  takano_makoto
  Change Condition of CXIsFinishedUncompXXX()

  Revision 1.9  07/27/2006 04:12:14  takano_makoto
  Change Interface of CXInitUncompContextXXX()
  Change Parameter type u8* to void*

  Revision 1.8  07/12/2006 01:11:41  takano_makoto
  fix comment

  Revision 1.7  07/10/2006 08:38:17  takano_makoto
  Added CXIsFinishedUncompXXX() to determine when streaming decompression is complete
  Changed the spec for CXReadUncompXXX() to include header in passed data
  (for a simplified interface)

  Revision 1.6  07/06/2006 09:19:14  takano_makoto
  Changed the include guard to the REVOLUTION_SDK format

  Revision 1.5  07/06/2006 04:40:14  takano_makoto
  changed RL8 and LZ8 to RL and ZL

  Revision 1.4  07/05/2006 11:14:43  takano_makoto
  revised the include guard

  Revision 1.3  07/05/2006 08:13:36  takano_makoto
  revised comments
  deleted context members only needed for 16 bit access functions

  Revision 1.2  07/04/2006 08:26:20  takano_makoto
  changed the prefix from the DS version

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#ifndef __CX_STREAMING_UNCOMPRESSION_STREAM_H__
#define __CX_STREAMING_UNCOMPRESSION_STREAM_H__

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    u8 *destp;                         // Write-destination pointer               4B
    s32 destCount;                     // Remaining size to write                 4B
    u16 length;                        // Remaining size of continuous write  2B
    u8  flags;                         // Compression flag                       1B
    u8  headerSize;                    // Size of header being read                 1B
                                       //                         Total is 12B
}
CXUncompContextRL;


typedef struct
{
    u8 *destp;                         // Write-destination pointer               4B
    s32 destCount;                     // Remaining size to write                 4B
    u8  flags;                         // Compression flag                       1B
    u8  flagIndex;                     // Current compression flag index         1B
    u8  length;                        // Remaining length of continuous write   1B
    u8  lengthFlg;                     // Length-acquired flag                   1B
    u8  headerSize;                    // Size of header being read                 1B
    u8  padding_[1];                   //                                 3B
                                       //                             Total is 16B
}
CXUncompContextLZ;


typedef struct
{
    u8 *destp;                         // Write-destination pointer               4B
    s32 destCount;                     // Remaining size to write                 4B
    u8 *treep;                         // Huffman encoding table, current pointer   4B
    u32 srcTmp;                        // Data being read                         4B
    u32 destTmp;                       // Data being decoded                      4B
    s16 treeSize;                      // Size of Huffman encoding table          2B
    u8  srcTmpCnt;                     // Size of data being read                 1B
    u8  destTmpCnt;                    // Number of bits that have been decoded   1B
    u8  bitSize;                       // Size of encoded bits                    1B
    u8  headerSize;                    // Size of header being read                 1B
    u8  padding_[2];                   //                                        2B
    u8  tree[0x200];                   // Huffman encoding table                512B (32B is OK if 4bit encoding, but allocated enough for 8bit encoding)   
                                       //                                   Total = 540B   (60B sufficient if 4bit encoding)   
}
CXUncompContextHuffman;

/*---------------------------------------------------------------------------*
  Name: CXInitUncompContextRL

  Description: Initializes the streaming uncompression context for run-length
                compressed data

  Arguments: context Pointer to the run-length uncompressed context
                dest        Destination address for uncompressed data
                header		a pointer to the leading data for the compressed data

  Returns: Can get the data size after decompression.

 *---------------------------------------------------------------------------*/
void CXInitUncompContextRL( CXUncompContextRL          *context, 
                            void                       *dest );

/*---------------------------------------------------------------------------*
  Name: CXInitUncompContextLZ

  Description: Initializes the streaming uncompression context for LZ compressed data.

  Arguments: context Pointer to the LZ uncompressed context
                dest        Destination address for uncompressed data
                header		a pointer to the leading data for the compressed data

 *---------------------------------------------------------------------------*/
void CXInitUncompContextLZ( CXUncompContextLZ          *context,
                            void                       *dest );

/*---------------------------------------------------------------------------*
  Name: CXInitUncompContextHuffman

  Description: Initializes the streaming uncompression context for Huffman compressed data.

  Arguments: context Pointer to the Huffman uncompressed context
                dest        Destination address for uncompressed data
                header		a pointer to the leading data for the compressed data

 *---------------------------------------------------------------------------*/
void CXInitUncompContextHuffman( CXUncompContextHuffman    *context, 
                                 void                      *dest );

/*---------------------------------------------------------------------------*
  Name: CXReadUncompRL

  Description: This function performs streaming uncompression of run-length compressed data.

  Arguments: context Pointer to the run-length uncompressed context
                data    Pointer to the next data
                len     Data size

  Returns: Size of remaining uncompressed data.

 *---------------------------------------------------------------------------*/
s32 CXReadUncompRL( CXUncompContextRL *context, const void *data, u32 len );

/*---------------------------------------------------------------------------*
  Name: CXReadUncompLZ

  Description: This function performs streaming uncompression of LZ compressed data.

  Arguments: context Pointer to the LZ uncompressed context
                data    Pointer to the next data
                len     Data size

  Returns: Size of remaining uncompressed data.

 *---------------------------------------------------------------------------*/
s32 CXReadUncompLZ( CXUncompContextLZ *context, const void *data, u32 len );

/*---------------------------------------------------------------------------*
  Name: CXReadUncompHuffman

  Description: This function performs streaming uncompression of Huffman compressed data.

  Arguments: context Pointer to the Huffman uncompressed context
                data    Pointer to the next data
                len     Data size

  Returns: Size of remaining uncompressed data.

 *---------------------------------------------------------------------------*/
s32 CXReadUncompHuffman( CXUncompContextHuffman *context, const void *data, u32 len );


/*---------------------------------------------------------------------------*
  Name:         CXIsFinishedUncompRL

  Description:  This function determines whether streaming decompression for runlength compression has completed or not.

  Arguments:    *context		Pointer to the run-length decompressed context

  Returns:      TRUE when decompression is complete
                FALSE when data needing to be read still remains
 *---------------------------------------------------------------------------*/
static inline BOOL CXIsFinishedUncompRL( const CXUncompContextRL *context )
{
    return (context->destCount > 0 || context->headerSize > 0)? FALSE : TRUE;
}


/*---------------------------------------------------------------------------*
  Name:         CXIsFinishedUncompLZ

  Description:  This function determines whether streaming decompression for LZ compression has completed or not.

  Arguments:    *context		Pointer to the LZ decompressed context

  Returns:      TRUE when decompression is complete
                FALSE when data needing to be read still remains
 *---------------------------------------------------------------------------*/
static inline BOOL CXIsFinishedUncompLZ( const CXUncompContextLZ *context )
{
    return (context->destCount > 0 || context->headerSize > 0)? FALSE : TRUE;
}


/*---------------------------------------------------------------------------*
  Name:         CXIsFinishedUncompHuffman

  Description:  This function determines whether streaming decompression for Huffman compression has completed or not.

  Arguments:    *context		pointer to the Huffman decompressed context

  Returns:      TRUE when decompression is complete
                FALSE when data needing to be read still remains
 *---------------------------------------------------------------------------*/
static inline BOOL CXIsFinishedUncompHuffman( const CXUncompContextHuffman *context )
{
    return (context->destCount > 0 || context->headerSize > 0)? FALSE : TRUE;
}


#ifdef __cplusplus
} /* extern "C"*/
#endif

/* __CX_STREAMING_UNCOMPRESSION_STREAM_H__*/
#endif
