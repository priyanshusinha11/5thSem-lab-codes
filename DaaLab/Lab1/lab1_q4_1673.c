#include <stdio.h>

void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *p1, int p2, int p)
{
    if (p2 <= 0)
    {
        printf("Invalid value of p2. It should be greater than 0.\n");
        return;
    }

    for (int j = 0; j < p; j++)
    {
        int temp = *(p1 + p2 - 1);

        for (int i = p2 - 1; i > 0; i--)
        {
            *(p1 + i) = *(p1 + i - 1);
        }

        *p1 = temp;
    }
}

int main()
{
    int n_3;
    FILE *fp;
    fp = fopen("./lab1data.dat", "r");
    if (fp == NULL)
    {
        printf("File not found!");
        return 1;
    }
    fscanf(fp, "%d", &n_3);
    int arr_3[n_3];
    for (int i_3 = 0; i_3 < n_3; i_3++)
    {
        fscanf(fp, "%d", &arr_3[i_3]);
    }
    fclose(fp);

    int p;
    printf("Enter p: ");
    scanf("%d", &p);
    ROTATE_RIGHT(arr_3, n_3, p);

    printf("Rotated Array: ");
    for (int i = 0; i < n_3; i++)
    {
        printf("%d ", arr_3[i]);
    }

    return 0;
}
