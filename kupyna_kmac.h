#ifndef KUPYNA_KMAC_H
#define KUPYNA_KMAC_H

#include <stdint.h>
#include "kupyna256.h"
#include "kupyna512.h"

struct kupyna256_kmac_ctx_t {
    struct kupyna256_ctx_t hctx;
    uint8_t ik[32];
    uint64_t len;
};

struct kupyna384_kmac_ctx_t {
    struct kupyna512_ctx_t hctx;
    uint8_t ik[48];
    uint64_t len;
};

struct kupyna512_kmac_ctx_t {
    struct kupyna512_ctx_t hctx;
    uint8_t ik[64];
    uint64_t len;
};

void kupyna256_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac);
void kupyna384_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac);
void kupyna512_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac);

void kupyna256_kmac_init(struct kupyna256_kmac_ctx_t* ctx, const uint8_t* key);
void kupyna256_kmac_update(struct kupyna256_kmac_ctx_t* ctx, const uint8_t* data, size_t len);
void kupyna256_kmac_final(struct kupyna256_kmac_ctx_t* ctx, uint8_t* mac);

void kupyna384_kmac_init(struct kupyna384_kmac_ctx_t* ctx, const uint8_t* key);
void kupyna384_kmac_update(struct kupyna384_kmac_ctx_t* ctx, const uint8_t* data, size_t len);
void kupyna384_kmac_final(struct kupyna384_kmac_ctx_t* ctx, uint8_t* mac);

void kupyna512_kmac_init(struct kupyna512_kmac_ctx_t* ctx, const uint8_t* key);
void kupyna512_kmac_update(struct kupyna512_kmac_ctx_t* ctx, const uint8_t* data, size_t len);
void kupyna512_kmac_final(struct kupyna512_kmac_ctx_t* ctx, uint8_t* mac);

#endif /* KUPYNA_KMAC_H */
