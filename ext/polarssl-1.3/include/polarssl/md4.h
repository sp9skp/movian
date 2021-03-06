/**
 * \file md4.h
 *
 * \brief MD4 message digest algorithm (hash function)
 *
 *  Copyright (C) 2006-2014, ARM Limited, All Rights Reserved
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * \warning   MD4 is considered a weak message digest and its use constitutes a
 *            security risk. We recommend considering stronger message digests
 *            instead.
 *
 */
#ifndef POLARSSL_MD4_H
#define POLARSSL_MD4_H

#if !defined(POLARSSL_CONFIG_FILE)
#include "config.h"
#else
#include POLARSSL_CONFIG_FILE
#endif

#include <stddef.h>

#if defined(_MSC_VER) && !defined(EFIX64) && !defined(EFI32)
#include <basetsd.h>
typedef UINT32 uint32_t;
#else
#include <inttypes.h>
#endif

#define POLARSSL_ERR_MD4_FILE_IO_ERROR                 -0x0072  /**< Read/write error in file. */

#if !defined(POLARSSL_MD4_ALT)
// Regular implementation
//

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          MD4 context structure
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
typedef struct
{
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[4];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */

    unsigned char ipad[64];     /*!< HMAC: inner padding        */
    unsigned char opad[64];     /*!< HMAC: outer padding        */
}
md4_context;

/**
 * \brief          Initialize MD4 context
 *
 * \param ctx      MD4 context to be initialized
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_init( md4_context *ctx );

/**
 * \brief          Clear MD4 context
 *
 * \param ctx      MD4 context to be cleared
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_free( md4_context *ctx );

/**
 * \brief          MD4 context setup
 *
 * \param ctx      context to be initialized
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_starts( md4_context *ctx );

/**
 * \brief          MD4 process buffer
 *
 * \param ctx      MD4 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_update( md4_context *ctx, const unsigned char *input, size_t ilen );

/**
 * \brief          MD4 final digest
 *
 * \param ctx      MD4 context
 * \param output   MD4 checksum result
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_finish( md4_context *ctx, unsigned char output[16] );

#ifdef __cplusplus
}
#endif

#else  /* POLARSSL_MD4_ALT */
#include "md4_alt.h"
#endif /* POLARSSL_MD4_ALT */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Output = MD4( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   MD4 checksum result
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4( const unsigned char *input, size_t ilen, unsigned char output[16] );

/**
 * \brief          Output = MD4( file contents )
 *
 * \param path     input file name
 * \param output   MD4 checksum result
 *
 * \return         0 if successful, or POLARSSL_ERR_MD4_FILE_IO_ERROR
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int md4_file( const char *path, unsigned char output[16] );

/**
 * \brief          MD4 HMAC context setup
 *
 * \param ctx      HMAC context to be initialized
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_hmac_starts( md4_context *ctx, const unsigned char *key,
                      size_t keylen );

/**
 * \brief          MD4 HMAC process buffer
 *
 * \param ctx      HMAC context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_hmac_update( md4_context *ctx, const unsigned char *input,
                      size_t ilen );

/**
 * \brief          MD4 HMAC final digest
 *
 * \param ctx      HMAC context
 * \param output   MD4 HMAC checksum result
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_hmac_finish( md4_context *ctx, unsigned char output[16] );

/**
 * \brief          MD4 HMAC context reset
 *
 * \param ctx      HMAC context to be reset
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_hmac_reset( md4_context *ctx );

/**
 * \brief          Output = HMAC-MD4( hmac key, input buffer )
 *
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   HMAC-MD4 result
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
void md4_hmac( const unsigned char *key, size_t keylen,
               const unsigned char *input, size_t ilen,
               unsigned char output[16] );

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 *
 * \warning        MD4 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int md4_self_test( int verbose );

/* Internal use */
void md4_process( md4_context *ctx, const unsigned char data[64] );

#ifdef __cplusplus
}
#endif

#endif /* md4.h */
