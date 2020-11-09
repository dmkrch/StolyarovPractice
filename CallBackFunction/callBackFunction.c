#include <stdio.h>

int ActionsWithTwoNumbers(int a, int b, int (*callback)(int, int))
{
    return callback(a,b);
}

int callback_int_sum(int a, int b)
{
    return a+b;
}

int callback_int_mul(int a, int b)
{
    return a*b;
}

int callback_int_div(int a, int b)
{
    return a/b;
}

int main()
{
    printf("%d\n", ActionsWithTwoNumbers(5,7,callback_int_sum));
    printf("%d\n", ActionsWithTwoNumbers(10,7,callback_int_mul));
    printf("%d\n", ActionsWithTwoNumbers(25,5, callback_int_div));

    return 0;
}
