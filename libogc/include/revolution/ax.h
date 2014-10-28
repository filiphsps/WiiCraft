/*---------------------------------------------------------------------------*
  Project:  Revolution AX library
  File:     AX.h

  Copyright (C)1998-2006 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ax.h,v $
  Revision 1.15  08/14/2006 02:00:38  aka
  Removed AX_DSP_CYCLES_PBSYNC.

  Revision 1.14  07/25/2006 00:55:22  aka
  Added a definition AX_ENABLE_REMOTE.

  Revision 1.13  07/21/2006 13:04:41  aka
  Re-designed how to support controller speakers.

  Revision 1.12  07/19/2006 07:40:48  aka
  Renamed AX_PB_MIXCTRL_RMT_XXX.

  Revision 1.11  07/19/2006 05:35:21  aka
  Added AX_PB_MIXCTRL_RMT_XXX definitions for controller speakers.

  Revision 1.10  07/19/2006 05:09:34  aka
  Added AXRmtGetLpfCoefs() and AXRmtGetHpfCoefs() for controller speakers.

  Revision 1.9  07/19/2006 04:42:13  aka
  Added AX_RMT_SAMPLES_PER_XXX definitions.

  Revision 1.8  07/10/2006 06:40:47  aka
  Modified to support controller speakers.

  Revision 1.7  03/22/2006 01:14:59  aka
  Changed AX_MAX_VOICES from 32 to 64.

  Revision 1.6  03/15/2006 08:25:26  aka
  Revised AX_DSP_CYCLES.

  Revision 1.5  2006/01/31 04:14:44  aka
  Renamed "Project" from Dolphin to Revolution.

  Revision 1.4  2006/01/31 01:01:54  aka
  Removed some comments.

  Revision 1.3  01/30/2006 11:50:16  aka
  Changed copyright.

  Revision 1.2  01/30/2006 11:29:59  aka
  Changed some comments from Japanese to English.

  Revision 1.1.1.1  2005/12/29 06:53:27  hiratsu
  Initial import.

  Revision 1.2  11/07/2005 06:42:32  aka
  Changed suiting to Revolution's audio spec.

  Revision 1.1.1.1  2005/05/12 02:41:06  yasuh-to
  Imported from dolphin tree.
    
    25    03/07/22 9:28a Akagi
    Changed return of AXRegisterCallback from void to AXUserCallback.
    
    24    03/06/11 2:58p Akagi
    Added AXGetLpfCoefs.
    
    23     03/04/15 19:53:00 Suzuki
    added the definition of AX_OUTPUT_BUFFER_DOUBLE and
    AX_OUTPUT_BUFFER_TRIPLE.
    
    22     03/04/15 13:44:00 Suzuki
    add AXInitEx.
    
    21    03/04/04 13:26 Suzuki
    add the definition of DSPADPCM
    
    20    8/15/02 11:02a Billyjack
    added low pass filter
    
    19    02/08/12 5:55p Akagi
    Added log field.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __AX_H__
#define __AX_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------------*
 *--------------------------------------------------------------------------*/
#define AX_ENABLE_REMOTE
    
/*--------------------------------------------------------------------------*
    profiling
 *--------------------------------------------------------------------------*/
typedef struct _AXPROFILE
{

    OSTime  axFrameStart;
    OSTime  auxProcessingStart;
    OSTime  auxProcessingEnd;
    OSTime  userCallbackStart;
    OSTime  userCallbackEnd;
    OSTime  axFrameEnd;
    u32     axNumVoices;
    u32     __padding;

} AXPROFILE;

/*--------------------------------------------------------------------------*
    mixing
 *--------------------------------------------------------------------------*/
typedef struct _AXPBMIX
{
    //  mixing values in .15, 0x8000 = ca. 1.0

    u16     vL;                 
    u16     vDeltaL;
    u16     vR;
    u16     vDeltaR;
    
    u16     vAuxAL;
    u16     vDeltaAuxAL;
    u16     vAuxAR;
    u16     vDeltaAuxAR;
    
    u16     vAuxBL;
    u16     vDeltaAuxBL;
    u16     vAuxBR;
    u16     vDeltaAuxBR;
    
    u16     vAuxCL;
    u16     vDeltaAuxCL;
    u16     vAuxCR;
    u16     vDeltaAuxCR;
    
    u16     vS;
    u16     vDeltaS;
    u16     vAuxAS;
    u16     vDeltaAuxAS;
    u16     vAuxBS;
    u16     vDeltaAuxBS;
    u16     vAuxCS;
    u16     vDeltaAuxCS;

} AXPBMIX;

#define AXPBMIX_VL_OFF            AXPBMIX_OFF
#define AXPBMIX_VDELTAL_OFF       (AXPBMIX_OFF+1)
#define AXPBMIX_VR_OFF            (AXPBMIX_OFF+2)
#define AXPBMIX_VDELTAR_OFF       (AXPBMIX_OFF+3)

#define AXPBMIX_VAUXAL_OFF        (AXPBMIX_OFF+4)
#define AXPBMIX_VDELTAAUXAL_OFF   (AXPBMIX_OFF+5)
#define AXPBMIX_VAUXAR_OFF        (AXPBMIX_OFF+6)
#define AXPBMIX_VDELTAAUXAR_OFF   (AXPBMIX_OFF+7)

#define AXPBMIX_VAUXBL_OFF        (AXPBMIX_OFF+8)
#define AXPBMIX_VDELTAAUXBL_OFF   (AXPBMIX_OFF+9)
#define AXPBMIX_VAUXBR_OFF        (AXPBMIX_OFF+10)
#define AXPBMIX_VDELTAAUXBR_OFF   (AXPBMIX_OFF+11)

#define AXPBMIX_VAUXCL_OFF        (AXPBMIX_OFF+12)
#define AXPBMIX_VDELTAAUXCL_OFF   (AXPBMIX_OFF+13)
#define AXPBMIX_VAUXCR_OFF        (AXPBMIX_OFF+14)
#define AXPBMIX_VDELTAAUXCR_OFF   (AXPBMIX_OFF+15)

#define AXPBMIX_VS_OFF            (AXPBMIX_OFF+16)
#define AXPBMIX_VDELTAS_OFF       (AXPBMIX_OFF+17)
#define AXPBMIX_VAUXAS_OFF        (AXPBMIX_OFF+18)
#define AXPBMIX_VDELTAAUXAS_OFF   (AXPBMIX_OFF+19)
#define AXPBMIX_VAUXBS_OFF        (AXPBMIX_OFF+20)
#define AXPBMIX_VDELTAAUXBS_OFF   (AXPBMIX_OFF+21)
#define AXPBMIX_VAUXCS_OFF        (AXPBMIX_OFF+22)
#define AXPBMIX_VDELTAAUXCS_OFF   (AXPBMIX_OFF+23)

#define AXPBMIX_SIZE              24

/*--------------------------------------------------------------------------*
    mixing for remote speaker
 *--------------------------------------------------------------------------*/
typedef struct _AXPBRMTMIX
{

    u16     vMain0;                 
    u16     vDeltaMain0;
    u16     vAux0;
    u16     vDeltaAux0;
    
    u16     vMain1;                 
    u16     vDeltaMain1;
    u16     vAux1;
    u16     vDeltaAux1;
    
    u16     vMain2;                 
    u16     vDeltaMain2;
    u16     vAux2;
    u16     vDeltaAux2;
    
    u16     vMain3;                 
    u16     vDeltaMain3;
    u16     vAux3;
    u16     vDeltaAux3;
    
} AXPBRMTMIX;

#define AXPBRMTMIX_SIZE           16

/*--------------------------------------------------------------------------*
    initial time delay
 *--------------------------------------------------------------------------*/
typedef struct _AXPBITD
{

    u16     flag;               //  on or off for this voice
    u16     bufferHi;           //  MRAM buffer
    u16     bufferLo;           //  
    u16     shiftL;             //  phase shift samples left (current)
    u16     shiftR;             //  phase shift samples right (current)
    u16     targetShiftL;       //  phase shift samples left (target)
    u16     targetShiftR;       //  phase shift samples right (target)

} AXPBITD;

//  flag
#define AX_PB_ITD_OFF      0x0000
#define AX_PB_ITD_ON       0x0001

#define AXPBITD_FLAG_OFF          AXPBITD_OFF
#define AXPBITD_BUFFERHI_OFF      (AXPBITD_OFF+1)
#define AXPBITD_BUFFERLO_OFF      (AXPBITD_OFF+2)
#define AXPBITD_SHIFTL_OFF        (AXPBITD_OFF+3)
#define AXPBITD_SHIFTR_OFF        (AXPBITD_OFF+4)
#define AXPBITD_TARGETSHIFTL_OFF  (AXPBITD_OFF+5)
#define AXPBITD_TARGETSHIFTR_OFF  (AXPBITD_OFF+6)
#define AXPBITD_SIZE              7

/*--------------------------------------------------------------------------*
    update / patch information
 *--------------------------------------------------------------------------*/
typedef struct _AXPBUPDATE
{

    u16     updNum[3];          // number of updates per 1ms step
    u16     dataHi;             // location of update data in MRAM
    u16     dataLo;

} AXPBUPDATE;

#define AXPBUPDATE_UPDNUM     AXPBUPDATE_OFF
#define AXPBUPDATE_DATAHI     (AXPBUPDATE_OFF+3)
#define AXPBUPDATE_DATALO     (AXPBUPDATE_OFF+4)
#define AXPBUPDATE_SIZE       5

/*--------------------------------------------------------------------------*
    depop data (last amplitudes mixed into buffers)
 *--------------------------------------------------------------------------*/
typedef struct _AXPBDPOP
{
    
    s16     aL;
    s16     aAuxAL;
    s16     aAuxBL;
    s16     aAuxCL;
    
    s16     aR;
    s16     aAuxAR;
    s16     aAuxBR;
    s16     aAuxCR;
    
    s16     aS;
    s16     aAuxAS;
    s16     aAuxBS;
    s16     aAuxCS;

} AXPBDPOP;

#define AXPBDPOP_AL_OFF       AXPBDPOP_OFF
#define AXPBDPOP_AAUXAL_OFF   (AXPBDPOP_OFF+1)
#define AXPBDPOP_AAUXBL_OFF   (AXPBDPOP_OFF+2)
#define AXPBDPOP_AAUXCL_OFF   (AXPBDPOP_OFF+3)

#define AXPBDPOP_AR_OFF       (AXPBDPOP_OFF+4)
#define AXPBDPOP_AAUXAR_OFF   (AXPBDPOP_OFF+5)
#define AXPBDPOP_AAUXBR_OFF   (AXPBDPOP_OFF+6)
#define AXPBDPOP_AAUXCR_OFF   (AXPBDPOP_OFF+7)

#define AXPBDPOP_AS_OFF       (AXPBDPOP_OFF+8)
#define AXPBDPOP_AAUXAS_OFF   (AXPBDPOP_OFF+9)
#define AXPBDPOP_AAUXBS_OFF   (AXPBDPOP_OFF+10)
#define AXPBDPOP_AAUXCS_OFF   (AXPBDPOP_OFF+11)

#define AXPBDPOP_SIZE         12
 
/*--------------------------------------------------------------------------*
    depop data for remote speakers
 *--------------------------------------------------------------------------*/
typedef struct _AXPBRMTDPOP
{
    
    s16     aMain0;
    s16     aMain1;
    s16     aMain2;
    s16     aMain3;
    
    s16     aAux0;
    s16     aAux1;
    s16     aAux2;
    s16     aAux3;

} AXPBRMTDPOP;

#define AXPBDRMTPOP_SIZE      8

/*--------------------------------------------------------------------------*
    volume envelope
 *--------------------------------------------------------------------------*/
typedef struct _AXPBVE
{

    u16     currentVolume;              // .15 volume at start of frame
    s16     currentDelta;               // signed per sample delta delta

} AXPBVE;

#define AXPBVE_CURRENTVOLUME_OFF  AXPBVE_OFF
#define AXPBVE_CURRENTDELTA_OFF   (AXPBVE_OFF+1)
#define AXPBVE_SIZE               2

/*--------------------------------------------------------------------------*
    buffer addressing
 *--------------------------------------------------------------------------*/
typedef struct _AXPBADDR
{                                       // all values are measured in samples:
    
    u16     loopFlag;                   // 0 = one-shot, 1=looping
    u16     format;                     // sample format used (see below)
    u16     loopAddressHi;              // Start of loop (this will point to a shared "zero" buffer if one-shot mode is active)
    u16     loopAddressLo;
    u16     endAddressHi;               // End of sample (and loop)
    u16     endAddressLo;
    u16     currentAddressHi;           // Current playback position
    u16     currentAddressLo;

} AXPBADDR;

#define AXPBADDR_LOOP_OFF     0           // States for loopFlag field
#define AXPBADDR_LOOP_ON      1

#define AXPBADDR_LOOPFLAG_OFF         AXPBADDR_OFF
#define AXPBADDR_FORMAT_OFF           (AXPBADDR_OFF+1)
#define AXPBADDR_LOOPADDRESSHI_OFF    (AXPBADDR_OFF+2)
#define AXPBADDR_LOOPADDRESSLO_OFF    (AXPBADDR_OFF+3)
#define AXPBADDR_ENDADDRESSHI_OFF     (AXPBADDR_OFF+4)
#define AXPBADDR_ENDADDRESSLO_OFF     (AXPBADDR_OFF+5)
#define AXPBADDR_CURRENTADDRESSHI_OFF (AXPBADDR_OFF+6)
#define AXPBADDR_CURRENTADDRESSLO_OFF (AXPBADDR_OFF+7)
#define AXPBADDR_SIZE                 8

/*--------------------------------------------------------------------------*
    ADPCM decoder state
 *--------------------------------------------------------------------------*/
typedef struct _AXPBADPCM
{

    u16     a[8][2];            //  coef table a1[0],a2[0],a1[1],a2[1]....

    u16     gain;               //  gain to be applied (0 for ADPCM, 0x0800 for PCM8/16)
    
    u16     pred_scale;         //  predictor / scale combination (nibbles, as in hardware)
    u16     yn1;                //  y[n - 1]
    u16     yn2;                //  y[n -2]
    
} AXPBADPCM;

#define AXPBADPCM_A1                  AXPBADPCM_OFF
#define AXPBADPCM_A2                  (AXPBADPCM_OFF+8)
#define AXPBADPCM_GAIN                (AXPBADPCM_OFF+16
#define AXPBADPCM_PRED_SCALE          (AXPBADPCM_OFF+17)
#define AXPBADPCM_YN1                 (AXPBADPCM_OFF+18)
#define AXPBADPCM_YN2                 (AXPBADPCM_OFF+19)
#define AXPBADPCM_SIZE                20

/*--------------------------------------------------------------------------*
    sample rate converter state
 *--------------------------------------------------------------------------*/
typedef struct _AXPBSRC
{
    
    u16     ratioHi;            //  sampling ratio, integer
    u16     ratioLo;            //  sampling ratio, fraction
    
    u16     currentAddressFrac; //  current fractional sample position
    
    u16     last_samples[4];    //  last 4 input samples

} AXPBSRC;

#define AXPBSRC_RATIOHI_OFF               AXPBSRC_OFF
#define AXPBSRC_RATIOLO_OFF               (AXPBSRC_OFF+1)
#define AXPBSRC_CURRENTADDRESSFRAC_OFF    (AXPBSRC_OFF+2)
#define AXPBSRC_LAST_SAMPLES_OFF          (AXPBSRC_OFF+3)       // 4 words
#define AXPBSRC_SIZE                      7
    
/*--------------------------------------------------------------------------*
    sample rate converter state for remote speakers
 *--------------------------------------------------------------------------*/
                                       
typedef struct _AXPBRMTSRC
{
    
    u16     currentAddressFrac; //  current fractional sample position
    
    u16     last_samples[4];    //  last 4 input samples

} AXPBRMTSRC;

#define AXPBRMTSRC_SIZE                   5

/*--------------------------------------------------------------------------*
    ADPCM loop parameters
 *--------------------------------------------------------------------------*/
typedef struct _AXPBADPCMLOOP
{
    
    u16     loop_pred_scale;    //  predictor / scale combination (nibbles, as in hardware)
    u16     loop_yn1;           //  y[n - 1]
    u16     loop_yn2;           //  y[n -2]

} AXPBADPCMLOOP;
    
#define AXPBADPCMLOOP_PRED_SCALE      AXPBADPCMLOOP_OFF
#define AXPBADPCMLOOP_YN1             (AXPBADPCMLOOP_OFF+1)
#define AXPBADPCMLOOP_YN2             (AXPBADPCMLOOP_OFF+2)
#define AXPBADPCMLOOP_SIZE            3

/*--------------------------------------------------------------------------*
    IIR filter parameters (lowpass)
 *--------------------------------------------------------------------------*/
typedef struct _AXPBLPF
{
    
    u16     on;                 
    u16     yn1;
    u16     a0;
    u16     b0;

} AXPBLPF;

#define AXPBLPF_ON                    AXPBLPF_OFF
#define AXPBLPF_YN1                   (AXPBLPF_OFF+1)
#define AXPBLPF_A0                    (AXPBLPF_OFF+2)
#define AXPBLPF_B0                    (AXPBLPF_OFF+3)
#define AXPBLPF_SIZE                  4

/*--------------------------------------------------------------------------*
    IIR filter parameters (highpass)
 *--------------------------------------------------------------------------*/
typedef struct _AXPBHPF
{
    
    u16     on;                 
    u16     yn1;
    u16     a0;
    u16     b0;

} AXPBHPF;

#define AXPBHPF_ON                    AXPBHPF_OFF
#define AXPBHPF_YN1                   (AXPBHPF_OFF+1)
#define AXPBHPF_A0                    (AXPBHPF_OFF+2)
#define AXPBHPF_B0                    (AXPBHPF_OFF+3)
#define AXPBHPF_SIZE                  4

/*--------------------------------------------------------------------------*
    voice parameter block
 *--------------------------------------------------------------------------*/
typedef struct _AXPB
{
    
    u16             nextHi;     // pointer to next parameter buffer (MRAM)
    u16             nextLo;
                    
    u16             currHi;     // pointer to this parameter buffer (MRAM)
    u16             currLo;
                    
    u16             srcSelect;  // Select type of SRC (none,4-tap,linear)
    u16             coefSelect; // Coef. to be used with 4-tap SRC
    u32             mixerCtrl;  // Mixer control bits
                    
    u16             state;      // current state (see below)
    u16             type;       // type of voice (stream)
                    
    AXPBMIX         mix;    
    AXPBITD         itd;
    AXPBUPDATE      update;
    AXPBDPOP        dpop;
    AXPBVE          ve;
    AXPBADDR        addr;
    AXPBADPCM       adpcm;
    AXPBSRC         src;
    AXPBADPCMLOOP   adpcmLoop;
    AXPBLPF         lpf;
    AXPBHPF         hpf;

    u16             remote;
    
    u16             rmtMixerCtrl; // Mixer control bits
    
    AXPBRMTMIX      rmtMix;
    AXPBRMTDPOP     rmtDpop;
    AXPBRMTSRC      rmtSrc;
    
    u16             pad[7];     // 32 byte alignment

} AXPB;

//  state
#define AX_PB_STATE_STOP        0x0000
#define AX_PB_STATE_RUN         0x0001

//  type
#define AX_PB_TYPE_NORMAL       0x0000
#define AX_PB_TYPE_STREAM       0x0001  // no loop context programming for ADPCM

//  format
#define AX_PB_FORMAT_PCM16      0x000A  // signed 16 bit PCM mono
#define AX_PB_FORMAT_PCM8       0x0019  // signed 8 bit PCM mono
#define AX_PB_FORMAT_ADPCM      0x0000  // ADPCM encoded (both standard & extended)

//  src select
#define AX_PB_SRCSEL_POLYPHASE  0x0000  // N64 type polyphase filter (4-tap)
#define AX_PB_SRCSEL_LINEAR     0x0001  // Linear interpolator
#define AX_PB_SRCSEL_NONE       0x0002  // No SRC (1:1)

//  coef select
#define AX_PB_COEFSEL_8KHZ      0x0000  // 8KHz low pass response
#define AX_PB_COEFSEL_12KHZ     0x0001  // 12.8KHz N64 type response
#define AX_PB_COEFSEL_16KHZ     0x0002  // 16KHz response

//  mixer ctrl for main speakers
#define AX_PB_MIXCTRL_L         0x00000001  // main left mix
#define AX_PB_MIXCTRL_R         0x00000002  // main right mix
#define AX_PB_MIXCTRL_LR_RAMP   0x00000004  // main bus ramp (applies to LR only)
#define AX_PB_MIXCTRL_S         0x00000008  // main surround mix
#define AX_PB_MIXCTRL_S_RAMP    0x00000010  // main bus ramp (applies to S only)

#define AX_PB_MIXCTRL_A_L       0x00010000  // AuxA left mix
#define AX_PB_MIXCTRL_A_R       0x00020000  // AuxA right mix
#define AX_PB_MIXCTRL_A_LR_RAMP 0x00040000  // AuxA bus ramp (applies to LR only)
#define AX_PB_MIXCTRL_A_S       0x00080000  // AuxA surround mix
#define AX_PB_MIXCTRL_A_S_RAMP  0x00100000  // AuxA bus ramp (applies to S only)

#define AX_PB_MIXCTRL_B_L       0x00200000  // AuxB left mix
#define AX_PB_MIXCTRL_B_R       0x00400000  // AuxB right mix
#define AX_PB_MIXCTRL_B_LR_RAMP 0x00800000  // AuxB bus ramp (applies to LR only)
#define AX_PB_MIXCTRL_B_S       0x01000000  // AuxB surround mix
#define AX_PB_MIXCTRL_B_S_RAMP  0x02000000  // AuxB bus ramp (applies to S only)

#define AX_PB_MIXCTRL_C_L       0x04000000  // AuxCleft mix
#define AX_PB_MIXCTRL_C_R       0x08000000  // AuxC right mix
#define AX_PB_MIXCTRL_C_LR_RAMP 0x10000000  // AuxC bus ramp (applies to LR only)
#define AX_PB_MIXCTRL_C_S       0x20000000  // AuxC surround mix
#define AX_PB_MIXCTRL_C_S_RAMP  0x40000000  // AuxC bus ramp (applies to S only)
#define AX_PB_MIXCTRL_C_DPL2    0x80000000  // AuxC DPL2, does not apply ITD for surrounds

//  IIR filter switch
#define AX_PB_LPF_OFF           0x0000  // IIR filter switch
#define AX_PB_LPF_ON            0x0001

#define AX_PB_HPF_OFF           0x0000  // IIR filter switch
#define AX_PB_HPF_ON            0x0001

// output
#define AX_PB_REMOTE_OFF        0x0000
#define AX_PB_REMOTE_ON         0x0001

//  mixer ctrl for remote speakers
#define AX_PB_MIXCTRL_MAIN0       0x0001  // main0 mix
#define AX_PB_MIXCTRL_MAIN0_RAMP  0x0002  // main0 mix with ramp
#define AX_PB_MIXCTRL_AUX0        0x0004  // aux0
#define AX_PB_MIXCTRL_AUX0_RAMP   0x0008  // aux0  mix with ramp
#define AX_PB_MIXCTRL_MAIN1       0x0010  // main1
#define AX_PB_MIXCTRL_MAIN1_RAMP  0x0020  // main1 mix with ramp
#define AX_PB_MIXCTRL_AUX1        0x0040  // aux1
#define AX_PB_MIXCTRL_AUX1_RAMP   0x0080  // aux1  mix with ramp
#define AX_PB_MIXCTRL_MAIN2       0x0100  // main2
#define AX_PB_MIXCTRL_MAIN2_RAMP  0x0200  // main2 mix with ramp
#define AX_PB_MIXCTRL_AUX2        0x0400  // aux2
#define AX_PB_MIXCTRL_AUX2_RAMP   0x0800  // aux2  mix with ramp
#define AX_PB_MIXCTRL_MAIN3       0x1000  // main3
#define AX_PB_MIXCTRL_MAIN3_RAMP  0x2000  // main3 mix with ramp
#define AX_PB_MIXCTRL_AUX3        0x4000  // aux3
#define AX_PB_MIXCTRL_AUX3_RAMP   0x8000  // aux3  mix with ramp

#define AX_PB_NEXTHI_OFF        0
#define AX_PB_NEXTLO_OFF        1
#define AX_PB_CURRHI_OFF        2
#define AX_PB_CURRLO_OFF        3
#define AX_PB_SRCSELECT_OFF     4
#define AX_PB_COEFSELECT_OFF    5
#define AX_PB_MIXERCTRL_OFF     6
#define AX_PB_STATE_OFF         8
#define AX_PB_TYPE_OFF          9
#define AXPBMIX_OFF             10

#define AXPBITD_OFF             (AXPBMIX_OFF       + AXPBMIX_SIZE)
#define AXPBUPDATE_OFF          (AXPBITD_OFF       + AXPBITD_SIZE)
#define AXPBDPOP_OFF            (AXPBUPDATE_OFF    + AXPBUPDATE_SIZE)
#define AXPBVE_OFF              (AXPBDPOP_OFF      + AXPBDPOP_SIZE)
#define AXPBADDR_OFF            (AXPBVE_OFF        + AXPBVE_SIZE)
#define AXPBADPCM_OFF           (AXPBADDR_OFF      + AXPBADDR_SIZE)
#define AXPBSRC_OFF             (AXPBADPCM_OFF     + AXPBADPCM_SIZE)
#define AXPBADPCMLOOP_OFF       (AXPBSRC_OFF       + AXPBSRC_SIZE)
#define AXPBLPF_OFF             (AXPBADPCMLOOP_OFF + AXPBADPCMLOOP_SIZE)
#define AXPBHPF_OFF             (AXPBLPF_OFF       + AXPBLPF_SIZE)

#define AXPBREMOTE_OFF          (AXPBHPF_OFF       + AXPBHPF_SIZE)
#define AXPBRMTMIXCTRL_OFF      (AXPBREMOTE_OFF    + 1)
#define AXPBRMTMIX_OFF          (AXPBRMTMIXCTRL_OFF+ 1)
#define AXPBRMTDPOP_OFF         (AXPBRMTMIX_OFF    + AXPBRMTMIX_SIZE)
#define AXPBRMTDSRC_OFF         (AXPBRMTDPOP_OFF   + AXPBRMTDPOP_SIZE)

#define AX_PB_SIZE              (AXPBRMTDSRC_OFF   + AXPBRMTDSRC_SIZE)

/*--------------------------------------------------------------------------*
    studio parameter block
 *--------------------------------------------------------------------------*/

typedef struct _AXSPB
{
    u16 dpopLHi;
    u16 dpopLLo;
    s16 dpopLDelta;
    u16 dpopRHi;
    u16 dpopRLo;
    s16 dpopRDelta;
    u16 dpopSHi;
    u16 dpopSLo;
    s16 dpopSDelta;
    
    u16 dpopALHi;
    u16 dpopALLo;
    s16 dpopALDelta;
    u16 dpopARHi;
    u16 dpopARLo;
    s16 dpopARDelta;
    u16 dpopASHi;
    u16 dpopASLo;
    s16 dpopASDelta;
    
    u16 dpopBLHi;
    u16 dpopBLLo;
    s16 dpopBLDelta;
    u16 dpopBRHi;
    u16 dpopBRLo;
    s16 dpopBRDelta;
    u16 dpopBSHi;
    u16 dpopBSLo;
    s16 dpopBSDelta;
    
    u16 dpopCLHi;
    u16 dpopCLLo;
    s16 dpopCLDelta;
    u16 dpopCRHi;
    u16 dpopCRLo;
    s16 dpopCRDelta;
    u16 dpopCSHi;
    u16 dpopCSLo;
    s16 dpopCSDelta;
    
    u16 dpopMain0Hi;
    u16 dpopMain0Lo;
    s16 dpopMain0Delta;
    u16 dpopAux0Hi;
    u16 dpopAux0Lo;
    s16 dpopAux0Delta;
    
    u16 dpopMain1Hi;
    u16 dpopMain1Lo;
    s16 dpopMain1Delta;
    u16 dpopAux1Hi;
    u16 dpopAux1Lo;
    s16 dpopAux1Delta;
    
    u16 dpopMain2Hi;
    u16 dpopMain2Lo;
    s16 dpopMain2Delta;
    u16 dpopAux2Hi;
    u16 dpopAux2Lo;
    s16 dpopAux2Delta;
    
    u16 dpopMain3Hi;
    u16 dpopMain3Lo;
    s16 dpopMain3Delta;
    u16 dpopAux3Hi;
    u16 dpopAux3Lo;
    s16 dpopAux3Delta;
    
} AXSPB;

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_DSP_CYCLES               (OS_BUS_CLOCK / 667)

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_MAX_VOICES               64

#define AX_MS_PER_FRAME             3

#define AX_IN_SAMPLES_PER_MS        32
#define AX_IN_SAMPLES_PER_SEC       (AX_IN_SAMPLES_PER_MS * 1000)
#define AX_IN_SAMPLES_PER_FRAME     (AX_IN_SAMPLES_PER_MS * AX_MS_PER_FRAME)

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_RMT_SAMPLES_PER_MS       6
#define AX_RMT_SAMPLES_PER_SEC      (AX_RMT_SAMPLES_PER_MS * 1000)
#define AX_RMT_SAMPLES_PER_FRAME    (AX_RMT_SAMPLES_PER_MS * AX_MS_PER_FRAME)

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_MODE_STEREO              0
#define AX_MODE_SURROUND            1
#define AX_MODE_DPL2                2

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_COMPRESSOR_OFF           0
#define AX_COMPRESSOR_ON            1

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_PRIORITY_STACKS          32
#define AX_PRIORITY_NODROP          (AX_PRIORITY_STACKS - 1)
#define AX_PRIORITY_LOWEST          1
#define AX_PRIORITY_FREE            0

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_SRC_TYPE_NONE            0
#define AX_SRC_TYPE_LINEAR          1
#define AX_SRC_TYPE_4TAP_8K         2
#define AX_SRC_TYPE_4TAP_12K        3
#define AX_SRC_TYPE_4TAP_16K        4

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_ADDR_ONESHOT             0
#define AX_ADDR_LOOP                1

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_SYNC_NONEWPARAMS         0x00000000
#define AX_SYNC_USER_SRCSELECT      0x00000001
#define AX_SYNC_USER_MIXCTRL        0x00000002
#define AX_SYNC_USER_STATE          0x00000004
#define AX_SYNC_USER_TYPE           0x00000008
#define AX_SYNC_USER_MIX            0x00000010
#define AX_SYNC_USER_ITD            0x00000020
#define AX_SYNC_USER_ITDTARGET      0x00000040
#define AX_SYNC_USER_UPDATE         0x00000080
#define AX_SYNC_USER_DPOP           0x00000100
#define AX_SYNC_USER_VE             0x00000200
#define AX_SYNC_USER_VEDELTA        0x00000400
#define AX_SYNC_USER_ADDR           0x00000800
#define AX_SYNC_USER_LOOP           0x00001000
#define AX_SYNC_USER_LOOPADDR       0x00002000
#define AX_SYNC_USER_ENDADDR        0x00004000
#define AX_SYNC_USER_CURRADDR       0x00008000
#define AX_SYNC_USER_ADPCM          0x00010000
#define AX_SYNC_USER_SRC            0x00020000
#define AX_SYNC_USER_SRCRATIO       0x00040000
#define AX_SYNC_USER_ADPCMLOOP      0x00080000
#define AX_SYNC_USER_LPF            0x00100000
#define AX_SYNC_USER_LPF_COEF       0x00200000
#define AX_SYNC_USER_HPF            0x00400000
#define AX_SYNC_USER_HPF_COEF       0x00800000

#define AX_SYNC_USER_REMOTE         0x01000000
#define AX_SYNC_USER_RMTMIXCTRL     0x02000000
#define AX_SYNC_USER_RMTMIX         0x04000000
#define AX_SYNC_USER_RMTDPOP        0x08000000
#define AX_SYNC_USER_RMTSRC         0x10000000

#define AX_SYNC_USER_ALLPARAMS      0x80000000

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#define AX_OUTPUT_BUFFER_DOUBLE     0
#define AX_OUTPUT_BUFFER_TRIPLE     1

/*---------------------------------------------------------------------------*
    callback interface
 *---------------------------------------------------------------------------*/
typedef void    (*AXUserCallback)   (void);   
typedef void    (*AXAuxCallback)    (void *data, void *context);
typedef void    (*AXVoiceCallback)  (void *p);

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
typedef struct _AXVPB
{
    void            *next;          // used in priority stacks
    void            *prev;          // used in priority stacks
    void            *next1;         // used in callback stack

    // these ares are used in voice allocation
    u32             priority;       // index to stack
    AXVoiceCallback callback;       // user callback for specified
    u32             userContext;    // user assigned context for callback

    // vars & flags for updating and sync PBs
    u32             index;          // index of VPB in array
    u32             sync;           // bit mask for each PB item to sync
    u32             depop;          // should depop voice
    u32             updateMS;       // update current ms
    u32             updateCounter;  // counter for n updates
    u32             updateTotal;    // bounds checking for update block
    u16             *updateWrite;   // write pointer for PB updates
    u16             updateData[128];// data for PB updates
    void            *itdBuffer;     // pointer to itd buffer
    AXPB            pb;             // write params to this PB

} AXVPB;

typedef struct _AXPBU
{
    
    u16 data[128];

} AXPBU;

typedef struct _AXPBITDBUFFER
{
    
    s16 data[32];

} AXPBITDBUFFER;

/*---------------------------------------------------------------------------*
Header for DSPADPCM.exe header
 *---------------------------------------------------------------------------*/
typedef struct
{
    u32 num_samples;       // total number of RAW samples
    u32 num_adpcm_nibbles; // number of ADPCM nibbles (including frame headers)
    u32 sample_rate;       // Sample rate, in Hz
    u16 loop_flag;         // 1=LOOPED, 0=NOT LOOPED
    u16 format;            // Always 0x0000, for ADPCM
    u32 sa;                // Start offset address for looped samples (zero for non-looped)
    u32 ea;                // End offset address for looped samples
    u32 ca;                // always zero
    u16 coef[16];          // decode coefficients (eight pairs of 16-bit words)
    u16 gain;              // always zero for ADPCM
    u16 ps;                // predictor/scale
    u16 yn1;               // sample history
    u16 yn2;               // sample history
    u16 lps;               // predictor/scale for loop context
    u16 lyn1;              // sample history (n-1) for loop context
    u16 lyn2;              // sample history (n-2) for loop context
    u16 pad[11];           // reserved
    
} DSPADPCM;

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
void    AXInit                      (void);
void    AXInitEx                    (u32 outputBufferMode);
void    AXQuit                      (void);

AXUserCallback AXRegisterCallback   (AXUserCallback callback);

void    AXSetMode                   (u32 mode);
u32     AXGetMode                   (void);

void    AXSetMaxDspCycles           (u32 cycles);
u32     AXGetMaxDspCycles           (void);
u32     AXGetDspCycles              (void);

void    AXRegisterAuxACallback      (AXAuxCallback callback, void *context);
void    AXRegisterAuxBCallback      (AXAuxCallback callback, void *context);
void    AXRegisterAuxCCallback      (AXAuxCallback callback, void *context);

AXVPB*  AXAcquireVoice              (
                                     u32                priority,
                                     AXVoiceCallback    callback,
                                     u32                userContext
                                     );

void    AXFreeVoice                 (AXVPB *p);
void    AXSetVoicePriority          (AXVPB *p, u32 priority);

void    AXSetVoiceSrcType           (AXVPB *p, u32 type);
void    AXSetVoiceState             (AXVPB *p, u16 state);
void    AXSetVoiceType              (AXVPB *p, u16 type);
void    AXSetVoiceMix               (AXVPB *p, AXPBMIX *mix);
void    AXSetVoiceItdOn             (AXVPB *p);
void    AXSetVoiceItdTarget         (AXVPB *p, u16 lShift, u16 rShift);
void    AXSetVoiceUpdateIncrement   (AXVPB *p);
void    AXSetVoiceUpdateWrite       (AXVPB *p, u16 param, u16 data);
void    AXSetVoiceDpop              (AXVPB *p, AXPBDPOP *dpop);
void    AXSetVoiceVe                (AXVPB *p, AXPBVE *ve);
void    AXSetVoiceVeDelta           (AXVPB *p, s16 delta);
void    AXSetVoiceAddr              (AXVPB *p, AXPBADDR *addr);
void    AXSetVoiceLoop              (AXVPB *p, u16 loop);
void    AXSetVoiceLoopAddr          (AXVPB *p, u32 address);
void    AXSetVoiceEndAddr           (AXVPB *p, u32 address);
void    AXSetVoiceCurrentAddr       (AXVPB *p, u32 address);
void    AXSetVoiceAdpcm             (AXVPB *p, AXPBADPCM *adpcm);
void    AXSetVoiceSrc               (AXVPB *p, AXPBSRC *src);
void    AXSetVoiceSrcRatio          (AXVPB *p, f32 ratio);
void    AXSetVoiceAdpcmLoop         (AXVPB *p, AXPBADPCMLOOP *adpcmloop);
void    AXSetVoiceLpf               (AXVPB *p, AXPBLPF *lpf);
void    AXSetVoiceLpfCoefs          (AXVPB *p, u16 a0, u16 b0);
void    AXSetVoiceHpf               (AXVPB *p, AXPBHPF *hpf);
void    AXSetVoiceHpfCoefs          (AXVPB *p, u16 a0, u16 b0);

void    AXInitProfile               (AXPROFILE *profile, u32 maxProfiles);
u32     AXGetProfile                (void);

void    AXSetCompressor             (u32);

void    AXSetStepMode               (u32);

void    AXGetLpfCoefs               (u16 freq, u16 *a0, u16 *b0);
void    AXGetHpfCoefs               (u16 freq, u16 *a0, u16 *b0);
    
void    AXSetVoiceRmtOn             (AXVPB *p, u16 on);
void    AXSetVoiceRmtMix            (AXVPB *p, AXPBRMTMIX  *mix);
void    AXSetVoiceRmtDpop           (AXVPB *p, AXPBRMTDPOP *dpop);
void    AXSetVoiceRmtSrc            (AXVPB *p, AXPBRMTSRC  *src);

s32     AXRmtGetSamplesLeft         (void);
s32     AXRmtGetSamples             (s32 chan, s16* buffer, s32 samples);
s32     AXRmtAdvancePtr             (s32 samples);
    
#ifdef __cplusplus
}
#endif

#endif // __AX_H__
