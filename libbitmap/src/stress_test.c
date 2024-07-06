#include "stress_test.h"
#define LOG_PATH "stress_logs.txt"
#define LOG_LEN 1024
#define TIME_LEN 80

bitmap_t* stress_bitmap_generate(size_t size)
{
    clock_t start;
    clock_t end;
    bitmap_t *bitmap;
    char *log;
    char result[TIME_LEN] = "success";
    start = clock();
    bitmap = bitmap_generate(size);
    end = clock();

    if(!bitmap)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "generate", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }

    return bitmap;
}

void stress_bitmap_clone(bitmap_t* bitmap, size_t size)
{
    clock_t start;
    clock_t end;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap)
    {
        bitmap = stress_bitmap_generate(size);
    }

    start = clock();
    bitmap_t* clone = bitmap_clone(bitmap);
    end = clock();

    if(!clone)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "clone", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }

    bitmap_remove(clone);
}

void stress_write_log(char* log_str)
{
    FILE *log;

    if(!(log = fopen(LOG_PATH, "a")))
    {
        if(!(log = fopen(LOG_PATH, "w")))
        {
            printf("Error occured while opening file\n");
            return;
        }
    }

    fprintf(log, "%s", log_str);

    if(fclose(log) == EOF)
    {
        printf("Error occured while closing file\n");
    }
}

void stress_clear_logs()
{
    FILE *log;

    if(!(log = fopen(LOG_PATH, "w")))
    {
        printf("Error occured while cleaning file\n");
        return;
    }

    if(fclose(log) == EOF)
    {
        printf("Error occured while cleaning file\n");
    }
}

char* stress_log_maker(clock_t start, clock_t end, char* operation, char* result, size_t bitmap_size)
{
    time_t now;
    struct tm *tm_info;
    char time_str[TIME_LEN];
    char* log_str = malloc(LOG_LEN);

    if(!log_str)
    {
        return NULL;
    }

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    time(&now);
    tm_info = localtime(&now);
    strftime(time_str, TIME_LEN, "%Y-%m-%d %H:%M:%S", tm_info);
    snprintf(log_str, LOG_LEN, "%s - Operation: %s - Size: %ld bytes - Time of exec: %f sec - result: %s\n", 
    time_str, operation,  bitmap_size, cpu_time_used, result);
    return log_str;
}

void stress_bitmap_copy(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    clock_t start;
    clock_t end;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(size);
    }

    if(!bitmap2)
    {
        bitmap2 = bitmap_init("0");
    }

    if(!bitmap2->bits)
    {
        bitmap2->size = size;
        bitmap2->bits = malloc(bitmap2->size);
    }

    start = clock();
    bitmap_copy(bitmap1, bitmap2);
    end = clock();

    if(!bitmap2)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "copy", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}

void stress_bitmap_concat(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    clock_t start;
    clock_t end;
    bitmap_t* concat;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(size);
    }

    if(!bitmap2)
    {
        bitmap2 = stress_bitmap_generate(size);
    }

    start = clock();
    concat = bitmap_concat(bitmap1, bitmap2);
    end = clock();

    if(!concat)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "concat", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }

    bitmap_remove(concat);
}

void stress_bitmap_reset(bitmap_t* bitmap, size_t size)
{
    clock_t start;
    clock_t end;
    char *log;
    char result[] = "success";

    if(!bitmap)
    {
        bitmap = stress_bitmap_generate(size);
    }

    start = clock();
    bitmap_reset(bitmap);
    end = clock();
    log = stress_log_maker(start, end, "reset", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}

void stress_bitmap_not(bitmap_t* bitmap, size_t size)
{
    clock_t start;
    clock_t end;
    char *log;
    char result[] = "success";

    if(!bitmap)
    {
        bitmap = stress_bitmap_generate(size);
    }

    start = clock();
    bitmap_not(bitmap);
    end = clock();
    log = stress_log_maker(start, end, "not", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}

void stress_bitmap_or(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    clock_t start;
    clock_t end;
    bitmap_t* bitmap_res;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(size);
    }

    if(!bitmap2)
    {
        bitmap2 = stress_bitmap_generate(size);
    }

    start = clock();
    bitmap_res = bitmap_or(bitmap1, bitmap2);
    end = clock();

    if(!bitmap_res)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "or", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }

    bitmap_remove(bitmap_res);
}

void stress_bitmap_xor(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    clock_t start;
    clock_t end;
    bitmap_t* bitmap_res;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(size);
    }

    if(!bitmap2)
    {
        bitmap2 = stress_bitmap_generate(size);
    }

    start = clock();
    bitmap_res = bitmap_xor(bitmap1, bitmap2);
    end = clock();

    if(!bitmap_res)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "xor", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }

    bitmap_remove(bitmap_res);
}

void stress_bitmap_and(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    clock_t start;
    clock_t end;
    bitmap_t* bitmap_res;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(size);
    }

    if(!bitmap2)
    {
        bitmap2 = stress_bitmap_generate(size);
    }

    start = clock();
    bitmap_res = bitmap_and(bitmap1, bitmap2);
    end = clock();

    if(!bitmap_res)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "and", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }

    bitmap_remove(bitmap_res);
}

void stress_bitmap_get_bit(bitmap_t* bitmap, size_t index, size_t size)
{
    clock_t start;
    clock_t end;
    uint8_t get_res;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap)
    {
        bitmap = stress_bitmap_generate(size);
    }

    start = clock();
    get_res = bitmap_get_bit(bitmap, index);
    end = clock();

    if(get_res == 2)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "get_bit", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}

void stress_bitmap_set_bit(bitmap_t* bitmap, size_t index, uint8_t bit, size_t size)
{
    clock_t start;
    clock_t end;
    uint8_t get_res;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap)
    {
        bitmap = stress_bitmap_generate(size);
    }

    start = clock();
    get_res = bitmap_set_bit(bitmap, index, bit);
    end = clock();

    if(get_res)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "set_bit", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}

void stress_bitmap_compare(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    clock_t start;
    clock_t end;
    int compare_res;
    char *log;
    char result[TIME_LEN] = "success";

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(size);
    }

    if(!bitmap2)
    {
        bitmap2 = stress_bitmap_generate(size);
    }

    start = clock();
    compare_res = bitmap_compare(bitmap1, bitmap2);
    end = clock();

    if(compare_res == -3)
    {
        strcpy(result, "failed");
    }

    log = stress_log_maker(start, end, "compare", result, size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}

void stress_test_global(bitmap_t* bitmap1, bitmap_t* bitmap2, size_t size)
{
    srand(time(NULL));
    clock_t start;
    clock_t end;
    char *log;
    size_t bitmap1_bytes;
    size_t actual_size = size;
    start = clock();

    if(!bitmap1)
    {
        bitmap1 = stress_bitmap_generate(actual_size);
    }

    if(!bitmap2)
    {
        bitmap2 = stress_bitmap_generate(actual_size);
    }

    if(!bitmap1 || !bitmap2)
    {
        stress_write_log("Failed generated bitmap");
        return;
    }

    bitmap1_bytes = (size_t)(bitmap1->size / __CHAR_BIT__);
    stress_bitmap_compare(bitmap1, bitmap2, actual_size);
    stress_bitmap_concat(bitmap1, bitmap2, actual_size);
    stress_bitmap_or(bitmap1, bitmap2, actual_size);
    stress_bitmap_and(bitmap1, bitmap2, actual_size);
    stress_bitmap_xor(bitmap1, bitmap2, actual_size);
    stress_bitmap_copy(bitmap1, bitmap2, actual_size);
    bitmap_remove(bitmap2);
    stress_bitmap_clone(bitmap1, actual_size);
    stress_bitmap_get_bit(bitmap1, 1 + rand() % bitmap1->size, bitmap1_bytes);
    stress_bitmap_set_bit(bitmap1, 1 + rand() % bitmap1->size, rand() % 2, bitmap1_bytes);
    stress_bitmap_not(bitmap1, actual_size);
    stress_bitmap_reset(bitmap1, actual_size);
    bitmap_remove(bitmap1);
    end = clock();
    log = stress_log_maker(start, end, "global", "success", actual_size);

    if(!log)
    {
        stress_write_log("ERROR");
    }

    else
    {
        stress_write_log(log);
        free(log);
    }
}
