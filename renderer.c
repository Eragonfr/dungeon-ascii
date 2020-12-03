#include "renderer.h"

const char CHAR_SEQ[19] = { 27, 91, 51, 56, 59, 50, 59, 48, 48, 48, 59, 48, 48, 48, 59, 48, 48, 48, 109 };
const int CHAR_SEQ_LENGTH = sizeof(CHAR_SEQ);

void setColorComponent(char* buffer, int color, int off)
{
    buffer[off + 0] = color / 100 + '0';
    buffer[off + 1] = color / 10 % 10 + '0';
    buffer[off + 2] = color % 10 + '0';
}

void setColor(char* buffer, int r, int g, int b)
{
    memcpy_s(buffer, CHAR_SEQ_LENGTH, CHAR_SEQ, CHAR_SEQ_LENGTH);

    setColorComponent(buffer, r,  7); // r
    setColorComponent(buffer, g, 11); // g
    setColorComponent(buffer, b, 15); // b
}

void renderMap(RgbChar* map, int count)
{
    char* buffer = malloc(count * 20);
    int off = 0;

    RgbChar lastChar = { -1, -1, -1, -1 };

    for (size_t i = 0; i < count; i++)
    {
        RgbChar rgbch = map[i];

        if (!colorEquals(rgbch, lastChar))
        {
            setColor(buffer + off, rgbch.r, rgbch.g, rgbch.b);
            off += CHAR_SEQ_LENGTH;

            lastChar = rgbch;
        }

        buffer[off] = rgbch.ch;
        off++;
    }

    buffer[off] = '\0';
    printf(buffer);

    //free(buffer);
}

int colorEquals(RgbChar a, RgbChar b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}