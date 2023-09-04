#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n;
    FILE *fp;
    printf("%s %s %s %s", argv[0], argv[1], argv[2], argv[3]);
    n = atoi(argv[1]);
    int a[n];
    printf("n = %d", n);
    fp = fopen(argv[2], "r");
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &a[i]);
        printf("\n[%d] = %d", i, a[i]);
    }
    return 0;
}
