#include <string.h>
#include <assert.h>
#include "kupyna512.h"
#include "kupyna_tables.h"

static inline void G(const uint64_t* x, uint64_t* y)
{
    y[0]  = T0[(uint8_t)x[0]]  ^ T1[(uint8_t)(x[15] >> 8)] ^ T2[(uint8_t)(x[14] >> 16)] ^ T3[(uint8_t)(x[13] >> 24)] ^ T4[(uint8_t)(x[12] >> 32)] ^ T5[(uint8_t)(x[11] >> 40)] ^ T6[(uint8_t)(x[10] >> 48)] ^ T7[(uint8_t)(x[5] >> 56)];
    y[1]  = T0[(uint8_t)x[1]]  ^ T1[(uint8_t)(x[0] >> 8)]  ^ T2[(uint8_t)(x[15] >> 16)] ^ T3[(uint8_t)(x[14] >> 24)] ^ T4[(uint8_t)(x[13] >> 32)] ^ T5[(uint8_t)(x[12] >> 40)] ^ T6[(uint8_t)(x[11] >> 48)] ^ T7[(uint8_t)(x[6] >> 56)];
    y[2]  = T0[(uint8_t)x[2]]  ^ T1[(uint8_t)(x[1] >> 8)]  ^ T2[(uint8_t)(x[0] >> 16)]  ^ T3[(uint8_t)(x[15] >> 24)] ^ T4[(uint8_t)(x[14] >> 32)] ^ T5[(uint8_t)(x[13] >> 40)] ^ T6[(uint8_t)(x[12] >> 48)] ^ T7[(uint8_t)(x[7] >> 56)];
    y[3]  = T0[(uint8_t)x[3]]  ^ T1[(uint8_t)(x[2] >> 8)]  ^ T2[(uint8_t)(x[1] >> 16)]  ^ T3[(uint8_t)(x[0] >> 24)]  ^ T4[(uint8_t)(x[15] >> 32)] ^ T5[(uint8_t)(x[14] >> 40)] ^ T6[(uint8_t)(x[13] >> 48)] ^ T7[(uint8_t)(x[8] >> 56)];
    y[4]  = T0[(uint8_t)x[4]]  ^ T1[(uint8_t)(x[3] >> 8)]  ^ T2[(uint8_t)(x[2] >> 16)]  ^ T3[(uint8_t)(x[1] >> 24)]  ^ T4[(uint8_t)(x[0] >> 32)]  ^ T5[(uint8_t)(x[15] >> 40)] ^ T6[(uint8_t)(x[14] >> 48)] ^ T7[(uint8_t)(x[9] >> 56)];
    y[5]  = T0[(uint8_t)x[5]]  ^ T1[(uint8_t)(x[4] >> 8)]  ^ T2[(uint8_t)(x[3] >> 16)]  ^ T3[(uint8_t)(x[2] >> 24)]  ^ T4[(uint8_t)(x[1] >> 32)]  ^ T5[(uint8_t)(x[0] >> 40)]  ^ T6[(uint8_t)(x[15] >> 48)] ^ T7[(uint8_t)(x[10] >> 56)];
    y[6]  = T0[(uint8_t)x[6]]  ^ T1[(uint8_t)(x[5] >> 8)]  ^ T2[(uint8_t)(x[4] >> 16)]  ^ T3[(uint8_t)(x[3] >> 24)]  ^ T4[(uint8_t)(x[2] >> 32)]  ^ T5[(uint8_t)(x[1] >> 40)]  ^ T6[(uint8_t)(x[0] >> 48)]  ^ T7[(uint8_t)(x[11] >> 56)];
    y[7]  = T0[(uint8_t)x[7]]  ^ T1[(uint8_t)(x[6] >> 8)]  ^ T2[(uint8_t)(x[5] >> 16)]  ^ T3[(uint8_t)(x[4] >> 24)]  ^ T4[(uint8_t)(x[3] >> 32)]  ^ T5[(uint8_t)(x[2] >> 40)]  ^ T6[(uint8_t)(x[1] >> 48)]  ^ T7[(uint8_t)(x[12] >> 56)];
    y[8]  = T0[(uint8_t)x[8]]  ^ T1[(uint8_t)(x[7] >> 8)]  ^ T2[(uint8_t)(x[6] >> 16)]  ^ T3[(uint8_t)(x[5] >> 24)]  ^ T4[(uint8_t)(x[4] >> 32)]  ^ T5[(uint8_t)(x[3] >> 40)]  ^ T6[(uint8_t)(x[2] >> 48)]  ^ T7[(uint8_t)(x[13] >> 56)];
    y[9]  = T0[(uint8_t)x[9]]  ^ T1[(uint8_t)(x[8] >> 8)]  ^ T2[(uint8_t)(x[7] >> 16)]  ^ T3[(uint8_t)(x[6] >> 24)]  ^ T4[(uint8_t)(x[5] >> 32)]  ^ T5[(uint8_t)(x[4] >> 40)]  ^ T6[(uint8_t)(x[3] >> 48)]  ^ T7[(uint8_t)(x[14] >> 56)];
    y[10] = T0[(uint8_t)x[10]] ^ T1[(uint8_t)(x[9] >> 8)]  ^ T2[(uint8_t)(x[8] >> 16)]  ^ T3[(uint8_t)(x[7] >> 24)]  ^ T4[(uint8_t)(x[6] >> 32)]  ^ T5[(uint8_t)(x[5] >> 40)]  ^ T6[(uint8_t)(x[4] >> 48)]  ^ T7[(uint8_t)(x[15] >> 56)];
    y[11] = T0[(uint8_t)x[11]] ^ T1[(uint8_t)(x[10] >> 8)] ^ T2[(uint8_t)(x[9] >> 16)]  ^ T3[(uint8_t)(x[8] >> 24)]  ^ T4[(uint8_t)(x[7] >> 32)]  ^ T5[(uint8_t)(x[6] >> 40)]  ^ T6[(uint8_t)(x[5] >> 48)]  ^ T7[(uint8_t)(x[0] >> 56)];
    y[12] = T0[(uint8_t)x[12]] ^ T1[(uint8_t)(x[11] >> 8)] ^ T2[(uint8_t)(x[10] >> 16)] ^ T3[(uint8_t)(x[9] >> 24)]  ^ T4[(uint8_t)(x[8] >> 32)]  ^ T5[(uint8_t)(x[7] >> 40)]  ^ T6[(uint8_t)(x[6] >> 48)]  ^ T7[(uint8_t)(x[1] >> 56)];
    y[13] = T0[(uint8_t)x[13]] ^ T1[(uint8_t)(x[12] >> 8)] ^ T2[(uint8_t)(x[11] >> 16)] ^ T3[(uint8_t)(x[10] >> 24)] ^ T4[(uint8_t)(x[9] >> 32)]  ^ T5[(uint8_t)(x[8] >> 40)]  ^ T6[(uint8_t)(x[7] >> 48)]  ^ T7[(uint8_t)(x[2] >> 56)];
    y[14] = T0[(uint8_t)x[14]] ^ T1[(uint8_t)(x[13] >> 8)] ^ T2[(uint8_t)(x[12] >> 16)] ^ T3[(uint8_t)(x[11] >> 24)] ^ T4[(uint8_t)(x[10] >> 32)] ^ T5[(uint8_t)(x[9] >> 40)]  ^ T6[(uint8_t)(x[8] >> 48)]  ^ T7[(uint8_t)(x[3] >> 56)];
    y[15] = T0[(uint8_t)x[15]] ^ T1[(uint8_t)(x[14] >> 8)] ^ T2[(uint8_t)(x[13] >> 16)] ^ T3[(uint8_t)(x[12] >> 24)] ^ T4[(uint8_t)(x[11] >> 32)] ^ T5[(uint8_t)(x[10] >> 40)] ^ T6[(uint8_t)(x[9] >> 48)]  ^ T7[(uint8_t)(x[4] >> 56)];
}

static inline void G1(const uint64_t* x, uint64_t* y, uint64_t round)
{
    y[0]  = T0[(uint8_t)x[0]]  ^ T1[(uint8_t)(x[15] >> 8)] ^ T2[(uint8_t)(x[14] >> 16)] ^ T3[(uint8_t)(x[13] >> 24)] ^ T4[(uint8_t)(x[12] >> 32)] ^ T5[(uint8_t)(x[11] >> 40)] ^ T6[(uint8_t)(x[10] >> 48)] ^ T7[(uint8_t)(x[5] >> 56)]  ^ (0 << 4) ^ round;
    y[1]  = T0[(uint8_t)x[1]]  ^ T1[(uint8_t)(x[0] >> 8)]  ^ T2[(uint8_t)(x[15] >> 16)] ^ T3[(uint8_t)(x[14] >> 24)] ^ T4[(uint8_t)(x[13] >> 32)] ^ T5[(uint8_t)(x[12] >> 40)] ^ T6[(uint8_t)(x[11] >> 48)] ^ T7[(uint8_t)(x[6] >> 56)]  ^ (1 << 4) ^ round;
    y[2]  = T0[(uint8_t)x[2]]  ^ T1[(uint8_t)(x[1] >> 8)]  ^ T2[(uint8_t)(x[0] >> 16)]  ^ T3[(uint8_t)(x[15] >> 24)] ^ T4[(uint8_t)(x[14] >> 32)] ^ T5[(uint8_t)(x[13] >> 40)] ^ T6[(uint8_t)(x[12] >> 48)] ^ T7[(uint8_t)(x[7] >> 56)]  ^ (2 << 4) ^ round;
    y[3]  = T0[(uint8_t)x[3]]  ^ T1[(uint8_t)(x[2] >> 8)]  ^ T2[(uint8_t)(x[1] >> 16)]  ^ T3[(uint8_t)(x[0] >> 24)]  ^ T4[(uint8_t)(x[15] >> 32)] ^ T5[(uint8_t)(x[14] >> 40)] ^ T6[(uint8_t)(x[13] >> 48)] ^ T7[(uint8_t)(x[8] >> 56)]  ^ (3 << 4) ^ round;
    y[4]  = T0[(uint8_t)x[4]]  ^ T1[(uint8_t)(x[3] >> 8)]  ^ T2[(uint8_t)(x[2] >> 16)]  ^ T3[(uint8_t)(x[1] >> 24)]  ^ T4[(uint8_t)(x[0] >> 32)]  ^ T5[(uint8_t)(x[15] >> 40)] ^ T6[(uint8_t)(x[14] >> 48)] ^ T7[(uint8_t)(x[9] >> 56)]  ^ (4 << 4) ^ round;
    y[5]  = T0[(uint8_t)x[5]]  ^ T1[(uint8_t)(x[4] >> 8)]  ^ T2[(uint8_t)(x[3] >> 16)]  ^ T3[(uint8_t)(x[2] >> 24)]  ^ T4[(uint8_t)(x[1] >> 32)]  ^ T5[(uint8_t)(x[0] >> 40)]  ^ T6[(uint8_t)(x[15] >> 48)] ^ T7[(uint8_t)(x[10] >> 56)] ^ (5 << 4) ^ round;
    y[6]  = T0[(uint8_t)x[6]]  ^ T1[(uint8_t)(x[5] >> 8)]  ^ T2[(uint8_t)(x[4] >> 16)]  ^ T3[(uint8_t)(x[3] >> 24)]  ^ T4[(uint8_t)(x[2] >> 32)]  ^ T5[(uint8_t)(x[1] >> 40)]  ^ T6[(uint8_t)(x[0] >> 48)]  ^ T7[(uint8_t)(x[11] >> 56)] ^ (6 << 4) ^ round;
    y[7]  = T0[(uint8_t)x[7]]  ^ T1[(uint8_t)(x[6] >> 8)]  ^ T2[(uint8_t)(x[5] >> 16)]  ^ T3[(uint8_t)(x[4] >> 24)]  ^ T4[(uint8_t)(x[3] >> 32)]  ^ T5[(uint8_t)(x[2] >> 40)]  ^ T6[(uint8_t)(x[1] >> 48)]  ^ T7[(uint8_t)(x[12] >> 56)] ^ (7 << 4) ^ round;
    y[8]  = T0[(uint8_t)x[8]]  ^ T1[(uint8_t)(x[7] >> 8)]  ^ T2[(uint8_t)(x[6] >> 16)]  ^ T3[(uint8_t)(x[5] >> 24)]  ^ T4[(uint8_t)(x[4] >> 32)]  ^ T5[(uint8_t)(x[3] >> 40)]  ^ T6[(uint8_t)(x[2] >> 48)]  ^ T7[(uint8_t)(x[13] >> 56)] ^ (8 << 4) ^ round;
    y[9]  = T0[(uint8_t)x[9]]  ^ T1[(uint8_t)(x[8] >> 8)]  ^ T2[(uint8_t)(x[7] >> 16)]  ^ T3[(uint8_t)(x[6] >> 24)]  ^ T4[(uint8_t)(x[5] >> 32)]  ^ T5[(uint8_t)(x[4] >> 40)]  ^ T6[(uint8_t)(x[3] >> 48)]  ^ T7[(uint8_t)(x[14] >> 56)] ^ (9 << 4) ^ round;
    y[10] = T0[(uint8_t)x[10]] ^ T1[(uint8_t)(x[9] >> 8)]  ^ T2[(uint8_t)(x[8] >> 16)]  ^ T3[(uint8_t)(x[7] >> 24)]  ^ T4[(uint8_t)(x[6] >> 32)]  ^ T5[(uint8_t)(x[5] >> 40)]  ^ T6[(uint8_t)(x[4] >> 48)]  ^ T7[(uint8_t)(x[15] >> 56)] ^ (10 << 4) ^ round;
    y[11] = T0[(uint8_t)x[11]] ^ T1[(uint8_t)(x[10] >> 8)] ^ T2[(uint8_t)(x[9] >> 16)]  ^ T3[(uint8_t)(x[8] >> 24)]  ^ T4[(uint8_t)(x[7] >> 32)]  ^ T5[(uint8_t)(x[6] >> 40)]  ^ T6[(uint8_t)(x[5] >> 48)]  ^ T7[(uint8_t)(x[0] >> 56)]  ^ (11 << 4) ^ round;
    y[12] = T0[(uint8_t)x[12]] ^ T1[(uint8_t)(x[11] >> 8)] ^ T2[(uint8_t)(x[10] >> 16)] ^ T3[(uint8_t)(x[9] >> 24)]  ^ T4[(uint8_t)(x[8] >> 32)]  ^ T5[(uint8_t)(x[7] >> 40)]  ^ T6[(uint8_t)(x[6] >> 48)]  ^ T7[(uint8_t)(x[1] >> 56)]  ^ (12 << 4) ^ round;
    y[13] = T0[(uint8_t)x[13]] ^ T1[(uint8_t)(x[12] >> 8)] ^ T2[(uint8_t)(x[11] >> 16)] ^ T3[(uint8_t)(x[10] >> 24)] ^ T4[(uint8_t)(x[9] >> 32)]  ^ T5[(uint8_t)(x[8] >> 40)]  ^ T6[(uint8_t)(x[7] >> 48)]  ^ T7[(uint8_t)(x[2] >> 56)]  ^ (13 << 4) ^ round;
    y[14] = T0[(uint8_t)x[14]] ^ T1[(uint8_t)(x[13] >> 8)] ^ T2[(uint8_t)(x[12] >> 16)] ^ T3[(uint8_t)(x[11] >> 24)] ^ T4[(uint8_t)(x[10] >> 32)] ^ T5[(uint8_t)(x[9] >> 40)]  ^ T6[(uint8_t)(x[8] >> 48)]  ^ T7[(uint8_t)(x[3] >> 56)]  ^ (14 << 4) ^ round;
    y[15] = T0[(uint8_t)x[15]] ^ T1[(uint8_t)(x[14] >> 8)] ^ T2[(uint8_t)(x[13] >> 16)] ^ T3[(uint8_t)(x[12] >> 24)] ^ T4[(uint8_t)(x[11] >> 32)] ^ T5[(uint8_t)(x[10] >> 40)] ^ T6[(uint8_t)(x[9] >> 48)]  ^ T7[(uint8_t)(x[4] >> 56)]  ^ (15 << 4) ^ round;
}

static inline void G2(const uint64_t* x, uint64_t* y, uint64_t round)
{
    y[0]  = (T0[(uint8_t)x[0]]  ^ T1[(uint8_t)(x[15] >> 8)] ^ T2[(uint8_t)(x[14] >> 16)] ^ T3[(uint8_t)(x[13] >> 24)] ^ T4[(uint8_t)(x[12] >> 32)] ^ T5[(uint8_t)(x[11] >> 40)] ^ T6[(uint8_t)(x[10] >> 48)] ^ T7[(uint8_t)(x[5] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 0)  * 0x10) ^ round)) << 56));
    y[1]  = (T0[(uint8_t)x[1]]  ^ T1[(uint8_t)(x[0] >> 8)]  ^ T2[(uint8_t)(x[15] >> 16)] ^ T3[(uint8_t)(x[14] >> 24)] ^ T4[(uint8_t)(x[13] >> 32)] ^ T5[(uint8_t)(x[12] >> 40)] ^ T6[(uint8_t)(x[11] >> 48)] ^ T7[(uint8_t)(x[6] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 1)  * 0x10) ^ round)) << 56));
    y[2]  = (T0[(uint8_t)x[2]]  ^ T1[(uint8_t)(x[1] >> 8)]  ^ T2[(uint8_t)(x[0] >> 16)]  ^ T3[(uint8_t)(x[15] >> 24)] ^ T4[(uint8_t)(x[14] >> 32)] ^ T5[(uint8_t)(x[13] >> 40)] ^ T6[(uint8_t)(x[12] >> 48)] ^ T7[(uint8_t)(x[7] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 2)  * 0x10) ^ round)) << 56));
    y[3]  = (T0[(uint8_t)x[3]]  ^ T1[(uint8_t)(x[2] >> 8)]  ^ T2[(uint8_t)(x[1] >> 16)]  ^ T3[(uint8_t)(x[0] >> 24)]  ^ T4[(uint8_t)(x[15] >> 32)] ^ T5[(uint8_t)(x[14] >> 40)] ^ T6[(uint8_t)(x[13] >> 48)] ^ T7[(uint8_t)(x[8] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 3)  * 0x10) ^ round)) << 56));
    y[4]  = (T0[(uint8_t)x[4]]  ^ T1[(uint8_t)(x[3] >> 8)]  ^ T2[(uint8_t)(x[2] >> 16)]  ^ T3[(uint8_t)(x[1] >> 24)]  ^ T4[(uint8_t)(x[0] >> 32)]  ^ T5[(uint8_t)(x[15] >> 40)] ^ T6[(uint8_t)(x[14] >> 48)] ^ T7[(uint8_t)(x[9] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 4)  * 0x10) ^ round)) << 56));
    y[5]  = (T0[(uint8_t)x[5]]  ^ T1[(uint8_t)(x[4] >> 8)]  ^ T2[(uint8_t)(x[3] >> 16)]  ^ T3[(uint8_t)(x[2] >> 24)]  ^ T4[(uint8_t)(x[1] >> 32)]  ^ T5[(uint8_t)(x[0] >> 40)]  ^ T6[(uint8_t)(x[15] >> 48)] ^ T7[(uint8_t)(x[10] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 5)  * 0x10) ^ round)) << 56));
    y[6]  = (T0[(uint8_t)x[6]]  ^ T1[(uint8_t)(x[5] >> 8)]  ^ T2[(uint8_t)(x[4] >> 16)]  ^ T3[(uint8_t)(x[3] >> 24)]  ^ T4[(uint8_t)(x[2] >> 32)]  ^ T5[(uint8_t)(x[1] >> 40)]  ^ T6[(uint8_t)(x[0] >> 48)]  ^ T7[(uint8_t)(x[11] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 6)  * 0x10) ^ round)) << 56));
    y[7]  = (T0[(uint8_t)x[7]]  ^ T1[(uint8_t)(x[6] >> 8)]  ^ T2[(uint8_t)(x[5] >> 16)]  ^ T3[(uint8_t)(x[4] >> 24)]  ^ T4[(uint8_t)(x[3] >> 32)]  ^ T5[(uint8_t)(x[2] >> 40)]  ^ T6[(uint8_t)(x[1] >> 48)]  ^ T7[(uint8_t)(x[12] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 7)  * 0x10) ^ round)) << 56));
    y[8]  = (T0[(uint8_t)x[8]]  ^ T1[(uint8_t)(x[7] >> 8)]  ^ T2[(uint8_t)(x[6] >> 16)]  ^ T3[(uint8_t)(x[5] >> 24)]  ^ T4[(uint8_t)(x[4] >> 32)]  ^ T5[(uint8_t)(x[3] >> 40)]  ^ T6[(uint8_t)(x[2] >> 48)]  ^ T7[(uint8_t)(x[13] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 8)  * 0x10) ^ round)) << 56));
    y[9]  = (T0[(uint8_t)x[9]]  ^ T1[(uint8_t)(x[8] >> 8)]  ^ T2[(uint8_t)(x[7] >> 16)]  ^ T3[(uint8_t)(x[6] >> 24)]  ^ T4[(uint8_t)(x[5] >> 32)]  ^ T5[(uint8_t)(x[4] >> 40)]  ^ T6[(uint8_t)(x[3] >> 48)]  ^ T7[(uint8_t)(x[14] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 9)  * 0x10) ^ round)) << 56));
    y[10] = (T0[(uint8_t)x[10]] ^ T1[(uint8_t)(x[9] >> 8)]  ^ T2[(uint8_t)(x[8] >> 16)]  ^ T3[(uint8_t)(x[7] >> 24)]  ^ T4[(uint8_t)(x[6] >> 32)]  ^ T5[(uint8_t)(x[5] >> 40)]  ^ T6[(uint8_t)(x[4] >> 48)]  ^ T7[(uint8_t)(x[15] >> 56)]) + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 10) * 0x10) ^ round)) << 56));
    y[11] = (T0[(uint8_t)x[11]] ^ T1[(uint8_t)(x[10] >> 8)] ^ T2[(uint8_t)(x[9] >> 16)]  ^ T3[(uint8_t)(x[8] >> 24)]  ^ T4[(uint8_t)(x[7] >> 32)]  ^ T5[(uint8_t)(x[6] >> 40)]  ^ T6[(uint8_t)(x[5] >> 48)]  ^ T7[(uint8_t)(x[0] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 11) * 0x10) ^ round)) << 56));
    y[12] = (T0[(uint8_t)x[12]] ^ T1[(uint8_t)(x[11] >> 8)] ^ T2[(uint8_t)(x[10] >> 16)] ^ T3[(uint8_t)(x[9] >> 24)]  ^ T4[(uint8_t)(x[8] >> 32)]  ^ T5[(uint8_t)(x[7] >> 40)]  ^ T6[(uint8_t)(x[6] >> 48)]  ^ T7[(uint8_t)(x[1] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 12) * 0x10) ^ round)) << 56));
    y[13] = (T0[(uint8_t)x[13]] ^ T1[(uint8_t)(x[12] >> 8)] ^ T2[(uint8_t)(x[11] >> 16)] ^ T3[(uint8_t)(x[10] >> 24)] ^ T4[(uint8_t)(x[9] >> 32)]  ^ T5[(uint8_t)(x[8] >> 40)]  ^ T6[(uint8_t)(x[7] >> 48)]  ^ T7[(uint8_t)(x[2] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 13) * 0x10) ^ round)) << 56));
    y[14] = (T0[(uint8_t)x[14]] ^ T1[(uint8_t)(x[13] >> 8)] ^ T2[(uint8_t)(x[12] >> 16)] ^ T3[(uint8_t)(x[11] >> 24)] ^ T4[(uint8_t)(x[10] >> 32)] ^ T5[(uint8_t)(x[9] >> 40)]  ^ T6[(uint8_t)(x[8] >> 48)]  ^ T7[(uint8_t)(x[3] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 14) * 0x10) ^ round)) << 56));
    y[15] = (T0[(uint8_t)x[15]] ^ T1[(uint8_t)(x[14] >> 8)] ^ T2[(uint8_t)(x[13] >> 16)] ^ T3[(uint8_t)(x[12] >> 24)] ^ T4[(uint8_t)(x[11] >> 32)] ^ T5[(uint8_t)(x[10] >> 40)] ^ T6[(uint8_t)(x[9] >> 48)]  ^ T7[(uint8_t)(x[4] >> 56)])  + (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - 15) * 0x10) ^ round)) << 56));
}

static inline void P(uint64_t* x, uint64_t* y, uint64_t round)
{
    for (uint_fast32_t idx=0; idx<16; ++idx) {
        x[idx] ^= (idx << 4) ^ round;
    }

    G1(x, y, round + 1);
    G(y, x);
}

static inline void Q(uint64_t* x, uint64_t* y, uint64_t round)
{
    for (uint_fast32_t j = 0; j < 16; ++j) {
        x[j] += (0x00F0F0F0F0F0F0F3ull ^ (((uint64_t)(((15 - j) * 0x10) ^ round)) << 56));
    }

    G2(x, y, round + 1);
    G(y, x);
}

static void outputTransform(struct kupyna512_ctx_t* ctx)
{
    union uint1024_t t1;
    union uint1024_t t2;

    memcpy(t1.q, ctx->h.q, sizeof(t1));

    for (uint8_t r = 0; r < 14; r += 2) {
        P(t1.q, t2.q, r);
    }

#if defined(__SSE2__)
    for (uint_fast32_t column = 0; column < 8; column+=2) {
        ctx->h.h[column]   = _mm_xor_si128(ctx->h.h[column],   t1.h[column]);
        ctx->h.h[column+1] = _mm_xor_si128(ctx->h.h[column+1], t1.h[column+1]);
    }
#elif defined(__SSE__)
    for (uint_fast32_t column = 0; column < 8; ++column) {
        ctx->h.h[column] = _mm_xor_ps(ctx->h.h[column], t1.h[column]);
    }
#else
    for (uint_fast32_t column = 0; column < 16; ++column) {
        ctx->h.q[column] ^= t1.q[column];
    }
#endif
}

static void transform(struct kupyna512_ctx_t* ctx, const union uint1024_t* b)
{
    union uint1024_t AQ1;
    union uint1024_t AP1;
    union uint1024_t tmp;

#if defined(__SSE2__)
    for (uint_fast32_t column = 0; column < 8; column += 4) {
        __m128i m1 = _mm_load_si128(b->h + column);
        __m128i m2 = _mm_load_si128(b->h + column + 1);
        __m128i m3 = _mm_load_si128(b->h + column + 2);
        __m128i m4 = _mm_load_si128(b->h + column + 3);
        AP1.h[column]   = _mm_xor_si128(ctx->h.h[column],   m1);
        AP1.h[column+1] = _mm_xor_si128(ctx->h.h[column+1], m2);
        AP1.h[column+2] = _mm_xor_si128(ctx->h.h[column+2], m3);
        AP1.h[column+3] = _mm_xor_si128(ctx->h.h[column+3], m4);
        _mm_store_si128(AQ1.h + column,     m1);
        _mm_store_si128(AQ1.h + column + 1, m2);
        _mm_store_si128(AQ1.h + column + 2, m3);
        _mm_store_si128(AQ1.h + column + 3, m4);
    }
#elif defined(__SSE__)
    for (uint_fast32_t column = 0; column < 8; column += 4) {
        __m128 m1 = _mm_load_ps((float*)(b->h + column));
        __m128 m2 = _mm_load_ps((float*)(b->h + column + 1));
        __m128 m3 = _mm_load_ps((float*)(b->h + column + 2));
        __m128 m4 = _mm_load_ps((float*)(b->h + column + 3));
        AP1.h[column]   = _mm_xor_ps(ctx->h.h[column],   m1);
        AP1.h[column+1] = _mm_xor_ps(ctx->h.h[column+1], m2);
        AP1.h[column+2] = _mm_xor_ps(ctx->h.h[column+2], m3);
        AP1.h[column+3] = _mm_xor_ps(ctx->h.h[column+3], m4);
        _mm_store_ps((float*)(AQ1.h + column),     m1);
        _mm_store_ps((float*)(AQ1.h + column + 1), m2);
        _mm_store_ps((float*)(AQ1.h + column + 2), m3);
        _mm_store_ps((float*)(AQ1.h + column + 3), m4);
    }
#else
    for (uint_fast32_t column = 0; column < 16; ++column) {
        AP1.q[column] = ctx->h.q[column] ^ b->q[column];
        AQ1.q[column] = b->q[column];
    }
#endif

    for (uint8_t r = 0; r < 14; r += 2) {
        P(AP1.q, tmp.q, r);
        Q(AQ1.q, tmp.q, r);
    }

#if defined(__SSE2__)
    for (uint_fast32_t column = 0; column < 8; column += 4) {
        ctx->h.h[column]   = _mm_xor_si128(ctx->h.h[column],   _mm_xor_si128(AQ1.h[column],   AP1.h[column]));
        ctx->h.h[column+1] = _mm_xor_si128(ctx->h.h[column+1], _mm_xor_si128(AQ1.h[column+1], AP1.h[column+1]));
        ctx->h.h[column+2] = _mm_xor_si128(ctx->h.h[column+2], _mm_xor_si128(AQ1.h[column+2], AP1.h[column+2]));
        ctx->h.h[column+3] = _mm_xor_si128(ctx->h.h[column+3], _mm_xor_si128(AQ1.h[column+3], AP1.h[column+3]));
    }
#elif defined(__SSE__)
    for (uint_fast32_t column = 0; column < 8; column += 4) {
        ctx->h.h[column]   = _mm_xor_ps(ctx->h.h[column],   _mm_xor_ps(AQ1.h[column],   AP1.h[column]));
        ctx->h.h[column+1] = _mm_xor_ps(ctx->h.h[column+1], _mm_xor_ps(AQ1.h[column+1], AP1.h[column+1]));
        ctx->h.h[column+2] = _mm_xor_ps(ctx->h.h[column+2], _mm_xor_ps(AQ1.h[column+2], AP1.h[column+2]));
        ctx->h.h[column+3] = _mm_xor_ps(ctx->h.h[column+3], _mm_xor_ps(AQ1.h[column+3], AP1.h[column+3]));
    }
#else
    for (uint_fast32_t column = 0; column < 16; ++column) {
        ctx->h.q[column] ^= AP1.q[column] ^ AQ1.q[column];
    }
#endif
}

void kupyna512_init(struct kupyna512_ctx_t* ctx)
{
    ctx->pos    = 0;
    ctx->total  = 0;
    memset(ctx->h.q, 0, sizeof(ctx->h.q));
    ctx->h.b[0] = 128;
}

void kupyna512_update(struct kupyna512_ctx_t* ctx, const uint8_t* data, size_t len)
{
    while (ctx->pos + len >= 128) {
        memcpy(ctx->m.b + ctx->pos, data, 128 - ctx->pos);
        transform(ctx, &ctx->m);
        len        -= 128 - ctx->pos;
        ctx->total += (128 - ctx->pos) * 8;
        data       += 128 - ctx->pos;
        ctx->pos    = 0;
    }

    memcpy(ctx->m.b + ctx->pos, data, len);
    ctx->pos   += len;
    ctx->total += len * 8;
}

void kupyna512_update_aligned(struct kupyna512_ctx_t* ctx, const uint8_t* data, size_t len)
{
    assert(((size_t)data & 0x0F) == 0);

    if (ctx->pos && ctx->pos + len >= 128) {
        memcpy(ctx->m.b + ctx->pos, data, 128 - ctx->pos);
        transform(ctx, &ctx->m);
        len        -= 128 - ctx->pos;
        ctx->total += (128 - ctx->pos) * 8;
        data       += 128 - ctx->pos;
        ctx->pos    = 0;
    }

    while (len >= 128) {
        transform(ctx, (union uint1024_t*)data);
        len        -= 128;
        ctx->total += 128  * 8;
        data       += 128;
    }

    memcpy(ctx->m.b + ctx->pos, data, len);
    ctx->pos   += len;
    ctx->total += len * 8;
}

void kupyna512_final(struct kupyna512_ctx_t* ctx, uint8_t* hash)
{
    ctx->m.b[ctx->pos] = 0x80;
    ++ctx->pos;
    if (ctx->pos > 116) {
        memset(ctx->m.b + ctx->pos, 0, 128 - ctx->pos);
        transform(ctx, &ctx->m);
        ctx->pos = 0;
    }

    memset(ctx->m.b + ctx->pos, 0,           128 - ctx->pos);
    memcpy(ctx->m.b + 116,      &ctx->total, sizeof(uint64_t));

    transform(ctx, &ctx->m);
    outputTransform(ctx);

    memcpy(hash, ctx->h.b + 128 - 512/8, 512/8);
}

void kupyna512_final2(struct kupyna512_ctx_t* ctx, uint8_t* hash, size_t bits)
{
    if (bits > 512) {
        bits = 512;
    }

    ctx->m.b[ctx->pos] = 0x80;
    ++ctx->pos;
    if (ctx->pos > 116) {
        memset(ctx->m.b + ctx->pos, 0, 128 - ctx->pos);
        transform(ctx, &ctx->m);
        ctx->pos = 0;
    }

    memset(ctx->m.b + ctx->pos, 0,           128 - ctx->pos);
    memcpy(ctx->m.b + 116,      &ctx->total, sizeof(uint64_t));

    transform(ctx, &ctx->m);
    outputTransform(ctx);

    memcpy(hash, ctx->h.b + 128 - bits/8, bits/8);
}
