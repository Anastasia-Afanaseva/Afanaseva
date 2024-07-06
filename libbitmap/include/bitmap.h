#pragma once
#include "bitmap_types.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "log.h"

bitmap_t* bitmap_init(char*);
bitmap_t* bitmap_generate(size_t);
void bitmap_remove(bitmap_t*);
int bitmap_compare(bitmap_t*, bitmap_t*);
int bitmap_copy(bitmap_t*, bitmap_t*);
bitmap_t* bitmap_clone(bitmap_t*);
bitmap_t* bitmap_concat(bitmap_t*, bitmap_t*);
void bitmap_reset(bitmap_t*);
bitmap_t* bitmap_or(bitmap_t*, bitmap_t*);
bitmap_t* bitmap_and(bitmap_t*, bitmap_t*);
bitmap_t* bitmap_xor(bitmap_t*, bitmap_t*);
void bitmap_not(bitmap_t*);
uint8_t bitmap_get_bit(bitmap_t*, size_t);
uint8_t bitmap_set_bit(bitmap_t*, size_t, uint8_t);
