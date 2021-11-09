#include <stdio.h>

int main()
{
    printf("AMITA\n");

    int a = 0x800000fe;
    int b = 0x800000fb;
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%x + %x = %x\n", a, b, a + b);
    printf("%lx\n", (long) -2147483394 + -2147483397);

    char c = 'A';
    char *str = "RinHizakura";
    printf("This is %c \n", c);
    printf("This is %s \n", str);
    return 0;
}
