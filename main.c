#include <assert.h>
#include <stdio.h>

int invert_value(int original)
{
    return 255 - original;
}

int main(void)
{
    assert(invert_value(0) == 255);
    assert(invert_value(255) == 0);
    assert(invert_value(20) == 235);
    assert(invert_value(invert_value(20)) == 20);

    unsigned char pixels[6] = {0, 0, 0, 255, 0, 0};
    for (int i = 0; i < 6; i++)
    {
        pixels[i] = invert_value(pixels[i]);
    }

    assert(pixels[0] == 255);
    assert(pixels[1] == 255);
    assert(pixels[2] == 255);
    assert(pixels[3] == 0);
    assert(pixels[4] == 255);
    assert(pixels[5] == 255);

    return 0;
}
