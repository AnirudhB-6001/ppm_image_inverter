#include "invert.h"
#include <stddef.h>

int invert_value(int original)
{
    return 255 - original;
}

void invert_image(Image *image)
{
    size_t pixel_count = image->width * image->height * 3;

    for (size_t i = 0; i < pixel_count; i++)
    {
        image->pixels[i] = invert_value(image->pixels[i]);
    }
}