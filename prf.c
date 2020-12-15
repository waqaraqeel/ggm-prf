#include <sys/random.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bit_array.h"

#define ARG_LEN 32

typedef BIT_ARRAY* ggm;

size_t k;

ggm prf(ggm sk, ggm x) {
    // if x is 0 or 1 (base case)
    if (bit_array_cmp_uint64(x, 0) == 0) {
        ggm ans = bit_array_create(k/2);
        bit_array_copy(ans, 0, sk, 0, k/2);
        return ans;
    }
    if (bit_array_cmp_uint64(x, 1) == 0) {
        ggm ans = bit_array_create(k/2);
        bit_array_copy(ans, 0, sk, k/2, k/2);
        return ans;
    }
    return sk;
}

int main(int argc, char** argv) {
    // get key size
    if (argc < 2) {
        fprintf(stderr, "Expected argument key size k\n");
        exit(2);
    }
    k = strtol(argv[1], NULL, 10);

    ggm buf = bit_array_create(k);
    // get randomness
    size_t filled = getrandom(buf->words, k, 0);
    if (filled < k) {
        fprintf(stderr, "Could not read enough randomness\n");
        exit(3);
    }
    // print our array
    bit_array_print(buf, stdout);
    printf("\n");

    // read args from stdin
    while(1) {
        char* arg = (char*) malloc(ARG_LEN);
        int read = scanf("%s", arg);
        if (strcmp(arg, "-1") == 0 || read < 1)
            break;

        ggm x = bit_array_create(k);
        bit_array_from_decimal(x, arg);

        ggm ans = prf(buf, x);
        bit_array_print(ans, stdout);
        printf("\n");

        free(arg);
        bit_array_free(x);
        bit_array_free(ans);
    }

    bit_array_free(buf);
    return 0;
}