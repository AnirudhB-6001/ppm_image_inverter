#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>

Image *read_ppm(const char *filename)
{
    FILE *input = fopen(filename, "rb");

    if (input == NULL)
    {
        printf("Could not open input file\n");
        return NULL;
    }

    Image *image = malloc(sizeof(Image));

    if (image == NULL)
    {
        fclose(input);
        return NULL;
    }

    image->width = 0;
    image->height = 0;
    image->max_value = 0;
    image->pixels = NULL;

    int first_character = fgetc(input);
    int second_character = fgetc(input);
    int third_character = fgetc(input);

    if (first_character != 'P' ||
    second_character != '6' ||
    third_character != '\n')
    {
        printf("Invalid PPM header\n");
        goto cleanup;
    }

    char dimensions_line[64];

    if (fgets(dimensions_line, sizeof dimensions_line, input) == NULL)
    {
        printf("Could not read dimensions\n");
        goto cleanup;
    }

    if (sscanf(dimensions_line, "%d %d", &image->width, &image->height) != 2)
    {
        printf("Invalid dimensions\n");
        goto cleanup;
    }

    if (image->width <= 0 || image->height <= 0)
    {
        printf("Invalid dimensions\n");
        goto cleanup;
    }

    char max_value_line[64];

    if (fgets(max_value_line, sizeof max_value_line, input) == NULL)
    {
        printf("Could not read max value\n");
        goto cleanup;
    }

    if (sscanf(max_value_line, "%d", &image->max_value) != 1)
    {
        printf("Invalid max value\n");
        goto cleanup;
    }

    if (image->max_value != 255)
    {
        printf("Unsupported max value\n");
        goto cleanup;
    }

    size_t pixel_count = image->width * image->height * 3;

    image->pixels = malloc(pixel_count);

    if (image->pixels == NULL)
    {
        printf("Could not allocate pixel memory\n");
        goto cleanup;
    }

    size_t bytes_read = fread(image->pixels, 1, pixel_count, input);

    if (bytes_read != pixel_count)
    {
        printf("Incomplete raster data\n");
        goto cleanup;
    }

    fclose(input);

    return image;

    cleanup:
        fclose(input);
        free(image->pixels);
        free(image);
        return NULL;
}

int write_ppm(const char *filename, Image *image)
{
    FILE *output = fopen(filename, "wb");

    if (output == NULL)
    {
        printf("Could not create output file\n");
        return 0;
    }

    fprintf(output, "P6\n%d %d\n%d\n",
            image->width,
            image->height,
            image->max_value);

    size_t pixel_count = image->width * image->height * 3;

    size_t bytes_written = fwrite(image->pixels, 1, pixel_count, output);

    fclose(output);

    if (bytes_written != pixel_count)
    {
        return 0;
    }

    return 1;
}

void free_image(Image *image)
{
    if (image == NULL)
    {
        return;
    }

    free(image->pixels);
    free(image);
}