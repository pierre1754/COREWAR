/*
** EPITECH PROJECT, 2021
** bread refacto to stop base on the \0
** File description:
** bread_file_len
*/

#include "blib.h"

static char *create_str(char *str, size_t size_base, size_t plus_size)
{
    str = realloc(str, size_base + plus_size + 1);
    if (str) {
        bmemset(str + size_base, '\0', plus_size + 1);
    }
    return str;
}

static char *bstrncat_forced(char *dest, char *src, size_t size_base,
    size_t plus_size)
{
    size_t j = 0;

    if (!dest || !src)
        return NULL;
    for (; j < plus_size; j++)
        dest[size_base + j] = src[j];
    dest[size_base + j] = '\0';
    return dest;
}


static file_t *bloop_read(int fd, char *temp, file_t *buffer, size_t size_read)
{
    size_t ret = 1;
    size_t len = 0;
    int iter = 0;

    do {
        iter++;
        len = (iter * size_read);
        bmemset(temp, '\0', size_read + 1);
        ret = read(fd, temp, size_read);
        buffer->file = bstrncat_forced(create_str(buffer->file,
            buffer->len, len), temp, buffer->len, len);
        buffer->len += ret;
        if (!buffer->file)
            return NULL;
    } while (ret == size_read);
    return buffer;
}

file_t *bread_file_len(char *path, size_t size_read)
{
    char *temp = malloc(sizeof(char) * (size_read + 1));
    file_t *buffer = create_file(size_read + 1, 0);
    int fd = open(path, O_RDONLY);

    if (fd == -1 || !temp || !buffer)
        return NULL;
    buffer = bloop_read(fd, temp, buffer, size_read);
    free(temp);
    close(fd);
    return buffer;
}
