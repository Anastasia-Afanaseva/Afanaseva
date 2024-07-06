#include "bitmap.h"
#include <stdlib.h>
#include <time.h>

bitmap_t* stress_bitmap_generate(size_t);
void stress_bitmap_compare(bitmap_t*, bitmap_t*, size_t);
void stress_bitmap_copy(bitmap_t*, bitmap_t*, size_t);
void stress_bitmap_clone(bitmap_t*, size_t);
void stress_bitmap_concat(bitmap_t*, bitmap_t*, size_t);
void stress_bitmap_reset(bitmap_t*, size_t);
void stress_bitmap_or(bitmap_t*, bitmap_t*, size_t);
void stress_bitmap_and(bitmap_t*, bitmap_t*, size_t);
void stress_bitmap_xor(bitmap_t*, bitmap_t*, size_t);
void stress_bitmap_not(bitmap_t*, size_t);
void stress_bitmap_get_bit(bitmap_t*, size_t, size_t);
void stress_bitmap_set_bit(bitmap_t*, size_t, uint8_t, size_t);
void stress_test_global(bitmap_t*, bitmap_t*, size_t);
void stress_write_log(char*);
void stress_clear_logs();
char* stress_log_maker(clock_t, clock_t, char*, char*, size_t);
