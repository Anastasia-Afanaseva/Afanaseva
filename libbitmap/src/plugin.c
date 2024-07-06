#include "plugin.h"

#define PLUGIN_EXT ".so"
#define PLUGIN_ELEN 3

#define PLUGIN_NAME_START "libplugin"
#define PLUGIN_FOO_NAME_START "plugin_"

plugin_t *plugins = NULL;
uint8_t plugin_cnt = 0;
char** list_of_plugins = NULL;

/* функционал подключения плагинов */
int init_plugin(char* plugin_path)
{
    log_debug("Enter");
    char plugin_str[512] = {0};
    struct dirent *de;
    size_t nlen;
    char *error;

    /* Открываем дирректорию, где хранятся плагины */
    DIR *dp = opendir(plugin_path);

    if(!dp)
    {
        log_err("Can't open current directory ret %d", 1);
        return 1;
    }

    /* Считаем кол-во плагинов */
    while((de = readdir(dp)))
    {
        nlen = strlen(de->d_name);

        if(nlen > PLUGIN_ELEN && strstr(de->d_name, PLUGIN_EXT))
        {
            plugin_cnt++;
        }
    }

    /* Выделяем массив структур под плагины */
    plugins = calloc(sizeof(plugin_t), plugin_cnt);

    if(plugins == NULL)
    {
        log_err("Can't allocate memory ret %d", 1);
        closedir(dp);
        return 1;
    }

    /* Устанавливаем метку в начало дирректории */
    rewinddir(dp);
    plugin_cnt = 0;

    /* Подключаем бибилиотеки, добавляем функцию с плагина */
    while((de = readdir(dp)))
    {
        nlen = strlen(de->d_name);

        if(nlen > PLUGIN_ELEN && strstr(de->d_name, PLUGIN_EXT))
        {
            /*Подключаем библиотеку*/
            snprintf(plugin_str, sizeof(plugin_str), "%s%s", plugin_path, de->d_name);
            void *handle = dlopen(plugin_str, RTLD_LAZY);

            if(!handle)
            {
                deinit_plugin();
                closedir(dp);
                log_err("Can't allocate memory ret %d\n", 1);
                return 1;
            }

            plugins[plugin_cnt].handle = handle;

            /* Вытягиваем название ф-ии */
            char *start = strstr(de->d_name, PLUGIN_NAME_START);
            start = start + strlen(PLUGIN_NAME_START);
            char *end = strstr(de->d_name, PLUGIN_EXT);
            size_t len_name = end - start;
            strncpy(plugins[plugin_cnt].name, start, len_name);

            /* Подключаем ф-ию плагина */
            memset(plugin_str, 0, sizeof(plugin_str));
            snprintf(plugin_str, sizeof(plugin_str), "%s%s", PLUGIN_FOO_NAME_START, plugins[plugin_cnt].name);
            bitmap_t* (*foo)(bitmap_t*, bitmap_t*);
            foo = dlsym(handle, plugin_str);

            if((error = dlerror()) != NULL)
            {
                plugin_cnt++;
                deinit_plugin();
                closedir(dp);
                log_err("Can't get plugin foo ret %d", 1);
                return 1;
            }

            plugins[plugin_cnt].OPERATION = foo;
            log_debug("%s function enabled", plugins[plugin_cnt].name);
            plugin_cnt++;
        }
    }

    create_list_connected_plugin();
    log_debug("Done ret %d", 0);
    closedir(dp);
    return 0;
}

/* функционал вызова плагина */
bitmap_t* call_plugin(bitmap_t* bitmap_1, bitmap_t* bitmap_2, const char* name)
{
    log_debug("Enter");

    for(int i = 0; i < plugin_cnt; i++)
    {
        if(strcmp(plugins[i].name, name) == 0)
        {
            return plugins[i].OPERATION(bitmap_1, bitmap_2);
        }
    }

    log_debug("Done but %s is not in the list of connected functions", name);
    return NULL;
}

/* функционал вывода создания массива подключенных операторов */
void create_list_connected_plugin(void)
{
    log_debug("Enter");
    list_of_plugins = (char**)calloc(sizeof(char*), plugin_cnt);

    if(list_of_plugins == NULL)
    {
        log_err("Can't allocate memory");
        return;
    }

    for(int i = 0; i < plugin_cnt; i++)
    {
        list_of_plugins[i] = plugins[i].name;
    }

    log_debug("Done");
    return;
}

const char** connected_plugins(void)
{
    return (const char**)list_of_plugins;
}

/* функционал отключения плагинов и освобождения памяти */
int deinit_plugin(void)
{
    log_debug("Enter");

    for(int i = 0; i < plugin_cnt; i++)
    {
        dlclose(plugins[i].handle);
    }

    free(plugins);
    free(list_of_plugins);
    log_debug("Done");
    return 0;
}

int plug_plugins_cnt_get(void)
{
    return plugin_cnt;
}
