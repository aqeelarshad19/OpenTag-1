/* Copyright 2010-2012 JP Norair
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
  * @file       /otlib/OT_types.h
  * @author     JP Norair
  * @version    V1.0
  * @date       21 July 2012
  * @brief      Common casted types
  *
  ******************************************************************************
  */


#ifndef __OT_TYPES_H
#define __OT_TYPES_H





/** Data & Programming Constants: 
  * OpenTag uses several constants for the purpose of simplifying and 
  * elucidating the code.
  */

// Reset these if already defined.  
// True/False is defined in ot_bool type (see types section)
#   ifdef True
#       undef    True
#   endif
#   ifdef False
#       undef    False
#   endif

#   ifndef ENABLED
#       ifdef DISABLED
#           define ENABLED  (~DISABLED)
#       else
#           define ENABLED  1
#       endif
#   endif
#   ifndef DISABLED
#       define DISABLED     0
#   endif
#   if (DISABLED == ENABLED)
#       undef ENABLED
#       define ENABLED      (~DISABLED)
#   endif

#   ifndef NULL
#       define NULL 0
#   endif



/** @typedef ot_bool
  * Boolean, takes True or False
  */
#ifdef __STDC_VERSION__
#   if (__STDC_VERSION__ >= 199901L)
#       define __HAS_C99
#   endif
#endif
#ifdef __HAS_C99
#   include <stdbool.h>
#   define ot_bool  bool
#   define True     true
#   define False    false
#else
    typedef enum { False = 0, True = !False } ot_bool;
#endif



/** @typedef ot_s8
  * equivalent to @c signed @c char
  */
typedef signed char         ot_s8;
    
/** @typedef ot_u8
  * equivalent to @c unsigned @c char
  */
typedef unsigned char       ot_u8;
    
/** @typedef ot_int
  * Generic integer: typically equivalent to @c signed @c short but may need to 
  * be re-evaluated if OpenTag is ported to an 8bit platform, since intg is the
  * default integer value in OpenTag
  */
typedef signed short        ot_int;
typedef signed short        ot_s16;
    
/** @typedef ot_uint
  * Generic unsigned integer: typically equivalent to @c unsigned @c short but 
  * may need to be re-evaluated if OpenTag is ported to an 8bit platform, since 
  * uintg is the default unsigned integer value in OpenTag
  */
typedef unsigned short      ot_uint;
typedef unsigned short      ot_u16;
    
/** @typedef ot_long
  * equivalent to @c signed @c long.  A word in OpenTag is ALWAYS 32 bits.
  */
typedef signed long         ot_long;
typedef signed long         ot_s32;
    
    
/** @typedef ot_ulong
  * equivalent to @c unsigned @c long.  A word in OpenTag is ALWAYS 32 bits.
  */
typedef unsigned long       ot_ulong;
typedef unsigned long       ot_u32;
    
        
/** @typedef ot_uni16
  * A union of 2 byte (16 bit) raw data types.  Useful for datastream parsing.
  */
typedef union {
    ot_u16 ushort;
    ot_s16 sshort;
    ot_u8  ubyte[2];
    ot_s8  sbyte[2];
} ot_uni16;

/** @typedef ot_uni32
  * A union of 4 byte (32 bit) raw data types.  Useful for datastream parsing.
  */
typedef union {
    ot_u32 ulong;
    ot_s32 slong;
    ot_u16 ushort[2];
    ot_s16 sshort;
    ot_u8  ubyte[4];
    ot_s8  sbyte[4];
} ot_uni32;


// Deprecated Union definitions
#define Twobytes    ot_uni16
#define Fourbytes   ot_uni32


/** @typedef ot_sub
  * Pure subroutine pointer that can be used nicely in manual jump tables
  * looks like: void subroutine(void)
  */
typedef void (*ot_sub)(void);


/** @typedef ot_sig
  * One-argument signal callback (classic POSIX)
  * looks like: void callback(ot_int)
  */
typedef void (*ot_sig)(ot_int);


/** @typedef ot_sig2
  * Two-argument signal callback
  * looks like: void callback(ot_int, ot_int)
  */
typedef void (*ot_sig2)(ot_int, ot_int);


/** @typedef ot_sigv
  * void-pointer-argument signal callback (endless possibilities)
  * looks like: void callback(void*)
  */
typedef void (*ot_sigv)(void*);


#endif 

