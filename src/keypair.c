// SPDX-License-Identifier: zlib license /* https://github.com/orlp/ed25519/tree/master  
// Copyright (C) 2022-2023 Orson Peters <orsonpeters@gmail.com>. All Rights Reserved

#include "ed25519.h"
#include "sha512.h"
#include "ge.h"
#include <string.h>

#ifndef WG_KEY_LEN
#define WG_KEY_LEN 32
#endif

void ed25519_create_keypair(unsigned char *public_key, unsigned char *private_key, const unsigned char *seed) {
    ge_p3 A;

    unsigned char hash[WG_KEY_LEN*2];
    int i=0;

    // hash = seed, and private_key = seed, where seed is 32 byte random
    memcpy(hash, seed, WG_KEY_LEN);
    memcpy(private_key, seed, WG_KEY_LEN);

     // hash = hash of private_key, if seed = private_key
    sha512(seed, 32, hash);

    // Clamp the hash
    hash[0] &= 248;
    hash[31] &= 63;
    hash[31] |= 64;

    // Scalar Mult
    ge_scalarmult_base(&A, hash);
    
    // P3 to bytes for public_key
    ge_p3_tobytes(public_key, &A);

    // Make secret key
    for (i = 0; i < 32; ++i) private_key[32 + i] = public_key[i];

/* Begin of NEAR CryptoSignKeyPair implementation
    // private_key = seed
    Array.Copy(seed, seedoffset, private_key , skoffset, 32);
    // hash = hash of private_key
    var h = Sha512.Hash(private_key, skoffset, 32);
    // Clamp the hash
    ScalarOperations.Clamp(h, 0);
    // Scalar Mult of hash
    GroupOperations.ScalarMultBase(out var A, h, 0);
    // P3 to bytes for public_key
    GroupOperations.P3ToBytes(public_key, pkoffset, ref A);
    // Make secret key
    for (i = 0; i < 32; ++i) private_key[skoffset + 32 + i] = public_key[pkoffset + i];
    */

}
