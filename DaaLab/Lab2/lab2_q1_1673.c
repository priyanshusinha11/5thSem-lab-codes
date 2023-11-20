#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int num_3, FILE *op)
{
    if (num_3 > 0)
    {
        decimalToBinary(num_3 / 2, op);
        fprintf(op, "%d", num_3 % 2);
    }
}
int main(int argc, char *argv[])
{
    printf("Priyanshu Kumar Sinha: 21051673\n");
    int n_3;
    FILE *ip, *op;
    sscanf(argv[1], "%d", &n_3);
    ip = fopen(argv[2], "r");
    op = fopen(argv[3], "w");
    int decNum_3;
    while (n_3-- > 0 && fscanf(ip, "%d", &decNum_3) == 1)
    {
        if (decNum_3 == 0)
        {
            fprintf(op, "0\n");
        }
        else
        {
            decimalToBinary(decNum_3, op);
            fprintf(op, "\n");
        }
    }
    fclose(ip);
    fclose(op);
    return 0;
}
