#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "color.h"
#include "error_keys.h"
#include "get_codeline.h"
#include "struct_file.h"

ErrorKeys InitCodeFile(FileInf* file)
{
    file->stream = fopen(file->name, file->typestream);
    struct stat st = {};
    stat(file->name, &st);
    file->size = st.st_size;
    if (file->stream == NULL)
    {
        return FILE_ERROR;
    }

    return NO_ERRORS;
}

ErrorKeys GetBuffer(char** buffer, FileInf* file)
{
    size_t buf_size = fread(*buffer, sizeof(char), file->size, file->stream);
    if (buf_size != file->size)
    {
        printf(RED("error: buffer size is wrong\n file size = %d\n buffer_size = %d\n"), file->size, buf_size);
        return FILE_ERROR;
    }

    return NO_ERRORS;
}
