#include "file.h"
#include "stdio.h"
#include "stdlib.h"


char* getFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "File not found: %s\n", filename);
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }

    long size = ftell(file);
    if (size < 0) {
        fclose(file);
        return NULL;
    }

    rewind(file); // same as fseek(file, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    if (bytesRead != (size_t)size) {
        fprintf(stderr, "Could not read the entire file: %s\n", filename);
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[size] = '\0'; // null-terminate
    fclose(file);

    return buffer;
}
