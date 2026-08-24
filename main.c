#include <stdio.h>
#include "invert.h"
#include "ppm.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./ppm_invert input.ppm output.ppm\n");
        return 1;
    }

    Image *image = read_ppm(argv[1]);

    if (image == NULL)
    {
        return 1;
    }

    invert_image(image);

    if (write_ppm(argv[2], image) == 0)
    {
        free_image(image);
        return 1;
    }

    free_image(image);

    return 0;
}