#include <stdio.h>

int main()
{
    printf("AMITA\n");
    int a = 0x800000fe;
    int b = 0x800000fb;
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%x + %x = %x\n", a, b, a + b);
    printf("%x\n", (long) -2147483394 + -2147483397);
    return 'M';
}
