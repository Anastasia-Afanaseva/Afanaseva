#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bitmap.h"

bitmap_t* bitmap_init(char* bit_str)
{
    log_debug("Enter");
    bitmap_t *bitmap = malloc(sizeof(struct bitmap_t));

    if(!bitmap)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    bitmap->size = strlen(bit_str);
    bitmap->bits = calloc(((bitmap->size / __CHAR_BIT__) + (bitmap->size % __CHAR_BIT__ != 0)), sizeof(uint8_t));

    if(!bitmap->bits)
    {
        log_err("Can't allocate memory");
        free(bitmap);
        return NULL;
    }

    for(size_t i = 0; i < bitmap->size; i++)
    {
        if(bit_str[i] == '1')
        {
            bitmap->bits[i / __CHAR_BIT__] |= (1 << (7 - i % __CHAR_BIT__));
        }

        else if(bit_str[i] == '0')
        {
            bitmap->bits[i / __CHAR_BIT__] &= ~(1 << (7 - i % __CHAR_BIT__));
        }

        else
        {
            log_err("Bitmap consists only of 0 and 1");
            free(bitmap->bits);
            free(bitmap);
            return NULL;
        }
    }

    log_debug("Done");
    return bitmap;
}

bitmap_t* bitmap_generate(size_t size)
{
    log_debug("Enter");
    bitmap_t *bitmap = malloc(sizeof(bitmap_t));
    
    if(!bitmap)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    bitmap->size = (size_t)(size * __CHAR_BIT__);
    bitmap->bits = calloc(size, sizeof(uint8_t));

    if(!bitmap->bits)
    {
        log_err("Can't allocate memory");
        free(bitmap);
        return NULL;
    }

    srand(time(NULL));

    for(size_t i = 0; i < size; i++) 
    {
        bitmap->bits[i] = rand() % 256;
    }
    
    log_debug("Done");
    return bitmap;
}

void bitmap_remove(bitmap_t* bitmap)
{
    log_debug("Enter");

    if(!bitmap)
    {
        return;
    }

    if(bitmap->bits)
    {
        free(bitmap->bits);
    }

    free(bitmap);
    log_debug("Done");
}

int bitmap_copy(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    log_debug("Enter");

    if(!bitmap1 || !bitmap1->bits || !bitmap2 || !bitmap2->bits)
    {
        log_err("Pointer value is NULL ret %d", -1);
        return -1;
    }

    size_t arr_size = (size_t)(bitmap1->size / __CHAR_BIT__ + (bitmap1->size % __CHAR_BIT__ != 0));

    if(bitmap1->size != bitmap2->size)
    {
        uint8_t* temp = calloc(arr_size, sizeof(uint8_t));

        if(!temp)
        {
            log_err("Can't allocate memory ret %d", -1);
            return -1;
        }

        bitmap2->size = bitmap1->size;
        free(bitmap2->bits);
        bitmap2->bits = temp;
    }

    memcpy(bitmap2->bits, bitmap1->bits, arr_size);
    log_debug("Done ret %d", 0);
    return 0;
}

bitmap_t* bitmap_clone(bitmap_t* bitmap)
{
    log_debug("Enter");

    if(!bitmap || !bitmap->bits)
    {
        log_err("Pointer value is NULL");
        return NULL;
    }

    size_t arr_size = (size_t)(bitmap->size / __CHAR_BIT__ + (bitmap->size % __CHAR_BIT__ != 0));
    bitmap_t* clone = malloc(sizeof(struct bitmap_t));

    if(!clone)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    clone->size = bitmap->size;
    clone->bits = calloc(arr_size, sizeof(uint8_t));

    if(!clone->bits)
    {
        log_err("Can't allocate memory");
        free(clone);
        return NULL;
    }

    memcpy(clone->bits, bitmap->bits, arr_size);
    log_debug("Done");
    return clone;
}

bitmap_t* bitmap_concat(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    log_debug("Enter");

    if(!bitmap1 || !bitmap1->bits || !bitmap2 || !bitmap2->bits)
    {
        log_err("Pointer value is NULL");
        return NULL;
    }

    size_t bitmap1_arr_size = (size_t)(bitmap1->size / __CHAR_BIT__ + (bitmap1->size % __CHAR_BIT__ != 0));
    size_t bitmap2_arr_size = (size_t)(bitmap2->size / __CHAR_BIT__ + (bitmap2->size % __CHAR_BIT__ != 0));
    size_t concat_arr_size;

    bitmap_t* concat_bitmap = malloc(sizeof(struct bitmap_t));

    if(!concat_bitmap)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    concat_bitmap->size = (size_t)(bitmap1->size + bitmap2->size);
    concat_arr_size = (size_t)(concat_bitmap->size / __CHAR_BIT__ + (concat_bitmap->size % __CHAR_BIT__ != 0));
    concat_bitmap->bits = calloc(concat_arr_size, sizeof(uint8_t));

    if(!concat_bitmap->bits)
    {
        log_err("Can't allocate memory");
        free(concat_bitmap);
        return NULL;
    }

    memcpy(concat_bitmap->bits, bitmap1->bits, bitmap1_arr_size);

    if(!(bitmap1->size % __CHAR_BIT__))
    {
        memcpy(concat_bitmap->bits + bitmap1_arr_size, bitmap2->bits, bitmap2_arr_size);
    }

    else
    {
        for(size_t i = 0; i < bitmap2->size; i++)
        {
            if(bitmap2->bits[i / __CHAR_BIT__] & (1 << (7 - i % __CHAR_BIT__)))
            {
                concat_bitmap->bits[(bitmap1->size + i) / __CHAR_BIT__] |= 1 << (7 - (bitmap1->size + i) % __CHAR_BIT__);
            }

            else
            {
                concat_bitmap->bits[(bitmap1->size + i) / __CHAR_BIT__] &= ~(1 << (7 - (bitmap1->size + i) % __CHAR_BIT__));
            }
        }
    }

    log_debug("Done");
    return concat_bitmap;
}

void bitmap_reset(bitmap_t* bitmap)
{
    log_debug("Enter");

    if(!bitmap || !bitmap->bits)
    {
        log_err("Pointer value is NULL");
        return;
    }

    size_t arr_size = (size_t)(bitmap->size / __CHAR_BIT__ + (bitmap->size % __CHAR_BIT__ != 0));
    memset(bitmap->bits, 0, arr_size);
    log_debug("Done");
}

void bitmap_not(bitmap_t* bitmap)
{
    log_debug("Enter");

    if(!bitmap || !bitmap->bits)
    {
        log_err("Pointer value is NULL");
        return;
    }

    size_t arr_size = (size_t)(bitmap->size / __CHAR_BIT__ + (bitmap->size % __CHAR_BIT__ != 0));

    for(size_t i = 0; i < arr_size; i++)
    {
        bitmap->bits[i] = ~bitmap->bits[i];
    }

    log_debug("Done");
}

uint8_t bitmap_get_bit(bitmap_t* bitmap, size_t index)
{
    log_debug("Enter");

    if(!bitmap || !bitmap->bits)
    {
        return 2;
    }

    if(index >= bitmap->size)
    {
        log_err("Bitmap index out of range ret %d", 2);
        return 2;
    }

    log_debug("Done");
    return (bitmap->bits[index / __CHAR_BIT__] & (1 << (7 - index % __CHAR_BIT__))) != 0;
}

uint8_t bitmap_set_bit(bitmap_t* bitmap, size_t index, uint8_t bit)
{
    log_debug("Enter");

    if(!bitmap || !bitmap->bits)
    {
        log_err("Pointer value is NULL ret %d", 2);
        return 2;
    }

    if(index >= bitmap->size)
    {
        log_err("Bitmap index out of range ret %d", 2);
        return 2;
    }

    if(bit == 0)
    {
        bitmap->bits[index / __CHAR_BIT__] &= ~(1 << (7 - index % __CHAR_BIT__));
    }

    else if(bit == 1)
    {
        bitmap->bits[index / __CHAR_BIT__] |= 1 << (7 - index % __CHAR_BIT__);
    }

    else
    {
        log_err("Bit may only be 0 or 1 ret %d", 3);
        return 3;
    }

    log_debug("Done ret %d", 0);
    return 0;
}

bitmap_t* bitmap_and(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    log_debug("Enter");

    if(!bitmap1 || !bitmap1->bits || !bitmap2 || !bitmap2->bits)
    {
        log_err("Pointer value is NULL");
        return NULL;
    }

    size_t max_size = bitmap1->size > bitmap2->size ? bitmap1->size : bitmap2->size;
    size_t min_size = bitmap1->size < bitmap2->size ? bitmap1->size : bitmap2->size;

    size_t min_arr_size = (size_t)((min_size + 7) / __CHAR_BIT__);
    size_t max_arr_size = (size_t)((max_size + 7) / __CHAR_BIT__);

    bitmap_t* and_bitmap = malloc(sizeof(bitmap_t));

    if(!and_bitmap)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    and_bitmap->size = max_size;
    and_bitmap->bits = calloc(max_arr_size, sizeof(uint8_t));

    if(!and_bitmap->bits)
    {
        log_err("Can't allocate memory");
        free(and_bitmap);
        return NULL;
    }

    for(size_t i = 0; i < min_arr_size; i++)
    {
        and_bitmap->bits[i] = bitmap1->bits[i] & bitmap2->bits[i];
    }

    log_debug("Done");
    return and_bitmap;
}

bitmap_t* bitmap_or(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    log_debug("Enter");

    if(!bitmap1 || !bitmap1->bits || !bitmap2 || !bitmap2->bits)
    {
        log_err("Pointer value is NULL");
        return NULL;
    }

    size_t min_size = bitmap1->size < bitmap2->size ? bitmap1->size : bitmap2->size;
    size_t max_size = bitmap1->size > bitmap2->size ? bitmap1->size : bitmap2->size;

    size_t min_arr_size = (size_t)((min_size + 7) / __CHAR_BIT__);
    size_t max_arr_size = (size_t)((max_size + 7) / __CHAR_BIT__);

    bitmap_t* or_bitmap = malloc(sizeof(bitmap_t));

    if(!or_bitmap)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    or_bitmap->size = max_size;
    or_bitmap->bits = calloc(max_arr_size, sizeof(uint8_t));

    if(!or_bitmap->bits)
    {
        log_err("Can't allocate memory");
        free(or_bitmap);
        return NULL;
    }

    for(size_t i = 0; i < min_arr_size; i++)
    {
        or_bitmap->bits[i] = bitmap1->bits[i] | bitmap2->bits[i];
    }

    if(bitmap1->size > bitmap2->size)
    {
        memcpy(or_bitmap->bits + min_arr_size, bitmap1->bits + min_arr_size, max_arr_size - min_arr_size);
    }

    else
    {
        memcpy(or_bitmap->bits + min_arr_size, bitmap2->bits + min_arr_size, max_arr_size - min_arr_size);
    }

    log_debug("Done");
    return or_bitmap;
}

bitmap_t* bitmap_xor(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    log_debug("Enter");

    if(!bitmap1 || !bitmap1->bits || !bitmap2 || !bitmap2->bits)
    {
        log_err("Pointer value is NULL");
        return NULL;
    }

    size_t min_size = bitmap1->size < bitmap2->size ? bitmap1->size : bitmap2->size;
    size_t max_size = bitmap1->size > bitmap2->size ? bitmap1->size : bitmap2->size;
    size_t min_arr_size = (size_t)((min_size + 7) / __CHAR_BIT__);
    size_t max_arr_size = (size_t)((max_size + 7) / __CHAR_BIT__);
    bitmap_t* xor_bitmap = malloc(sizeof(bitmap_t));

    if(!xor_bitmap)
    {
        log_err("Can't allocate memory");
        return NULL;
    }

    xor_bitmap->size = max_size;
    xor_bitmap->bits = calloc(max_arr_size, sizeof(uint8_t));

    if(!xor_bitmap->bits)
    {
        log_err("Can't allocate memory");
        free(xor_bitmap);
        return NULL;
    }

    for(size_t i = 0; i < min_arr_size; i++)
    {
        xor_bitmap->bits[i] = bitmap1->bits[i] ^ bitmap2->bits[i];
    }

    if(bitmap1->size > bitmap2->size)
    {
        memcpy(xor_bitmap->bits + min_arr_size, bitmap1->bits + min_arr_size, max_arr_size - min_arr_size);
    }

    else
    {
        memcpy(xor_bitmap->bits + min_arr_size, bitmap2->bits + min_arr_size, max_arr_size - min_arr_size);
    }

    log_debug("Done");
    return xor_bitmap;
}

int bitmap_compare(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    if(!bitmap1 || !bitmap1->bits || !bitmap2 || !bitmap2->bits)
    {
        log_err("Pointer value is NULL ret %d", -3);
        return -3;
    }

    size_t bitmap1_size = (size_t)((bitmap1->size + 7) / __CHAR_BIT__);
    size_t bitmap2_size = (size_t)((bitmap2->size + 7) / __CHAR_BIT__);

    if(bitmap1_size > bitmap2_size)
    {
        return 2;
    }

    else if(bitmap1_size < bitmap2_size)
    {
        return -2;
    }

    else
    {
        int cmp = memcmp(bitmap1->bits, bitmap2->bits, bitmap1_size);
        
        if(cmp > 0)
        {
            return 1;
        }

        else if(cmp < 0)
        {
            return -1;
        }

        else
        {
            return 0;
        }
    }
}
