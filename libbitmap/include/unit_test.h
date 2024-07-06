#include "bitmap.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define LOG_PATH "logs/unit_logs.txt"

#define LOG_LEN 1024
#define TIME_LEN 80

void unit_write_log(const char* log_str);
char* unit_log_maker(clock_t start, clock_t end, const char* operation, const char* result, size_t bitmap_size);
void unit_clear_logs();
bitmap_t* test_bitmap_generate(size_t);
void test_bitmap_copy(bitmap_t*, bitmap_t*, size_t);
void test_bitmap_clone(bitmap_t*, size_t);
void test_bitmap_concat(bitmap_t*, bitmap_t*, size_t);
void test_bitmap_and(bitmap_t*, bitmap_t*, size_t);
void test_bitmap_or(bitmap_t*, bitmap_t*, size_t);
void test_bitmap_xor(bitmap_t*, bitmap_t*, size_t);
void test_bitmap_compare(bitmap_t*, bitmap_t*, size_t);
void test_bitmap_reset(bitmap_t*, size_t);
void test_bitmap_not(bitmap_t*, size_t);
void test_bitmap_set_get_bit(bitmap_t*, size_t);
void unit_test_global();
