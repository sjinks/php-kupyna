#include <string.h>
#include <assert.h>
#include "kupyna256.h"
#include "kupyna_tables.h"

static inline void G(const uint64_t* x, uint64_t* y)
{
    y[0] = T0[(uint8_t)x[0]] ^ T1[(uint8_t)(x[7] >> 8)] ^ T2[(uint8_t)(x[6] >> 16)] ^ T3[(uint8_t)(x[5] >> 24)] ^ T4[(uint8_t)(x[4] >> 32)] ^ T5[(uint8_t)(x[3] >> 40)] ^ T6[(uint8_t)(x[2] >> 48)] ^ T7[(uint8_t)(x[1] >> 56)];
    y[1] = T0[(uint8_t)x[1]] ^ T1[(uint8_t)(x[0] >> 8)] ^ T2[(uint8_t)(x[7] >> 16)] ^ T3[(uint8_t)(x[6] >> 24)] ^ T4[(uint8_t)(x[5] >> 32)] ^ T5[(uint8_t)(x[4] >> 40)] ^ T6[(uint8_t)(x[3] >> 48)] ^ T7[(uint8_t)(x[2] >> 56)];
    y[2] = T0[(uint8_t)x[2]] ^ T1[(uint8_t)(x[1] >> 8)] ^ T2[(uint8_t)(x[0] >> 16)] ^ T3[(uint8_t)(x[7] >> 24)] ^ T4[(uint8_t)(x[6] >> 32)] ^ T5[(uint8_t)(x[5] >> 40)] ^ T6[(uint8_t)(x[4] >> 48)] ^ T7[(uint8_t)(x[3] >> 56)];
    y[3] = T0[(uint8_t)x[3]] ^ T1[(uint8_t)(x[2] >> 8)] ^ T2[(uint8_t)(x[1] >> 16)] ^ T3[(uint8_t)(x[0] >> 24)] ^ T4[(uint8_t)(x[7] >> 32)] ^ T5[(uint8_t)(x[6] >> 40)] ^ T6[(uint8_t)(x[5] >> 48)] ^ T7[(uint8_t)(x[4] >> 56)];
    y[4] = T0[(uint8_t)x[4]] ^ T1[(uint8_t)(x[3] >> 8)] ^ T2[(uint8_t)(x[2] >> 16)] ^ T3[(uint8_t)(x[1] >> 24)] ^ T4[(uint8_t)(x[0] >> 32)] ^ T5[(uint8_t)(x[7] >> 40)] ^ T6[(uint8_t)(x[6] >> 48)] ^ T7[(uint8_t)(x[5] >> 56)];
    y[5] = T0[(uint8_t)x[5]] ^ T1[(uint8_t)(x[4] >> 8)] ^ T2[(uint8_t)(x[3] >> 16)] ^ T3[(uint8_t)(x[2] >> 24)] ^ T4[(uint8_t)(x[1] >> 32)] ^ T5[(uint8_t)(x[0] >> 40)] ^ T6[(uint8_t)(x[7] >> 48)] ^ T7[(uint8_t)(x[6] >> 56)];
    y[6] = T0[(uint8_t)x[6]] ^ T1[(uint8_t)(x[5] >> 8)] ^ T2[(uint8_t)(x[4] >> 16)] ^ T3[(uint8_t)(x[3] >> 24)] ^ T4[(uint8_t)(x[2] >> 32)] ^ T5[(uint8_t)(x[1] >> 40)] ^ T6[(uint8_t)(x[0] >> 48)] ^ T7[(uint8_t)(x[7] >> 56)];
    y[7] = T0[(uint8_t)x[7]] ^ T1[(uint8_t)(x[6] >> 8)] ^ T2[(uint8_t)(x[5] >> 16)] ^ T3[(uint8_t)(x[4] >> 24)] ^ T4[(uint8_t)(x[3] >> 32)] ^ T5[(uint8_t)(x[2] >> 40)] ^ T6[(uint8_t)(x[1] >> 48)] ^ T7[(uint8_t)(x[0] >> 56)];
}

static inline void G1(const uint64_t* x, uint64_t* y, uint64_t round)
{
    y[0] = T0[(uint8_t)x[0]] ^ T1[(uint8_t)(x[7] >> 8)] ^ T2[(uint8_t)(x[6] >> 16)] ^ T3[(uint8_t)(x[5] >> 24)] ^ T4[(uint8_t)(x[4] >> 32)] ^ T5[(uint8_t)(x[3] >> 40)] ^ T6[(uint8_t)(x[2] >> 48)] ^ T7[(uint8_t)(x[1] >> 56)] ^ (0 << 4) ^ round;
    y[1] = T0[(uint8_t)x[1]] ^ T1[(uint8_t)(x[0] >> 8)] ^ T2[(uint8_t)(x[7] >> 16)] ^ T3[(uint8_t)(x[6] >> 24)] ^ T4[(uint8_t)(x[5] >> 32)] ^ T5[(uint8_t)(x[4] >> 40)] ^ T6[(uint8_t)(x[3] >> 48)] ^ T7[(uint8_t)(x[2] >> 56)] ^ (1 << 4) ^ round;
    y[2] = T0[(uint8_t)x[2]] ^ T1[(uint8_t)(x[1] >> 8)] ^ T2[(uint8_t)(x[0] >> 16)] ^ T3[(uint8_t)(x[7] >> 24)] ^ T4[(uint8_t)(x[6] >> 32)] ^ T5[(uint8_t)(x[5] >> 40)] ^ T6[(uint8_t)(x[4] >> 48)] ^ T7[(uint8_t)(x[3] >> 56)] ^ (2 << 4) ^ round;
    y[3] = T0[(uint8_t)x[3]] ^ T1[(uint8_t)(x[2] >> 8)] ^ T2[(uint8_t)(x[1] >> 16)] ^ T3[(uint8_t)(x[0] >> 24)] ^ T4[(uint8_t)(x[7] >> 32)] ^ T5[(uint8_t)(x[6] >> 40)] ^ T6[(uint8_t)(x[5] >> 48)] ^ T7[(uint8_t)(x[4] >> 56)] ^ (3 << 4) ^ round;
    y[4] = T0[(uint8_t)x[4]] ^ T1[(uint8_t)(x[3] >> 8)] ^ T2[(uint8_t)(x[2] >> 16)] ^ T3[(uint8_t)(x[1] >> 24)] ^ T4[(uint8_t)(x[0] >> 32)] ^ T5[(uint8_t)(x[7] >> 40)] ^ T6[(uint8_t)(x[6] >> 48)] ^ T7[(uint8_t)(x[5] >> 56)] ^ (4 << 4) ^ round;
    y[5] = T0[(uint8_t)x[5]] ^ T1[(uint8_t)(x[4] >> 8)] ^ T2[(uint8_t)(x[3] >> 16)] ^ T3[(uint8_t)(x[2] >> 24)] ^ T4[(uint8_t)(x[1] >> 32)] ^ T5[(uint8_t)(x[0] >> 40)] ^ T6[(uint8_t)(x[7] >> 48)] ^ T7[(uint8_t)(x[6] >> 56)] ^ (5 << 4) ^ round;
    y[6] = T0[(uint8_t)x[6]] ^ T1[(uint8_t)(x[5] >> 8)] ^ T2[(uint8_t)(x[4] >> 16)] ^ T3[(uint8_t)(x[3] >> 24)] ^ T4[(uint8_t)(x[2] >> 32)] ^ T5[(uint8_t)(x[1] >> 40)] ^ T6[(uint8_t)(x[0] >> 48)] ^ T7[(uint8_t)(x[7] >> 56)] ^ (6 << 4) ^ round;
    y[7] = T0[(uint8_t)x[7]] ^ T1[(uint8_t)(x[6] >> 8)] ^ T2[(uint8_t)(x[5] >> 16)] ^ T3[(uint8_t)(x[4] >> 24)] ^ T4[(uint8_t)(x[3] >> 32)] ^ T5[(uint8_t)(x[2] >> 40)] ^ T6[(uint8_t)(x[1] >> 48)] ^ T7[(uint8_t)(x[0] >> 56)] ^ (7 << 4) ^ round;
}

static inline void G2(const uint64_t* x, uint64_t* y, uint64_t round)
{
    y[0] = (T0[(uint8_t)x[0]] ^ T1[(uint8_t)(x[7] >> 8)] ^ T2[(uint8_t)(x[6] >> 16)] ^ T3[(uint8_t)(x[5] >> 24)] ^ T4[(uint8_t)(x[4] >> 32)] ^ T5[(uint8_t)(x[3] >> 40)] ^ T6[(uint8_t)(x[2] >> 48)] ^ T7[(uint8_t)(x[1] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 0) * 0x10) ^ round)) << 56));
    y[1] = (T0[(uint8_t)x[1]] ^ T1[(uint8_t)(x[0] >> 8)] ^ T2[(uint8_t)(x[7] >> 16)] ^ T3[(uint8_t)(x[6] >> 24)] ^ T4[(uint8_t)(x[5] >> 32)] ^ T5[(uint8_t)(x[4] >> 40)] ^ T6[(uint8_t)(x[3] >> 48)] ^ T7[(uint8_t)(x[2] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 1) * 0x10) ^ round)) << 56));
    y[2] = (T0[(uint8_t)x[2]] ^ T1[(uint8_t)(x[1] >> 8)] ^ T2[(uint8_t)(x[0] >> 16)] ^ T3[(uint8_t)(x[7] >> 24)] ^ T4[(uint8_t)(x[6] >> 32)] ^ T5[(uint8_t)(x[5] >> 40)] ^ T6[(uint8_t)(x[4] >> 48)] ^ T7[(uint8_t)(x[3] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 2) * 0x10) ^ round)) << 56));
    y[3] = (T0[(uint8_t)x[3]] ^ T1[(uint8_t)(x[2] >> 8)] ^ T2[(uint8_t)(x[1] >> 16)] ^ T3[(uint8_t)(x[0] >> 24)] ^ T4[(uint8_t)(x[7] >> 32)] ^ T5[(uint8_t)(x[6] >> 40)] ^ T6[(uint8_t)(x[5] >> 48)] ^ T7[(uint8_t)(x[4] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 3) * 0x10) ^ round)) << 56));
    y[4] = (T0[(uint8_t)x[4]] ^ T1[(uint8_t)(x[3] >> 8)] ^ T2[(uint8_t)(x[2] >> 16)] ^ T3[(uint8_t)(x[1] >> 24)] ^ T4[(uint8_t)(x[0] >> 32)] ^ T5[(uint8_t)(x[7] >> 40)] ^ T6[(uint8_t)(x[6] >> 48)] ^ T7[(uint8_t)(x[5] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 4) * 0x10) ^ round)) << 56));
    y[5] = (T0[(uint8_t)x[5]] ^ T1[(uint8_t)(x[4] >> 8)] ^ T2[(uint8_t)(x[3] >> 16)] ^ T3[(uint8_t)(x[2] >> 24)] ^ T4[(uint8_t)(x[1] >> 32)] ^ T5[(uint8_t)(x[0] >> 40)] ^ T6[(uint8_t)(x[7] >> 48)] ^ T7[(uint8_t)(x[6] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 5) * 0x10) ^ round)) << 56));
    y[6] = (T0[(uint8_t)x[6]] ^ T1[(uint8_t)(x[5] >> 8)] ^ T2[(uint8_t)(x[4] >> 16)] ^ T3[(uint8_t)(x[3] >> 24)] ^ T4[(uint8_t)(x[2] >> 32)] ^ T5[(uint8_t)(x[1] >> 40)] ^ T6[(uint8_t)(x[0] >> 48)] ^ T7[(uint8_t)(x[7] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 6) * 0x10) ^ round)) << 56));
    y[7] = (T0[(uint8_t)x[7]] ^ T1[(uint8_t)(x[6] >> 8)] ^ T2[(uint8_t)(x[5] >> 16)] ^ T3[(uint8_t)(x[4] >> 24)] ^ T4[(uint8_t)(x[3] >> 32)] ^ T5[(uint8_t)(x[2] >> 40)] ^ T6[(uint8_t)(x[1] >> 48)] ^ T7[(uint8_t)(x[0] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((7 - 7) * 0x10) ^ round)) << 56));
}

static inline void P(uint64_t* x, uint64_t* y, uint64_t round)
{
    for (uint_fast32_t idx=0; idx<8; ++idx) {
        x[idx] ^= (idx << 4) ^ round;
    }

    G1(x, y, round + 1);
    G(y, x);
}

static inline void Q(uint64_t* x, uint64_t* y, uint64_t round)
{
    for (uint_fast32_t j = 0; j < 8; ++j) {
        x[j] += (0x00F0F0F0F0F0F0F3ULL ^ (((uint64_t)(((7 - j) * 0x10) ^ round)) << 56));
    }

    G2(x, y, round + 1);
    G(y, x);
}

static void outputTransform(struct kupyna256_ctx_t* ctx)
{
    union uint512_t t1;
    union uint512_t t2;

    memcpy(t1.q, ctx->h.q, sizeof(t1));

    for (uint8_t r = 0; r < 10; r += 2) {
        P(t1.q, t2.q, r);
    }

#if defined(__SSE2__)
    for (uint_fast32_t column=0; column<4; column+=2) {
        ctx->h.h[column]   = _mm_xor_si128(ctx->h.h[column],   t1.h[column]);
        ctx->h.h[column+1] = _mm_xor_si128(ctx->h.h[column+1], t1.h[column+1]);
    }
#elif defined(__SSE__)
    for (uint_fast32_t column=0; column<4; ++column) {
        ctx->h.h[column] = _mm_xor_ps(ctx->h.h[column], t1.h[column]);
    }
#else
    for (uint_fast32_t column=0; column<8; ++column) {
        ctx->h.q[column] ^= t1.q[column];
    }
#endif
}

static void transform(struct kupyna256_ctx_t* ctx, const union uint512_t* b)
{
    union uint512_t AQ1;
    union uint512_t AP1;
    union uint512_t tmp;

#if defined(__SSE2__)
    __m128i m1 = _mm_load_si128(b->h);
    __m128i m2 = _mm_load_si128(b->h + 1);
    __m128i m3 = _mm_load_si128(b->h + 2);
    __m128i m4 = _mm_load_si128(b->h + 3);
    AP1.h[0]   = _mm_xor_si128(ctx->h.h[0], m1);
    AP1.h[1]   = _mm_xor_si128(ctx->h.h[1], m2);
    AP1.h[2]   = _mm_xor_si128(ctx->h.h[2], m3);
    AP1.h[3]   = _mm_xor_si128(ctx->h.h[3], m4);
    _mm_store_si128(AQ1.h,     m1);
    _mm_store_si128(AQ1.h + 1, m2);
    _mm_store_si128(AQ1.h + 2, m3);
    _mm_store_si128(AQ1.h + 3, m4);
#elif defined(__SSE__)
    __m128 m1 = _mm_load_ps((float*)(b->h));
    __m128 m2 = _mm_load_ps((float*)(b->h + 1));
    __m128 m3 = _mm_load_ps((float*)(b->h + 2));
    __m128 m4 = _mm_load_ps((float*)(b->h + 3));
    AP1.h[0] = _mm_xor_ps(ctx->h.h[0], m1);
    AP1.h[1] = _mm_xor_ps(ctx->h.h[1], m2);
    AP1.h[2] = _mm_xor_ps(ctx->h.h[2], m3);
    AP1.h[3] = _mm_xor_ps(ctx->h.h[3], m4);
    _mm_store_ps((float*)(AQ1.h),     m1);
    _mm_store_ps((float*)(AQ1.h + 1), m2);
    _mm_store_ps((float*)(AQ1.h + 2), m3);
    _mm_store_ps((float*)(AQ1.h + 3), m4);
#else
    for (uint_fast32_t column=0; column<8; ++column) {
        AP1.q[column] = ctx->h.q[column] ^ b->q[column];
        AQ1.q[column] = b->q[column];
    }
#endif

    for (uint8_t r = 0; r < 10; r += 2) {
        P(AP1.q, tmp.q, r);
        Q(AQ1.q, tmp.q, r);
    }

#if defined(__SSE2__)
    ctx->h.h[0] = _mm_xor_si128(ctx->h.h[0], _mm_xor_si128(AQ1.h[0], AP1.h[0]));
    ctx->h.h[1] = _mm_xor_si128(ctx->h.h[1], _mm_xor_si128(AQ1.h[1], AP1.h[1]));
    ctx->h.h[2] = _mm_xor_si128(ctx->h.h[2], _mm_xor_si128(AQ1.h[2], AP1.h[2]));
    ctx->h.h[3] = _mm_xor_si128(ctx->h.h[3], _mm_xor_si128(AQ1.h[3], AP1.h[3]));
#elif defined(__SSE__)
    ctx->h.h[0] = _mm_xor_ps(ctx->h.h[0], _mm_xor_ps(AQ1.h[0], AP1.h[0]));
    ctx->h.h[1] = _mm_xor_ps(ctx->h.h[1], _mm_xor_ps(AQ1.h[1], AP1.h[1]));
    ctx->h.h[2] = _mm_xor_ps(ctx->h.h[2], _mm_xor_ps(AQ1.h[2], AP1.h[2]));
    ctx->h.h[3] = _mm_xor_ps(ctx->h.h[3], _mm_xor_ps(AQ1.h[3], AP1.h[3]));
#else
    for (uint_fast32_t column=0; column<8; ++column) {
        ctx->h.q[column] ^= AP1.q[column] ^ AQ1.q[column];
    }
#endif
}

void kupyna256_init(struct kupyna256_ctx_t* ctx)
{
    ctx->pos    = 0;
    ctx->total  = 0;
    memset(ctx->h.q, 0, sizeof(ctx->h.q));
    ctx->h.b[0] = 64;
}

void kupyna256_update(struct kupyna256_ctx_t* ctx, const uint8_t* data, size_t len)
{
    while (ctx->pos + len >= 64) {
        memcpy(ctx->m.b + ctx->pos, data, 64 - ctx->pos);
        transform(ctx, &ctx->m);
        len        -= 64 - ctx->pos;
        ctx->total += (64 - ctx->pos) * 8;
        data       += 64 - ctx->pos;
        ctx->pos    = 0;
    }

    memcpy(ctx->m.b + ctx->pos, data, len);
    ctx->pos   += len;
    ctx->total += len * 8;
}

void kupyna256_update_aligned(struct kupyna256_ctx_t* ctx, const uint8_t* data, size_t len)
{
    assert(((size_t)data & 0x0F) == 0);

    if (ctx->pos && ctx->pos + len >= 64) {
        memcpy(ctx->m.b + ctx->pos, data, 64 - ctx->pos);
        transform(ctx, &ctx->m);
        len        -= 64 - ctx->pos;
        ctx->total += (64 - ctx->pos) * 8;
        data       += 64 - ctx->pos;
        ctx->pos    = 0;
    }

    while (len >= 64) {
        transform(ctx, (union uint512_t*)data);
        len        -= 64;
        ctx->total += 64  * 8;
        data       += 64;
    }

    memcpy(ctx->m.b + ctx->pos, data, len);
    ctx->pos   += len;
    ctx->total += len * 8;
}

void kupyna256_final(struct kupyna256_ctx_t* ctx, uint8_t* hash)
{
    ctx->m.b[ctx->pos] = 0x80;
    ++ctx->pos;
    if (ctx->pos > 52) {
        memset(ctx->m.b + ctx->pos, 0, 64 - ctx->pos);
        transform(ctx, &ctx->m);
        ctx->pos = 0;
    }

    memset(ctx->m.b + ctx->pos, 0,           64 - ctx->pos);
    memcpy(ctx->m.b + 52,       &ctx->total, sizeof(uint64_t));

    transform(ctx, &ctx->m);
    outputTransform(ctx);

    memcpy(hash, ctx->h.b + 64 - 256/8, 256/8);
}

void kupyna256_final2(struct kupyna256_ctx_t* ctx, uint8_t* hash, size_t bits)
{
    if (bits > 256) {
        bits = 256;
    }

    ctx->m.b[ctx->pos] = 0x80;
    ++ctx->pos;
    if (ctx->pos > 52) {
        memset(ctx->m.b + ctx->pos, 0, 64 - ctx->pos);
        transform(ctx, &ctx->m);
        ctx->pos = 0;
    }

    memset(ctx->m.b + ctx->pos, 0,           64 - ctx->pos);
    memcpy(ctx->m.b + 52,       &ctx->total, sizeof(uint64_t));

    transform(ctx, &ctx->m);
    outputTransform(ctx);

    memcpy(hash, ctx->h.b + 64 - bits/8, bits/8);
}
