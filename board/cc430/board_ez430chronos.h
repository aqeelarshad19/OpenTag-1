/* Copyright 2009-2012 JP Norair
  *
  * Licensed under the OpenTag License, Version 1.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * http://www.indigresso.com/wiki/doku.php?id=opentag:license_1_0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  */
/**
  * @file       /board/cc430/board_chronos.h
  * @author     JP Norair
  * @version    V1.0
  * @date       5 May 2012
  * @brief      Board Configuration for TI ez430 Chronos Watch board
  * @ingroup    Platform
  *
  * Do not include this file, include OT_platform.h
  *
  * Specifically, this board is from the TI ez430 Chronos Dev Kit.  It can be 
  * seen on the OpenTag wiki and on TI's website:
  * http://www.indigresso.com/wiki/doku.php?id=opentag:board:ez430-chronos
  * http://processors.wiki.ti.com/index.php?title=EZ430-Chronos
  ******************************************************************************
  */
  

#ifndef __board_chronos_H
#define __board_chronos_H

#include "build_config.h"
#include "platform_CC430.h"

#ifdef __NULL_RADIO__
#   include "radio_null.h"
#else
#   include "radio_CC430.h"
#endif


/// Macro settings: ENABLED, DISABLED, NOT_AVAILABLE
#ifdef ENABLED
#   undef ENABLED
#endif
#define ENABLED  1

#ifdef DISABLED
#   undef DISABLED
#endif
#define DISABLED  0

#ifdef NOT_AVAILABLE
#   undef NOT_AVAILABLE
#endif
#define NOT_AVAILABLE   DISABLED



/** RF Front End Parameters and Settings <BR>
  * ========================================================================<BR>
  * The default is 433 MHz.  You could potentially change this to 866 if you
  * have 866 EMK boards, but make sure the radio module supports it.  Only 433
  * is confirmed working.
  */
#define RF_PARAM_BAND   433
#define RF_HDB_ATTEN    12      //Half dB attenuation (units = 0.5dB), used to scale TX power
#define RF_RSSI_OFFSET  6       //Offset applied to RSSI calculation




/** MCU Feature settings      <BR>
  * ========================================================================<BR>
  * Implemented capabilities of the CC430F5137/6137 variants.
  *
  * @note In debug builds, MPipe is made available as a UART on GPIO2.0, 2.1.
  * These pins are routed to the 2x4 header on the board.  In release builds,
  * there is probably no reason to use MPipe on this board.  If you wish, you
  * can change the setup.
  */
#define MCU_FEATURE(VAL)                 MCU_FEATURE_##VAL       // FEATURE                  AVAILABILITY
#define MCU_FEATURE_CRC                  ENABLED                 // CCITT CRC16              Low
#define MCU_FEATURE_AES128               ENABLED                 // AES128 engine            Moderate
#define MCU_FEATURE_ECC                  DISABLED                // ECC engine               Low
#define MCU_FEATURE_ALGE                 DISABLED                // Algebraic Eraser engine  Rare/None yet
#define MCU_FEATURE_RADIODMA             DISABLED
#define MCU_FEATURE_RADIODMA_TXBYTES     0
#define MCU_FEATURE_RADIODMA_RXBYTES     0
#define MCU_FEATURE_MAPEEPROM            DISABLED
#define MCU_FEATURE_MPIPEDMA             (DISABLED || MPIPE_FOR_DEBUGGING)      // MPipe is only useful for debug mode
#define MCU_FEATURE_MEMCPYDMA            (ENABLED && !MCU_FEATURE_MPIPEDMA)      // Must be disabled if MPIPEDMA is enabled

#define MCU_PARAM(VAL)                  MCU_PARAM_##VAL
#define MCU_PARAM_POINTERSIZE           2



/** Board-based Feature Settings <BR>
  * ========================================================================<BR>
  * Notes apart from the obvious:  
  *
  * 1. There is a general purpose button attached to P1.5.  The other two 
  * buttons are hooked directly into the PaLFi core.  In the board schematic 
  * and documentation, this button is defined as "SW2".  This button is active-
  * low and it requires you to pull-up the input pin.
  * 
  * 2. The 4 LEDs (TRIGS 1-4) are reverse-biased.  Therefore, to use them
  * properly you need to invert the output signal.
  */
#define BOARD_FEATURE(VAL)              BOARD_FEATURE_##VAL
#define BOARD_FEATURE_USBCONVERTER      ENABLED                 // Is UART connected via USB converter?
#define BOARD_FEATURE_LFXTAL            ENABLED                 // LF XTAL used as Clock source
#define BOARD_FEATURE_HFXTAL            DISABLED                // HF XTAL used as Clock source
#define BOARD_FEATURE_INVERT_TRIG1      DISABLED
#define BOARD_FEATURE_INVERT_TRIG2      DISABLED
#define BOARD_FEATURE_INVERT_TRIG3      DISABLED
#define BOARD_FEATURE_INVERT_TRIG4      DISABLED

#define BOARD_SW2_PORT                  GPIO1
#define BOARD_SW2_PIN                   GPIO_Pin_5
#define BOARD_SW2_POLARITY              0

#define BOARD_PARAM(VAL)                BOARD_PARAM_##VAL
#define BOARD_PARAM_LFHz                32768
#define BOARD_PARAM_LFtol               0.00002
#define BOARD_PARAM_HFHz                32768
#define BOARD_PARAM_HFmult              610                     // DCO = HFHz * HFmult
#define BOARD_PARAM_HFtol               BOARD_PARAM_LFtol
#define BOARD_PARAM_MCLKDIV             1                       // Master Clock = DCO / MCLKDIV
#define BOARD_PARAM_SMCLKDIV            8                       // Submaster Clock = DCO / SMCLKDIV (~2.5 MHz)

#if (BOARD_FEATURE(LFXTAL) == ENABLED)
#   define BOARD_LFXT_PINS      (GPIO_Pin_0 | GPIO_Pin_1)
#   define BOARD_LFXT_CONF      (UCS_CTL6_XTS_low | UCS_CTL6_XT1BYPASS_off | UCS_CTL6_XCAP_2 )
#else
#   define BOARD_LFXT_PINS      0
#   define BOARD_LFXT_CONF      (XT1OFF)
#endif

#if (BOARD_FEATURE(HFXTAL) == ENABLED)
#   define BOARD_HFXT_PINS      (GPIO_Pin_2 | GPIO_Pin_3)
#   define BOARD_HFXT_CONF      (XT2DRIVE_3)
#else
#   define BOARD_HFXT_PINS      0
#   define BOARD_HFXT_CONF      (UCS_CTL6_XT2OFF | 0xC0 )
#endif


OT_INLINE_H void BOARD_PORT_STARTUP(void) {
/// Configure all ports to grounded outputs in order to minimize current
    P1DIR = ~(BOARD_SW2_PIN);
    P2DIR = 0xFF;
    P3DIR = 0xFF;
    P4DIR = 0xFF;
    
#   if (defined(DEBUG_ON) || defined(__DEBUG__))
    PJDIR = 0x00;
#   else
    PJDIR = 0xFF;
#   endif    
    
    P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;
    PJOUT = 0x00;
}

// LFXT1 Preconfiguration, using values local to the board design
// ALL CC430 Boards MUST HAVE SOME VARIANT OF THIS
OT_INLINE_H void BOARD_XTAL_STARTUP(void) {
    // Turn on XT1 as LF crystal.  Let RF core manage 26 MHz XT2
    GPIO5->SEL |= BOARD_LFXT_PINS | BOARD_HFXT_PINS;
    UCS->CTL6   = BOARD_LFXT_CONF | BOARD_HFXT_CONF;
    
    // Loop until XT2, XT1, and DCO all stabilize
    do {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1&OFIFG);
  
    // Set LF and HF drive strength to minimum (depends on XTAL spec)
    UCS->CTL6  &= ~(XT1DRIVE_3);
}






/** Platform Memory Configuration <BR>
  * ========================================================================<BR>
  * OpenTag needs to know where it can put Nonvolatile memory (file system) and
  * how much space it can allocate for filesystem.
  */
#define SRAM_START_ADDR             0x0000
#define SRAM_SIZE                   (4*1024)
#define EEPROM_START_ADDR           0
#define EEPROM_SIZE                 0
#define FLASH_START_ADDR            0x8000
#define FLASH_START_PAGE            0
#define FLASH_PAGE_SIZE             512
#define FLASH_WORD_BYTES            2
#define FLASH_WORD_BITS             (FLASH_WORD_BYTES*8)
#ifdef __LARGE_MEMORY__
#   warn "No current CC430 part has large-memory model"
#else
#   define FLASH_NUM_PAGES          64
#   define FLASH_FS_ALLOC           (512*8)     //allocating total of 8 blocks (4KB)
#   define FLASH_FS_ADDR            0x8000
#   define FLASH_FS_FALLOWS         3
#endif
#define FLASH_PAGE_ADDR(VAL)    (FLASH_START_ADDR + ( (VAL) * FLASH_PAGE_SIZE) )




// MSP430 only ... Information Flash
// Info Page A usage is riddled with glitches, hence limiting to 3 pages
// instead of 4.  Page A is addresses 1980 - 19FF
#   define INFO_START_ADDR          0x1800
#   define INFO_START_PAGE          0
#   define INFO_PAGE_SIZE           128
#   define INFO_NUM_PAGES           3
#   define INFO_PAGE_ADDR(VAL)      (INFO_START_ADDR + (INFO_PAGE_SIZE*VAL))
#   define INFO_D_ADDR              INFO_PAGE_ADDR(0)
#   define INFO_C_ADDR              INFO_PAGE_ADDR(1)
#   define INFO_B_ADDR              INFO_PAGE_ADDR(2)
#   define INFO_A_ADDR              INFO_PAGE_ADDR(3)





/** Note: Clocking for the Board's MCU      <BR>
  * ========================================================================<BR>
  * The CC430 MCU can be clocked up to 20MHz.  OpenTag uses the ACLK at 1024 Hz
  * for GPTIM, so it's important to define either the internal 32768Hz osc or
  * an external LFXTAL (on XT1).  The MCLK and SMCLK can be generated by XT2,
  * a multiplied XT2, or a multiplied XT1.
  */
#define MCU_PARAM_LFXTALHz              BOARD_PARAM_LFHz
#define MCU_PARAM_LFXTALtol             BOARD_PARAM_LFtol
//#define MCU_PARAM_LFOSCHz               BOARD_PARAM_LFHz
//#define MCU_PARAM_LFOSCtol              BOARD_PARAM_LFtol
//#define MCU_PARAM_XTALHz                BOARD_PARAM_HFHz
//#define MCU_PARAM_XTALmult              BOARD_PARAM_HFmult
//#define MCU_PARAM_XTALtol               BOARD_PARAM_HFtol
#define MCU_PARAM_OSCHz                 (BOARD_PARAM_HFHz*BOARD_PARAM_HFmult)
#define MCU_PARAM_OSCmult               BOARD_PARAM_HFmult
#define MCU_PARAM_OSCtol                BOARD_PARAM_HFtol


#define PLATFORM_MCLK_DIV           BOARD_PARAM_MCLKDIV
#define PLATFORM_SMCLK_DIV          BOARD_PARAM_SMCLKDIV

#define PLATFORM_LSCLOCK_PINS       BOARD_LFXT_PINS
#define PLATFORM_LSCLOCK_CONF       BOARD_LFXT_CONF
#define PLATFORM_HSCLOCK_PINS       BOARD_HFXT_PINS
#define PLATFORM_HSCLOCK_CONF       BOARD_HFXT_CONF
#define PLATFORM_LSCLOCK_HZ         BOARD_PARAM_LFHz
#define PLATFORM_LSCLOCK_ERROR      BOARD_PARAM_LFtol
#define PLATFORM_HSCLOCK_HZ         (BOARD_PARAM_HFHz*BOARD_PARAM_HFmult)
#define PLATFORM_HSCLOCK_ERROR      BOARD_PARAM_HFtol
#define PLATFORM_HSCLOCK_MULT       BOARD_PARAM_HFmult




/** Peripheral definitions for this platform <BR>
  * ========================================================================<BR>
  * OT_GPTIM:   General Purpose Timer used by OpenTag kernel                <BR>
  * OT_TRIG:    Optional test trigger usable in OpenTag apps (often LEDs)   <BR>
  * MPIPE:      UART to use for the MPipe                                   <BR>
  */
  
#define OT_GPTIM            TIM1A3
#define OT_GPTIM_IRQ        TIM1A3_IRQChannel
#define OT_GPTIM_VECTOR     TIMER1_A1_VECTOR
#define OT_GPTIM_CLOCK      32768
#define OT_GPTIM_RES        1024
#define TI_TO_CLK(VAL)      ((OT_GPTIM_RES/1024)*VAL)
#define CLK_TO_TI(VAL)      (VAL/(OT_GPTIM_RES/1024))

#if (OT_GPTIM_CLOCK == PLATFORM_LSCLOCK_HZ)
#   undef OT_GPTIM_CLOCK
#   define OT_GPTIM_CLOCK   TIMA_Ctl_Clock_ACLK
#   define OT_GPTIM_ERROR   PLATFORM_LSCLOCK_ERROR
#else
#   undef OT_GPTIM_CLOCK
#   define OT_GPTIM_CLOCK   TIMA_Ctl_Clock_MCLK
#   define OT_GPTIM_ERROR   PLATFORM_HSCLOCK_ERROR
#endif

#define OT_GPTIM_ERRDIV     32768 //this needs to be hard-coded for CCS




/** TNM2 Temp-sensor interface<BR>
  * ========================================================================<BR>
  * TNM2 is a 2-wire SPI device (not including Ground).  It is set-up such that
  * the TNM2 is the master and the CC430 is the Slave.
  *
  * Note: using the TNM2 requires an SPI peripheral, which means that either 
  * the heartbeat monitor or the accelerometer cannot be used.
  * 
  * - P2.0: SPI Clock port (input)
  * - P2.4: SPI Data in (input)
  */
#define TNM2_SPI_PORT       GPIO2
#define TNM2_SPI            SPIB0
#define TNM2_SPISCK_PIN     GPIO_Pin_0
#define TNM2_SPIMOSI_PIN    GPIO_Pin_4

#define TNM2_SPI_Px         P2M
#define TNM2_SPIMOSI_MAP    MAP4
#define TNM2_SPISCK_MAP     MAP0
#define TNM2_SPIMOSI_SIG    PM_UCB0SIMO
#define TNM2_SPISCK_SIG     PM_UCB0CLK




/** PWM control interface <BR>
  * ========================================================================<BR>
  * PWM uses TIM0A5 to generate the waveform.
  */
#define PWMTIM          TIM0A5
#define PWMTIM_PORT     GPIO2
#define PWMTIM_PIN      GPIO_Pin_1
#define PWMTIM_Px       P2M
#define PWMTIM_MAP      MAP1
#define PWMTIM_SIG      PM_TA0CCR0A
  



/** Standard OpenTag triggers<BR>
  * ========================================================================<BR>
  * There is no trigger in the Watch Implementation
  */
#define OT_TRIG1_PORTNUM    1
#define OT_TRIG1_PORT       PALFI_LED1_PORT
#define OT_TRIG1_PIN        PALFI_LED1_PIN
#define OT_TRIG1_HIDRIVE    DISABLED
#define OT_TRIG2_PORTNUM    1
#define OT_TRIG2_PORT       PALFI_LED2_PORT
#define OT_TRIG2_PIN        PALFI_LED2_PIN
#define OT_TRIG2_HIDRIVE    DISABLED




/** Heartbeat Monitor Sensor <BR>
  * ========================================================================<BR>
  * Unimplemented in this version
  */  


/** Accelerometer Sensor <BR>
  * ========================================================================<BR>
  * Unimplemented in this version
  */    
  

/** LCD Interface <BR>
  * ========================================================================<BR>
  * Unimplemented in this version
  */  
#define LCD_










// Pin that can be used for ADC-based random number (usually floating pin)
// You could also put on a low voltage, reverse-biased zener on the board
// to produce a pile of noise.  2.1V seems like a good value.
#define OT_GWNADC_PORT      GPIO2
#define OT_GWNADC_PIN       GPIO_Pin_2
#define OT_GWNADC_BITS      1
//#define OT_GWNZENER_PORT    GPIO2
//#define OT_GWNZENER_PIN     GPIO_Pin_4
//#define OT_GWNZENER_HIDRIVE DISABLED




/** MPipe (usually just for debugging on this board)
  * ========================================================================<BR>
  * MPipe must use I2C, because there is only a two-pin external connection,
  * and the UCA0 is tied to the PaLFi core.  UCA0 supports UART.  UCB0 supports
  * only SPI and I2C.
  */

#define MPIPE_I2C           I2CB0
#define MPIPE_I2C_SELF		0x01
#define MPIPE_I2C_TARGET	0x02

#define MPIPE_DMANUM        2

#define MPIPE_I2C_PORT      GPIO2
#define MPIPE_I2C_PORTMAP   P2M
#define MPIPE_I2C_SDAPIN    GPIO_Pin_1
#define MPIPE_I2C_SCLPIN    GPIO_Pin_0
#define MPIPE_I2C_PINS   	(MPIPE_I2C_SDAPIN | MPIPE_I2C_SCLPIN)

#define MPIPE_I2C_SCLSIG    PM_UCB0SCL
#define MPIPE_I2C_SDASIG    PM_UCB0SDA
#define MPIPE_I2C_RXTRIG	DMA_Trigger_UCB0RXIFG
#define MPIPE_I2C_TXTRIG	DMA_Trigger_UCB0TXIFG
#define MPIPE_I2C_VECTOR    USCI_B0_VECTOR

#if (MCU_FEATURE_MPIPEDMA == ENABLED)
#   if (MPIPE_DMANUM == 0)
#       define MPIPE_DMA     DMA0
#   elif (MPIPE_DMANUM == 1)
#       define MPIPE_DMA     DMA1
#   elif (MPIPE_DMANUM == 2)
#       define MPIPE_DMA     DMA2
#   else
#       error "MPIPE_DMANUM is not defined to an available index (0-2)"
#   endif
#endif

#define MPIPE_I2C_SCLMAP	MPIPE_I2C_PORTMAP->MAP0
#define MPIPE_I2C_SDAMAP	MPIPE_I2C_PORTMAP->MAP1





#if (MCU_FEATURE_MEMCPYDMA == ENABLED)
#   define MEMCPY_DMANUM    1
#   if (MEMCPY_DMANUM == 0)
#       define MEMCPY_DMA     DMA0
#   elif (MEMCPY_DMANUM == 1)
#       define MEMCPY_DMA     DMA1
#   elif (MEMCPY_DMANUM == 2)
#       define MEMCPY_DMA     DMA2
#   else
#       error "MEMCPY_DMANUM is not defined to an available index (0-2)"
#   endif
#endif








/******* ALL SHIT BELOW HERE IS SUBJECT TO REDEFINITION **********/


/** Flash Memory Setup: 
  * "OTF" means "Open Tag Flash," but if flash is not used, it just means 
  * storage memory.  Unfortunately this does not begin with F.
  */
#define OTF_VWORM_PAGES         (FLASH_FS_ALLOC/FLASH_PAGE_SIZE)
#define OTF_VWORM_FALLOW_PAGES  FLASH_FS_FALLOWS
#define OTF_VWORM_PAGESIZE      FLASH_PAGE_SIZE
#define OTF_VWORM_WORD_BYTES    FLASH_WORD_BYTES
#define OTF_VWORM_WORD_BITS     FLASH_WORD_BITS
#define OTF_VWORM_SIZE          (OTF_VWORM_PAGES * OTF_VWORM_PAGESIZE)
#define OTF_VWORM_START_PAGE    ((FLASH_FS_ADDR-FLASH_START_ADDR)/FLASH_PAGE_SIZE)
#define OTF_VWORM_START_ADDR    FLASH_FS_ADDR

#define OTF_M2_ENCODE_TABLE     ENABLED

// Total number of pages taken from program memory
#define OTF_TOTAL_PAGES         (OTF_VWORM_PAGES)




/** Abstracted Flash Organization: 
  * OpenTag uses Flash to store 2 kinds of data.  The default setup puts 
  * Filesystem memory in the back.
  * 1. Program code (obviously)
  * 2. Filesystem Memory
  *
  * FLASH_xxx constants are defined in the platform_config_xxx.h file.  
  */
#define OTF_TOTAL_SIZE          FLASH_FS_ALLOC
#define OTF_START_PAGE          OTF_VWORM_START_PAGE
#define OTF_START_ADDR          FLASH_FS_ADDR

#define OTF_VWORM_LAST_PAGE     (OTF_VWORM_START_PAGE + OTF_VWORM_PAGES - 1)
#define OTF_VWORM_END_ADDR      (FLASH_FS_ADDR + FLASH_FS_ALLOC - 1)






#endif
