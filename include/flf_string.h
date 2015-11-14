#ifndef FLF_STRING_H
#define FLF_STRING_H
#include <stdint.h>

struct string {
    uint32_t len;
    const char *buf;
};
typedef struct string string;

char str_equal(const string *str, const char *b, uint32_t len);

#endif
