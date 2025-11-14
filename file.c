#include "file.h"
#include "stdio.h"
#include "stdlib.h"


char* getFile(const char *str) {
    FILE *file = fopen(str, "rb");
    if (!file) {
        fprintf(stderr, "File not found\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET); // rewind to beginning

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    if (bytesRead != size) {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[size] = '\0'; // null-terminate
    fclose(file);

    return buffer;
}
