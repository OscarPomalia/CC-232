/*
 * FastSqrt.h
 * Adaptado pedagogicamente para CC232 a partir del codigo de Morin.
 */

#ifndef FASTSQRT_H_
#define FASTSQRT_H_

#include <cassert>

namespace ods {

static int *sqrtab;
static int *logtab;

class FastSqrt {
protected:
    static const int halfint = 1 << 16;
    static const int r = 29;

    static void inittabs(int) {
        sqrtab = new int[halfint];
        logtab = new int[halfint];
        logtab[0] = 0;
        for (int d = 0; d < 16; d++) {
            for (int k = 0; k < (1 << d); k++) {
                logtab[(1 << d) + k] = d;
            }
        }
        int s = 1 << 7;  // sqrt(2^14)
        for (int i = 0; i < halfint; i++) {
            if ((s + 1) * (s + 1) <= (i << 14)) s++;
            sqrtab[i] = s;
        }
    }
public:
    static void init() { inittabs(0); }

    static int log(int x) {
        assert(x > 0);
        if (x >= halfint) {
            return 16 + logtab[x >> 16];
        }
        return logtab[x];
    }

    static int sqrt(int x) {
        assert(x >= 0);
        if (x <= 1) return x;
        int rp = log(x);
        int upgrade = ((r - rp) / 2) * 2;
        int xp = x << upgrade;  // xp tiene r o r-1 bits
        int s = sqrtab[xp >> (r / 2)] >> (upgrade / 2);
        while ((s + 1) * (s + 1) <= x) s++;
        while (s * s > x) s--;
        return s;
    }
};

} /* namespace ods */

#endif /* FASTSQRT_H_ */
