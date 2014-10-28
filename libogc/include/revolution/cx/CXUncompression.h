/*---------------------------------------------------------------------------*
  Project:     compress/uncompress library
  File:        CXUncompression.h

  Copyright 2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: CXUncompression.h,v $
  Revision 1.10  07/14/2006 05:23:56  takano_makoto
  Add CXUncompressAny()
  Bug fix in CXGetCompressionType()

  Revision 1.9  07/06/2006 09:19:14  takano_makoto
  Changed the include guard to the REVOLUTION_SDK format

  Revision 1.8  07/06/2006 05:29:48  takano_makoto
  Added CXUnfilterDiff

  Revision 1.7  07/06/2006 04:39:50  takano_makoto
  revised duplicate definitions in CXGetCompressionType, CXGetUncompressedSize

  Revision 1.6  07/06/2006 04:13:04  takano_makoto
  added CXGetCompressionType, CXGetUncompressedSize

  Revision 1.5  07/05/2006 11:14:43  takano_makoto
  revised the include guard

  Revision 1.4  07/05/2006 08:13:03  takano_makoto
  revised comments

  Revision 1.3  07/04/2006 08:38:39  takano_makoto
  fix copyright header

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __CX_UNCOMPRESSION_H__
#define __CX_UNCOMPRESSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <dolphin/types.h>


//---- compression type
typedef enum
{
    CX_COMPRESSION_LZ           = 0x10,     // LZ77
    CX_COMPRESSION_HUFFMAN      = 0x20,     // Huffman
    CX_COMPRESSION_RL           = 0x30,     // Run Length
    CX_COMPRESSION_DIFF         = 0x80,     // Differential filter

    CX_COMPRESSION_TYPE_MASK    = 0xF0,
    CX_COMPRESSION_TYPE_EX_MASK = 0xFF
}
CXCompressionType;


//----------------------------------------------------------------
// Compressed data header
//
typedef struct
{
    u32 compParam : 4;
    u32 compType  : 4;
    u32 destSize  :24;

}
CXCompressionHeader;


/*---------------------------------------------------------------------------*
  Name:         CXGetCompressionHeader

  Description:  Gets header information from the first four bytes in the compression data

  Arguments:    data	a pointer to the first four bytes of data in the compressed data

  Returns:      None.
 *---------------------------------------------------------------------------*/
CXCompressionHeader CXGetCompressionHeader( const void *data );

/*---------------------------------------------------------------------------*
  Name:         CXGetCompressionType

  Description:  Gets compression data from the first one byte in the compressed data

  Arguments:    srcp :  compressed data address

  Returns:      compression type.
                CX_COMPREESION_LZ      : LZ77 compressed data
                CX_COMPREESION_HUFFMAN : Huffman compressed data
                CX_COMPREESION_RL      : Run-length compressed data
                CX_COMPRESSION_DIFF    : data converted with a differential filter
 *---------------------------------------------------------------------------*/
static inline CXCompressionType   CXGetCompressionType( const void *data )
{
    return (CXCompressionType)( *(u8*)data & 0xF0 );
}

//======================================================================
//          Expanding compressed data
//======================================================================

/*---------------------------------------------------------------------------*
  Name:         CXGetUncompressedSize

  Description:  Gets the data size after decompression.
                This function can be used for data in all compression formats handled by CX.

  Arguments:    srcp :  a pointer to the first four bytes of data in the compressed data

  Returns:      Data size after expansion
 *---------------------------------------------------------------------------*/
u32 CXGetUncompressedSize( const void *srcp );


/*---------------------------------------------------------------------------*
  Name:         CXUncompressAny

  Description:  Determines the compression type from the data header and
                runs the appropriate decompression process.
                As all the decompression for compression types are linked,
                it would be good to run this function for each compression type unless
                a special compression format is used.

  Arguments:    srcp          source address
                destp         destination address

  Returns:      None.
 *---------------------------------------------------------------------------*/
void CXUncompressAny( const void* srcp, void* destp );


/*---------------------------------------------------------------------------*
  Name:         CXUncompressRL

  Description:  8-bit expanding runlength compressed data

  * Expands runlength compressed data, and writes in 8-bit units.
  - Align source address to a 4-byte boundary.

  * Data header
      u32 :4                  reserved
          compType:4          compression type  ( = 3)
          destSize:24         Data size after decoding
  
  * Flag data format
      u8  length:7            Expansion data length - 1 (When not compressed)
                              Expansion data length - 3 (Only compress when the contiguous length is 3-bytes or greater)
          flag:1              (0, 1) = (not compressed, compressed)
  
  Arguments:    *srcp          source address
                *destp         destination address

  Returns:      None.
 *---------------------------------------------------------------------------*/
void CXUncompressRL( const void *srcp, void *destp );


/*---------------------------------------------------------------------------*
  Name:         CXUncompressLZ
  
  Description:  8-bit expanding LZ77 compressed data
  
  * Expands LZ77 compressed data, and writes in 8-bit units.
  - Align source address to a 4-byte boundary.
  
  * Data header
      u32 :4                  reserved
          compType:4          compression type  ( = 1)
          destSize:24         Data size after decoding
  
  * Flag data format
      u8  flags               compression/no compression flag
                              (0, 1) = (not compressed, compressed)
  * Code data format (Big Endian)
      u16 length:4            Expansion data length - 3(Only compress when the match length is 3-bytes or greater)
          offset:12           match data offset - 1
  
  Arguments:    *srcp          source address
                *destp         destination address
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void CXUncompressLZ( const void *srcp, void *destp );


/*---------------------------------------------------------------------------*
  Name:         CXUncompressHuffman
  
  Description:  Expanding Huffman compressed data
  
  * Expands Huffman compressed data, and writes in 32-bit units.
  - Align source address to a 4-byte boundary.
  - Align the destination address to a four byte boundary.
  - The compression buffer size must be prepared in 4-byte multiples.
  
  * Data header
      u32 bitSize:4           1 data bit size (Normally 4|8)
          compType:4          compression type  ( = 2)
          destSize:24         Data size after decoding
  
  * Tree table
      u8           treeSize        tree table size/2 - 1
      TreeNodeData nodeRoot        root node
  
      TreeNodeData nodeLeft        root left node
      TreeNodeData nodeRight       root right node
  
      TreeNodeData nodeLeftLeft    left left node
      TreeNodeData nodeLeftRight   left ride node
  
      TreeNodeData nodeRightLeft   right left node
      TreeNodeData nodeRightRight  right right node
  
              ÅE
              ÅE
  
    The compress data structure follows
  
  * TreeNodeData structure
      u8  nodeNextOffset:6    Offset to the next node data - 1 (2-byte units)
          rightEndFlag:1      right node end flag
          leftEndzflag:1       Left node end flag
                              when end flag is set
                              there is data in next node
  
  Arguments:    *srcp          source address
                *destp         destination address

  Returns:      None.
 *---------------------------------------------------------------------------*/
void CXUncompressHuffman( const void *srcp, void *destp );


/*---------------------------------------------------------------------------*
  Name:         CXUnfilterDiff

  Description:  Decode differential filter conversion. Use 8-bit decoding.
  
    - Decodes a differential filter. Writes in 8-bit units.
    - Cannot decode directly into VRAM
    - If the size of compressed data is not a multiple of four,
      adjust as necessary by padding with 0s.
    - Align source address to a 4-byte boundary.

  Arguments:    *srcp          source address
                *destp         destination address

  Returns:      None.
 *---------------------------------------------------------------------------*/
void CXUnfilterDiff( register const void *srcp, register void *destp );


//================================================================================


/*---------------------------------------------------------------------------*
  Name:         CXiUncompressBackward

  Description:  Uncompress special archive for module compression

  Arguments:    bottom         = Bottom adrs of packed archive + 1
                bottom[-12] = offset for top    of compressed data
                                 inp_top = bottom + bottom[-12]
                bottom[-8]     = offset for bottom of compressed data
                                 inp     = bottom + bottom[ -8]
                bottom[ -4] = offset for bottom of original data
                                 outp    = bottom + bottom[ -4]
  
                typedef struct
                {
                    int         bufferTop;
                    int         compressBottom;
                    int         originalBottom;
                }  CompFooter;

  Returns:      None.
 *---------------------------------------------------------------------------*/
// !!!! Coded in libraries/init/ARM9/crt0.c
// void CXiUncompressBackward( void *bottom );




#ifdef __cplusplus
} /* extern "C"*/
#endif

/* __CX_UNCOMPRESSION_H__*/
#endif
