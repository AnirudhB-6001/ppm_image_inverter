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

    int original = 20;
    int inverted = invert_value(original);

    printf("%d\n", inverted);

    return 0;
}