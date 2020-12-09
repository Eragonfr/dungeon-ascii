#include "renderer.h"

// default sequence header
const unsigned char COLOR_SEQ_HEADER[7] = { 27, 91, 51, 56, 59, 50, 59 };
const int COLOR_SEQ_HEADER_SIZE = sizeof(COLOR_SEQ_HEADER);

int writeColorComponent(char* buffer, unsigned char color, unsigned int off)
{
    // separe color digits
    unsigned char digits[3] =
    {
        color / 100 + 48,
        color / 10 % 10 + 48,
        color % 10 + 48
    };
     
    // count of digits to write
    int size = 0;
    for (int i = 0; i < 3; i++)
    {
        if ((digits[i] == 48 && size != 0) || digits[i] != 48)
        {
            size++;
        }
    }

    // handle 0
    if (size == 0) { size = 1; }
    
    // write digits to buffer
    int digitOff = 3 - size;
    for (int i = 0; i < size; i++)
    {
        buffer[off + i] = digits[i + digitOff];
    }

    off += size;

    // add separator
    buffer[off++] = 59;
    
    return size + 1;
}

int writeColor(char* buffer, unsigned char r, unsigned char g, unsigned char b)
{
    // default header
    memcpy(buffer, COLOR_SEQ_HEADER, COLOR_SEQ_HEADER_SIZE);

    int off = COLOR_SEQ_HEADER_SIZE;

    // write color components
    off += writeColorComponent(buffer, r, off); // r
    off += writeColorComponent(buffer, g, off); // g
    off += writeColorComponent(buffer, b, off); // b

    // add seperator
    buffer[off - 1] = 109;

    return off;
}

void renderMap(const RgbChar* map, unsigned int count)
{
    // prepare buffer   
    char* buffer = calloc(count * 20, sizeof(char));
    if (buffer == NULL) { return; }

    int off = 0;

    rgbch lastChar = { -1, -1, -1, -1 };

    // simplify map
    for (size_t i = 0; i < count; i++)
    {
        rgbchar rgbch = map[i];

        if (!colorEquals(rgbch, lastChar))
        {
            off += writeColor(buffer + off, rgbch.r, rgbch.g, rgbch.b);

            lastChar = rgbch;
        }

        buffer[off] = rgbch.ch;
        off++;
    }

    buffer[off] = '\0';

    printf(buffer);

    free(buffer);
}