#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc < 4) {
        printf("Too few args\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int minw = atoi(argv[2]);
    int maxw = atoi(argv[3]);

    char *buf = malloc(maxw + 1);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int len = rand() % (maxw - minw) + minw;
        for (int j = 0; j < len; j++) {
            buf[j] = rand() % (127 - 32) + 32;
        }
        buf[len] = 0;
        printf("%s\n", buf);
    }
    free(buf);
    return 0;
}
