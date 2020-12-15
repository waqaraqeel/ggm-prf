SRC=blake3.c blake3_dispatch.c blake3_portable.c
ASM=blake3_sse2_x86-64_unix.S blake3_sse41_x86-64_unix.S blake3_avx2_x86-64_unix.S blake3_avx512_x86-64_unix.S

all: libblake3.so

libblake3.so: $(SRC) $(ASM)
	gcc -shared -O3 -o $@ $^