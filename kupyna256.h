#ifndef KUPYNA256_H_
#define KUPYNA256_H_

#include <stdint.h>
#if defined(__SSE2__)
#include <emmintrin.h>
#elif defined(__SSE__)
#include <xmmintrin.h>
#endif

union uint512_t {
#if defined(__SSE2__)
    __m128i h[4];
#elif defined(__SSE__)
    __m128 h[4];
#endif
    uint64_t q[8];
    uint8_t b[64];
};

struct kupyna256_ctx_t {
    union uint512_t h;
    union uint512_t m;
    size_t pos;
    uint64_t total;
};

void kupyna256_init(struct kupyna256_ctx_t* ctx);
void kupyna256_update(struct kupyna256_ctx_t* ctx, const uint8_t* data, size_t len);
void kupyna256_final(struct kupyna256_ctx_t* ctx, uint8_t* hash);
void kupyna256_final2(struct kupyna256_ctx_t* ctx, uint8_t* hash, size_t bits);

#endif /* KUPYNA256_H_ */
