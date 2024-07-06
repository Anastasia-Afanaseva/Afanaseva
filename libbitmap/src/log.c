#include "log.h"

#if !defined SYSLOG
char level[][LEVEL_LOG_STRLEN] = {"LOG_EMERG", "LOG_ALERT", "LOG_CRIT", "LOG_ERR",
                                  "LOG_WARNING", "LOG_NOTICE", "LOG_INFO", "LOG_DEBUG"};

char* time_log(void)
{
    // Переменная для сохранения текущего времени
    long int ttime;
    ttime = time(NULL);
    char* time_1 = ctime(&ttime);
    time_1[strlen(time_1) - 1] = '\0';
    return time_1;
}
#endif

#if defined SYSLOG
void write_log(int level_log, const char* format, ...)
{
    va_list arg;
    openlog("LIBBITMAP", LOG_PID, LOG_USER);
    va_start(arg, format);
    vsyslog(level_log, format, arg);
    va_end(arg);
    closelog();
    return;
}
#elif defined FILE_LOG
#define LOG_PATH_LEN 255
char log_path[LOG_PATH_LEN] = {0};
void log_path_add(char* path)
{
    snprintf(log_path, LOG_PATH_LEN, "%s", path);
}

void write_log(int level_log, const char* format, ...)
{
    va_list arg;
    FILE* fd = NULL;

    if (strlen(log_path) == 0)
    {
        printf("\nНе указан путь к лог файлу");
        return;
    }

    if((fd = fopen(log_path, "a+")) == NULL)
    {
        printf("\nНе удалось открыть файл");
        return;
    }

    va_start(arg, format);
    fprintf(fd, "\n%s LIBBITMAP %s ", time_log(), level[level_log]);
    vfprintf(fd, format, arg);
    va_end(arg);
    fclose(fd);
    return;
}
#else
void write_log(int level_log, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    fprintf(stderr, "\n%s LIBBITMAP %s ", time_log(), level[level_log]);
    vfprintf(stderr, format, arg);
    va_end(arg);
    return;
}
#endif
