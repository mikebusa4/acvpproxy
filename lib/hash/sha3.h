/*
 * Copyright (C) 2020, Stephan Mueller <smueller@chronox.de>
 *
 * License: see LICENSE file in root directory
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef SHA3_H
#define SHA3_H

#include "hash.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define SHA3_SIZE_BLOCK(bits)		((1600 - 2 * bits) >> 3)

/* SHA3-224 */
#define SHA3_224_SIZE_DIGEST_BITS	224
#define SHA3_224_SIZE_DIGEST		(SHA3_224_SIZE_DIGEST_BITS >> 3)
#define SHA3_224_SIZE_BLOCK		SHA3_SIZE_BLOCK(SHA3_224_SIZE_DIGEST_BITS)
extern const struct hash *sha3_224;

/* SHA3-256 */
#define SHA3_256_SIZE_DIGEST_BITS	256
#define SHA3_256_SIZE_DIGEST		(SHA3_256_SIZE_DIGEST_BITS >> 3)
#define SHA3_256_SIZE_BLOCK		SHA3_SIZE_BLOCK(SHA3_256_SIZE_DIGEST_BITS)
extern const struct hash *sha3_256;

/* SHA3-384 */
#define SHA3_384_SIZE_DIGEST_BITS	384
#define SHA3_384_SIZE_DIGEST		(SHA3_384_SIZE_DIGEST_BITS >> 3)
#define SHA3_384_SIZE_BLOCK		SHA3_SIZE_BLOCK(SHA3_384_SIZE_DIGEST_BITS)
extern const struct hash *sha3_384;

/* SHA3-512 */
#define SHA3_512_SIZE_DIGEST_BITS	512
#define SHA3_512_SIZE_DIGEST		(SHA3_512_SIZE_DIGEST_BITS >> 3)
#define SHA3_512_SIZE_BLOCK		SHA3_SIZE_BLOCK(SHA3_512_SIZE_DIGEST_BITS)
extern const struct hash *sha3_512;

/* Largest block size we support */
#define SHA3_MAX_SIZE_BLOCK		SHA3_224_SIZE_BLOCK

#ifdef __cplusplus
}
#endif

#endif /* SHA3_H */
