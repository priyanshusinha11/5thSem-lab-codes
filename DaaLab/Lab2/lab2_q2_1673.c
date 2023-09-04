#include <stdio.h>

int gcd(int a_3, int b_3)
{
    if (b_3 == 0)
        return a_3;
    return gcd(b_3, a_3 % b_3);
}

int main(int argc, char *argv[])
{
    FILE *ip, *op;
    ip = fopen(argv[1], "r");
    op = fopen(argv[2], "w");
    int a_3, b_3;
    while (fscanf(ip, "%d %d", &a_3, &b_3) == 2)
    {
        int ans_3 = gcd(a_3, b_3);
        fprintf(op, "The GCD of %d and %d is %d\n", a_3, b_3, ans_3);
    }
    fclose(ip);
    fclose(op);
    return 0;
}
