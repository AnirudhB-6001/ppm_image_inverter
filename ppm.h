#ifndef PPM_H
#define PPM_H

typedef struct
{
    int width;
    int height;
    int max_value;
    unsigned char *pixels;
} Image;

Image *read_ppm(const char *filename);
int write_ppm(const char *filename, Image *image);
void free_image(Image *image);

#endif