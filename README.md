# binary-left-shift-modular-inverse
Binary left-shift modular inverse implementation in c language

https://www.researchgate.net/publication/304417579_Modular_Inverse_Algorithms_Without_Multiplications_for_Cryptographic_Applications
Algorithm 3: Left-shift binary algorithm

# compile
clang main.c

# caution
if test result in browser console, use bigint

for example
```
2148583669n *  197344934n % 2521008887 == 1n
```
because integer mutiply may overflow
