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

    FILE *input = fopen("sample.ppm", "r");

    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    int first_character = fgetc(input);
    int second_character = fgetc(input);
    int third_character = fgetc(input);

    if (first_character == EOF || second_character == EOF)
    {
        printf("Could not read file\n");
        fclose(input);
        return 1;
    }

    if (first_character == EOF || second_character == EOF || third_character == EOF)
    {
        printf("Invalid PPM magic number\n");
        fclose(input);
        return 1;
    }

    if (third_character != '\n')
    {
        printf("Invalid PPM header\n");
        fclose(input);
        return 1;
    }
    printf("%c%c\n", first_character, second_character);

    fclose(input);

    return 0;
}
