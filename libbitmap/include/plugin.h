#pragma once
#include "bitmap_types.h"
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "log.h"

int deinit_plugin(void);
int init_plugin(char* plugin_path);
bitmap_t* call_plugin(bitmap_t* bitmap_1, bitmap_t* bitmap_2, const char* name);
void create_list_connected_plugin(void);
const char** connected_plugins(void);
int plug_plugins_cnt_get(void);
