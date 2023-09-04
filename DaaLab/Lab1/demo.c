#include <stdio.h>

void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *p1, int p2)
{
    if (p2 <= 0)
    {
        printf("Invalid value of p2. It should be greater than 0.\n");
        return;
    }

    int temp = *(p1 + p2 - 1);

    for (int i = p2 - 1; i > 0; i--)
    {
        *(p1 + i) = *(p1 + i - 1);
    }

    *p1 = temp;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int p2 = 3;

    printf("Original Array: ");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }

    ROTATE_RIGHT(arr, p2);

    printf("\nRotated Array: ");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
