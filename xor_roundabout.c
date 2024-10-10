/*
* Implements XOR encryption through ASM instructions
* other than the normal "xor a, b" instruction.
* useful in AV/EDR evasion for malware.
*/

// implementing for large inputs or kys is left as an
// exercise to the reader
// (hint: just use a loop for the key)

#include <stdio.h>

unsigned char xor_roundabout(unsigned char value, unsigned char key) {
    unsigned char result;
    asm volatile (
        "mov %1, %%al;"      // value -> AL
        "mov %2, %%bl;"      // key -> BL
        "add %%al, %%bl;"    // AL = AL + BL (intermediate value)
        "sub %%al, %%bl;"    // AL = AL - BL (undo part of the addition)
        "sub %%al, %%bl;"    // AL = AL - BL (achieve the XOR effect)

        "mov %%al, %0;"      // result -> 'result'
        : "=r" (result)      // output: 'result'
        : "r" (value), "r" (key)   // inputs: 'value', 'key'
        : "%al", "%bl"       // clobbered registers: AL and BL
    );
    return result;
}

int main(void) {
    unsigned char value = 0xA5;
    unsigned char key = 0x5F;
    unsigned char result = xor_roundabout(value, key);
    printf("Result of XORing 0x%X with 0x%X is 0x%X\n", value, key, result); // result should be 0xA5.
    return 0;
}
