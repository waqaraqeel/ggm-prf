#include <sys/random.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bit_array.h"
#include "blake3/blake3.h"

#define BLOCK 8

blake3_hasher hasher;

typedef BIT_ARRAY* ba;


void* prg(void* in) {
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, (uint8_t*) in, BLOCK/8);
    void *out =  malloc(BLOCK*2);
    blake3_hasher_finalize(&hasher, (uint8_t*) out, BLOCK/8*2);
    return out;
}

void prf(ba sk, ba x, ba ans) {
    if (x->num_of_bits == 1) {
        ans->words =  (uint64_t*) (prg((void*) sk->words) + (bit_array_get_bit(x, 0) ? BLOCK/8 : 0));
    } else {
        ba xp = bit_array_create(x->num_of_bits - 1);
        bit_array_copy(xp, 0, x, 0, x->num_of_bits - 1);
        ba prfp = bit_array_create(BLOCK);
        prf(sk, xp, prfp);
        ans->words = (uint64_t*) (prg((void*) prfp->words) + (bit_array_get_bit(x, x->num_of_bits-1) ? BLOCK/8 : 0));
        bit_array_free(xp);
    }
}

int main() {
    ba buf = bit_array_create(BLOCK);
    size_t filled = getrandom(buf->words, BLOCK, 0);
    if (filled < BLOCK) {
        fprintf(stderr, "Could not read random\n");
        exit(1);
    }
    bit_array_print(buf, stdout); printf("\n");

    uint64_t arg;
    while(1) {
        size_t read = scanf("%ld", &arg);
        if (read < 1)
            break;
        ba x = bit_array_create(BLOCK);
        x->words = &arg;

        ba ans = bit_array_create(BLOCK);
        prf(buf, x, ans);
        bit_array_print(x, stdout); printf(" -> ");
        bit_array_print(ans, stdout); printf("\n");
    }
    bit_array_free(buf);
    return 0;
}