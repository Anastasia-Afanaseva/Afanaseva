#pragma once
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define LEVEL_LOG_STRLEN 15

#if defined FILE_LOG
void log_path_add(char* path);
#endif

void write_log(int level_log, const char* format, ...);

#define log_err(fmt, ...) \
    write_log(LOG_ERR, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_notice(fmt, ...) \
    write_log(LOG_NOTICE, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_warning(fmt, ...) \
    write_log(LOG_WARNING, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_info(fmt, ...) \
    write_log(LOG_INFO, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_crit(fmt, ...) \
    write_log(LOG_CRIT, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_emerg(fmt, ...) \
    write_log(LOG_EMERG, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_debug(fmt, ...) \
    write_log(LOG_DEBUG, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define log_alert(fmt, ...) \
    write_log(LOG_ALERT, "%s %s %d " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);
