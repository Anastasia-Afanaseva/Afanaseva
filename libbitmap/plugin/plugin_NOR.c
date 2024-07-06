#include <stdlib.h>
#include "bitmap_types.h"
#include "log.h"
#include "bitmap.h"

bitmap_t* plugin_NOR(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    log_debug("Enter");
    bitmap_t* bitmap = bitmap_or(bitmap1, bitmap2);
    bitmap_not(bitmap);
    log_debug("Done");
    return bitmap;
}
