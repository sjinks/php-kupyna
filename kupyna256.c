#include <string.h>
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

static void P(uint64_t* x, uint64_t* y, uint64_t round)
{
    for (uint_fast32_t idx=0; idx<8; ++idx) {
        x[idx] ^= (idx << 4) ^ round;
    }

    G(x, y);
}

static void Q(uint64_t* x, uint64_t* y, uint64_t i)
{
    for (uint_fast32_t j = 0; j < 8; ++j) {
        x[j] += (0x00F0F0F0F0F0F0F3ULL ^ (((uint64_t)(((7 - j) * 0x10) ^ i)) << 56));
    }

    G(x, y);
}

static void outputTransform(struct kupyna256_ctx_t* ctx)
{
    union uint512_t t1;
    union uint512_t t2;

    memcpy(t1.q, ctx->h.q, sizeof(t1));

    for (uint8_t r = 0; r < 10; r += 2) {
        P(t1.q, t2.q, r);
        P(t2.q, t1.q, r + 1);
    }

    for (int column = 0; column < 8; ++column) {
        ctx->h.q[column] ^= t1.q[column];
    }
}

static void transform(struct kupyna256_ctx_t* ctx)
{
    union uint512_t AQ1;
    union uint512_t AP1;
    union uint512_t tmp;

    for (int column = 0; column < 8; ++column) {
        AP1.q[column] = ctx->h.q[column] ^ ctx->m.q[column];
        AQ1.q[column] = ctx->m.q[column];
    }

    for (uint8_t r = 0; r < 10; r += 2) {
        P(AP1.q, tmp.q, r);
        P(tmp.q, AP1.q, r + 1);
        Q(AQ1.q, tmp.q, r);
        Q(tmp.q, AQ1.q, r + 1);
    }

    for (int column = 0; column < 8; ++column) {
        ctx->h.q[column] ^= AP1.q[column] ^ AQ1.q[column];
    }
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
        transform(ctx);
        len        -= 64 - ctx->pos;
        ctx->total += (64 - ctx->pos) * 8;
        data       += 64 - ctx->pos;
        ctx->pos    = 0;
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
        transform(ctx);
        ctx->pos = 0;
    }

    memset(ctx->m.b + ctx->pos, 0,           52 - ctx->pos);
    memcpy(ctx->m.b + 52,       &ctx->total, sizeof(uint64_t));
    memset(ctx->m.b + 60,       0,           4);

    transform(ctx);
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
        transform(ctx);
        ctx->pos = 0;
    }

    memset(ctx->m.b + ctx->pos, 0,           52 - ctx->pos);
    memcpy(ctx->m.b + 52,       &ctx->total, sizeof(uint64_t));
    memset(ctx->m.b + 60,       0,           4);

    transform(ctx);
    outputTransform(ctx);

    memcpy(hash, ctx->h.b + 64 - bits/8, bits/8);
}
