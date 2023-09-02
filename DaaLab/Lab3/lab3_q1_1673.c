#include <stdio.h>

int binarySearchLeftmost(int arr[], int size, int key, int *cnt)
{
    int left = 0;
    int right = size - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
        {
            result = mid;
            right = mid - 1;
        }
        else if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }

        (*cnt)++;
    }

    return result;
}

int main()
{
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    int key;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);

    int cnt = 0;
    int position = binarySearchLeftmost(arr, size, key, &cnt);

    if (position != -1)
    {
        printf("%d found at index position %d\n", key, position);
        printf("Number of comparisons: %d\n", cnt);
    }
    else
    {
        printf("%d not found in the array\n", key);
        printf("Number of comparisons: %d\n", cnt);
    }

    return 0;
}
