#include <stdio.h>

int main() {

    int count[256] = {0};

    char str[] = "I am a student!";
    for (int i = 0; str[i] != '\0'; i++)
        count[str[i]]++;

    for (int i = 0; i < 256; i++)
    {
        if (count[i] > 0)
            printf("字符 %c 出现了 %d 次\n", i, count[i]);
    }

    return 0;
}