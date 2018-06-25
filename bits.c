#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool bit_set(char bits, char place)
{
    char mask = 1 << place;
    return bits & mask;
}

char bit_flip(char bits, char place)
{
    char mask = 1 << place;
    return bits ^ mask;
}

int main(int argc, char **argv)
{
    assert(bit_set(0b01100000, 0) == false);
    assert(bit_set(0b01100000, 1) == false);
    assert(bit_set(0b01100000, 2) == false);
    assert(bit_set(0b01100000, 3) == false);
    assert(bit_set(0b01100000, 4) == false);
    assert(bit_set(0b01100000, 5) == true);
    assert(bit_set(0b01100000, 6) == true);
    assert(bit_set(0b01100000, 7) == false);

    assert(bit_flip(0b00000000, 0) == 0b00000001);
    assert(bit_flip(0b00000000, 3) == 0b00001000);
    assert(bit_flip(0b01111111, 3) == 0b01110111);
    assert(bit_flip(0b01110110, 0) == 0b01110111);

    return 0;
}
