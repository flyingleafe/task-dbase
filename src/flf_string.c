#include "flf_string.h"

char str_equal(const string *str, const char *b, uint32_t len) {
    if (str->len != len) {
        return 0;
    }
    const char *a = str->buf;
    while (len) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
        len--;
    }
    return 1;
}
