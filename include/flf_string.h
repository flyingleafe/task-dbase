#ifndef FLF_STRING_H
#define FLF_STRING_H
#include <stdint.h>

#pragma pack(push, 1)
struct string {
    uint32_t len;
    const char *buf;
};
#pragma pack(pop)

typedef struct string string;

char str_equal(const string *str, const char *b, uint32_t len);

#endif
