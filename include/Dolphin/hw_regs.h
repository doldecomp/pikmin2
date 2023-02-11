#ifndef _DOLPHIN_HW_REGS_H
#define _DOLPHIN_HW_REGS_H

#include "types.h"
#include "Dolphin/OS/OSUtil.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

/////// HARDWARE REGISTERS ///////
// Video Interface registers.
vu16 __VIRegs[59] AT_ADDRESS(0xCC002000);

// offsets for __VIRegs[i]
#define VI_VERT_TIMING      (0)
#define VI_DISP_CONFIG      (1)
#define VI_HORIZ_TIMING_0   (2)
#define VI_HORIZ_TIMING_1   (4)
#define VI_VERT_TIMING_ODD  (6)
#define VI_VERT_TIMING_EVEN (8)

#define VI_BBI_ODD  (10) // burst blanking interval
#define VI_BBI_EVEN (12) // burst blanking interval

#define VI_DISP_INT_0 (24) // display interrupt 0
#define VI_DISP_INT_1 (26) // display interrupt 1
#define VI_DISP_INT_2 (28) // display interrupt 2
#define VI_DISP_INT_3 (30) // display interrupt 3

// Processor Interface registers.
vu32 __PIRegs[12] AT_ADDRESS(0xCC003000);

// offsets for __PIRegs[i]
#define PI_INTRPT_SRC  (0) // interrupt cause
#define PI_INTRPT_MASK (1) // interrupt mask
#define PI_FIFO_START  (3) // FIFO base start
#define PI_FIFO_END    (4) // FIFO base end
#define PI_FIFO_PTR    (5) // FIFO current write pointer

// Memory Interface registers.
vu16 __MEMRegs[64] AT_ADDRESS(0xCC004000);

// offsets for __MEMRegs[i]
#define MEM_PROT_1    (0) // protected region 1
#define MEM_PROT_2    (2) // protected region 1
#define MEM_PROT_3    (4) // protected region 1
#define MEM_PROT_4    (6) // protected region 1
#define MEM_PROT_TYPE (8) // protection type

#define MEM_INTRPT_MASK    (14) // interrupt mask
#define MEM_INTRPT_SRC     (15) // interrupt cause
#define MEM_INTRPT_FLAG    (16) // set when interrupt happens
#define MEM_INTRPT_ADDR_LO (17) // address that caused interrupt
#define MEM_INTRPT_ADDR_HI (18) // address that caused interrupt

// Digital Signal Processor registers (for audio mixing).
vu16 __DSPRegs[32] AT_ADDRESS(0xCC005000);

// offsets for __DSPRegs[i]
#define DSP_MAILBOX_IN_HI  (0)
#define DSP_MAILBOX_IN_LO  (1)
#define DSP_MAILBOX_OUT_HI (2)
#define DSP_MAILBOX_OUT_LO (3)
#define DSP_CONTROL_STATUS (5)

#define DSP_ARAM_SIZE        (9)
#define DSP_ARAM_MODE        (11)
#define DSP_ARAM_REFRESH     (13)
#define DSP_ARAM_DMA_MM_HI   (16) // Main mem address
#define DSP_ARAM_DMA_MM_LO   (17)
#define DSP_ARAM_DMA_ARAM_HI (18) // ARAM address
#define DSP_ARAM_DMA_ARAM_LO (19)
#define DSP_ARAM_DMA_SIZE_HI (20) // DMA buffer size
#define DSP_ARAM_DMA_SIZE_LO (21)

#define DSP_DMA_START_HI    (24) // DMA start address
#define DSP_DMA_START_LO    (25)
#define DSP_DMA_CONTROL_LEN (27)
#define DSP_DMA_BYTES_LEFT  (29)

// DVD Interface registers.
vu32 __DIRegs[16] AT_ADDRESS(0xCC006000);

// offsets for __DIRegs[i]
#define DI_STATUS       (0)
#define DI_COVER_STATUS (1) // cover status - 0=normal, 1=interrupt/open
#define DI_CMD_BUF_0    (2) // command buffer 0
#define DI_CMD_BUF_1    (3) // command buffer 1
#define DI_CMD_BUF_2    (4) // command buffer 2
#define DI_DMA_MEM_ADDR (5) // DMA address
#define DI_DMA_LENGTH   (6) // transfer length address
#define DI_CONTROL      (7)
#define DI_MM_BUF       (8) // Main memory buffer
#define DI_CONFIG       (9)

// Serial Interface registers.
vu32 __SIRegs[64] AT_ADDRESS(0xCC006400);

// offsets for __SIRegs[i]
// Channel 0/Joy-channel 1
#define SI_CHAN_0_BUF   (0) // output buffer
#define SI_CHAN_0_BTN_1 (1) // button 1
#define SI_CHAN_0_BTN_2 (2) // button 2
// Channel 1/Joy-channel 2
#define SI_CHAN_1_BUF   (3) // output buffer
#define SI_CHAN_1_BTN_1 (4) // button 1
#define SI_CHAN_1_BTN_2 (5) // button 2
// Channel 2/Joy-channel 3
#define SI_CHAN_2_BUF   (6) // output buffer
#define SI_CHAN_2_BTN_1 (7) // button 1
#define SI_CHAN_2_BTN_2 (8) // button 2
// Channel 3/Joy-channel 4
#define SI_CHAN_3_BUF   (9) // output buffer
#define SI_CHAN_3_BTN_1 (10) // button 1
#define SI_CHAN_3_BTN_2 (11) // button 2

#define SI_POLL     (12)
#define SI_CC_STAT  (13) // communication control status
#define SI_STAT     (14)
#define SI_EXI_LOCK (15) // exi clock lock

#define SI_IO_BUFFER (32) // start of buffer (32 to 63)

// Expansion/External Interface registers.
vu32 __EXIRegs[16] AT_ADDRESS(0xCC006800);

// offsets for __EXIRegs[i]
// Channel 0
#define EXI_CHAN_0_STAT     (0) // parameters/status
#define EXI_CHAN_0_DMA_ADDR (1) // DMA start address
#define EXI_CHAN_0_LEN      (2) // DMA transfer length
#define EXI_CHAN_0_CONTROL  (3) // control register
#define EXI_CHAN_0_IMM      (4) // immediate data
// Channel 1
#define EXI_CHAN_1_STAT     (5) // parameters/status
#define EXI_CHAN_1_DMA_ADDR (6) // DMA start address
#define EXI_CHAN_1_LEN      (7) // DMA transfer length
#define EXI_CHAN_1_CONTROL  (8) // control register
#define EXI_CHAN_1_IMM      (9) // immediate data
// Channel 2
#define EXI_CHAN_0_STAT     (10) // parameters/status
#define EXI_CHAN_0_DMA_ADDR (11) // DMA start address
#define EXI_CHAN_0_LEN      (12) // DMA transfer length
#define EXI_CHAN_0_CONTROL  (13) // control register
#define EXI_CHAN_0_IMM      (14) // immediate data

// Audio Streaming Interface registers.
vu32 __AIRegs[8] AT_ADDRESS(0xCC006C00);

// offsets for __AIRegs[i]
#define AI_CONTROL        (0) // control
#define AI_VOLUME         (1) // volume
#define AI_SAMPLE_COUNTER (2) // number of stereo samples output
#define AI_INTRPT_TIMING  (3) // interrupt timing

//////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
