


This is a simple and quick implementation of the Goldreich-Goldwasser-Micali
construction of pseudorandom functions
[[GGM'84](https://dl.acm.org/doi/pdf/10.1145/3335741.3335752)].

This construction requires a length-doubling pseudorandom generator (PRG). Such
PRGs can be constructed from one-way functions (OWF). This implementation uses
the [Blake3](https://github.com/BLAKE3-team/BLAKE3) hash function as an OWF.

## Dependencies
This implementation depends on [this](https://github.com/noporpoise/BitArray)
bit array library, and the [Blake3](https://github.com/BLAKE3-team/BLAKE3) hash
function implementation. Both are bundled. You don't anything besides the
standard C build tools.

## Build
To build, just run:
```
make
```

Then, run `./prf` and enter the decimal value of input to get output of PRF.
Enter a non-numeric input to exit.