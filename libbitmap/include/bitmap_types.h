#pragma once
#include <stdint.h>
#include <stdio.h>

typedef struct bitmap_t
{
    size_t size;
    uint8_t *bits;
} bitmap_t;

typedef struct
{
    void *handle;
    char name[32];
    bitmap_t* (*OPERATION)(bitmap_t*, bitmap_t*);
} plugin_t;
