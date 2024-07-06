#include "bitmap.h"

#define LOG_PATH "unit_logs.txt"
#define LOG_LEN 1024
#define TIME_LEN 80

void unit_write_log(const char* log_str)
{
    FILE *log;

    if(!(log = fopen(LOG_PATH, "a")))
    {
        perror("Error opening log file");
        return;
    }

    fprintf(log, "%s", log_str);

    if(fclose(log) == EOF)
    {
        perror("Error occured while closing file\n");
    }
}

char* unit_log_maker(clock_t start, clock_t end, const char* operation, const char* result, size_t bitmap_size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[TIME_LEN];
    strftime(time_str, TIME_LEN, "%Y-%m-%d %H:%M:%S", tm_info);
    char* log_str = (char*)malloc(LOG_LEN);

    if(!log_str)
    {
        return NULL;
    }

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    snprintf(log_str, LOG_LEN, "%s - Operation: %s - Size: %lu bytes - Time: %f seconds - Result: %s\n", time_str, operation, bitmap_size, cpu_time_used, result);
    return log_str;
}

void unit_clear_logs()
{
    FILE *log;

    if(!(log = fopen(LOG_PATH, "w")))
    {
        perror("Error clearing log file");
        return;
    }

    if(fclose(log) == EOF)
    {
        perror("Error occured while closing file\n");
    }
}

bitmap_t* test_bitmap_generate(size_t bit_count)
{
    clock_t start = clock();
    bitmap_t* bitmap = bitmap_generate(bit_count);
    clock_t end = clock();
    char* log = unit_log_maker(start, end, "generate", bitmap ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
    return bitmap;
}

void test_bitmap_xor(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t bit_count)
{
    clock_t start = clock();
    bitmap_t *xor_bitmap = bitmap_xor(bitmap1, bitmap2);
    clock_t end = clock();
    int pass = 1;

    if(xor_bitmap)
    {
        for(size_t i = 0; i < bit_count; i++)
        {
            if(xor_bitmap->bits[i] != (bitmap1->bits[i] ^ bitmap2->bits[i]))
            {
                pass = 0;
                break;
            }
        }
    }

    else
    {
        pass = 0;
    }

    char* log = unit_log_maker(start, end, "xor", pass ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
    bitmap_remove(xor_bitmap);
}

void test_bitmap_copy(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t bit_count)
{
    clock_t start = clock();
    int result = bitmap_copy(bitmap1, bitmap2);
    clock_t end = clock();
    int pass = (result == 0 && memcmp(bitmap1->bits, bitmap2->bits, (bit_count + 7) / 8) == 0);
    char* log = unit_log_maker(start, end, "copy", pass ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
}

void test_bitmap_clone(bitmap_t* bitmap, size_t bit_count)
{
    clock_t start = clock();
    bitmap_t *clone = bitmap_clone(bitmap);
    clock_t end = clock();
    char* log = unit_log_maker(start, end, "clone", (clone && memcmp(bitmap->bits, clone->bits, (bit_count + 7) / __CHAR_BIT__) == 0) ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
    bitmap_remove(clone);
}

void test_bitmap_concat(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t bit_count)
{
    clock_t start = clock();
    bitmap_t *concat = bitmap_concat(bitmap1, bitmap2);
    clock_t end = clock();
    int pass = 1;

    if(concat && concat->size == bitmap1->size + bitmap2->size)
    {
        if(memcmp(concat->bits, bitmap1->bits, bit_count) || memcmp(concat->bits + bit_count, bitmap2->bits, bit_count))
        {
            pass = 0;
        }   
    }

    else
    {
        pass = 0;
    }

    char* log = unit_log_maker(start, end, "concat", pass ? "Passed" : "Failed", bit_count + bit_count);
    unit_write_log(log);
    free(log);
    bitmap_remove(concat);
}

void test_bitmap_and(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t bit_count)
{
    clock_t start = clock();
    bitmap_t *and_bitmap = bitmap_and(bitmap1, bitmap2);
    clock_t end = clock();
    int pass = 1;

    if(and_bitmap)
    {
        for(size_t i = 0; i < bit_count; i++)
        {
            if(and_bitmap->bits[i] != (bitmap1->bits[i] & bitmap2->bits[i]))
            {
                pass = 0;
                break;
            }
        }
    }

    else
    {
        pass = 0;
    }

    char* log = unit_log_maker(start, end, "and", pass ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
    bitmap_remove(and_bitmap);
}

void test_bitmap_or(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t bit_count)
{
    clock_t start = clock();
    bitmap_t *or_bitmap = bitmap_or(bitmap1, bitmap2);
    clock_t end = clock();
    int pass = 1;

    if(or_bitmap)
    {
        for(size_t i = 0; i < bit_count; i++)
        {
            if(or_bitmap->bits[i] != (bitmap1->bits[i] | bitmap2->bits[i]))
            {
                pass = 0;
                break;
            }
        }
    }

    else
    {
        pass = 0;
    }

    char* log = unit_log_maker(start, end, "or", pass ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
    bitmap_remove(or_bitmap);
}

void test_bitmap_compare(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t bit_count)
{
    clock_t start = clock();
    int compare_result = bitmap_compare(bitmap1, bitmap2);
    int result = 0;
    clock_t end = clock();

    if(compare_result < -1 || compare_result > 1)
    {
        result = 1;
    }

    char* log = unit_log_maker(start, end, "compare", result == 0 ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
}

void test_bitmap_reset(bitmap_t* bitmap, size_t bit_count)
{
    
    clock_t start = clock();
    bitmap_reset(bitmap);
    clock_t end = clock();
    int all_zero = 1;

    for(size_t i = 0; i < bit_count; i++)
    {
        if(bitmap->bits[i] != 0)
        {
            all_zero = 0;
            break;
        }
    }

    char* log = unit_log_maker(start, end, "reset", all_zero ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
}

void test_bitmap_not(bitmap_t* bitmap, size_t bit_count)
{
    
    bitmap_t* bitmap2_clone = bitmap_clone(bitmap);
    clock_t start = clock();
    bitmap_not(bitmap);
    clock_t end = clock();
    int all_inverted = 1;

    for(size_t i = 0; i < bit_count; i++)
    {
        if(bitmap->bits[i] == bitmap2_clone->bits[i])
        {
            all_inverted = 0;
            break;
        }
    }

    char* log = unit_log_maker(start, end, "NOT operation", all_inverted ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
    bitmap_remove(bitmap2_clone);
}

void test_bitmap_set_get_bit(bitmap_t* bitmap, size_t bit_count)
{
    clock_t start = clock();
    bitmap_set_bit(bitmap, 0, 0);
    int set_get_result = bitmap_get_bit(bitmap, 0) == 0;
    clock_t end = clock();
    char* log = unit_log_maker(start, end, "set and get bit", set_get_result ? "Passed" : "Failed", bit_count);
    unit_write_log(log);
    free(log);
}

int unit_test_global(void)
{
    unit_clear_logs();
    srand(time(NULL));
    size_t sizes[] = {32, 2 * 1024, 10 * 1024, 10 * 1024 * 1024};
    size_t num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    bitmap_t* bitmap1 = NULL;
    bitmap_t* bitmap2 = NULL;

    for(size_t i = 0; i < num_sizes; i++)
    {
        char log_header[LOG_LEN];
        snprintf(log_header, LOG_LEN, "-<{ Unit-testing on %lu bytes bitmaps }>-\n", sizes[i]);
        unit_write_log(log_header);
        bitmap1 = test_bitmap_generate(sizes[i]);
        bitmap2 = test_bitmap_generate(sizes[i]);
        test_bitmap_clone(bitmap1, sizes[i]);
        test_bitmap_concat(bitmap1, bitmap2, sizes[i]);
        test_bitmap_and(bitmap1, bitmap2, sizes[i]);
        test_bitmap_or(bitmap1, bitmap2, sizes[i]);
        test_bitmap_xor(bitmap1, bitmap2, sizes[i]);
        test_bitmap_compare(bitmap1, bitmap2, sizes[i]);
        test_bitmap_copy(bitmap1, bitmap2, sizes[i]);
        test_bitmap_reset(bitmap1, sizes[i]);
        test_bitmap_not(bitmap1, sizes[i]);
        test_bitmap_set_get_bit(bitmap1, sizes[i]);
        bitmap_remove(bitmap1);
        bitmap_remove(bitmap2);
    }

    return 0;
}
