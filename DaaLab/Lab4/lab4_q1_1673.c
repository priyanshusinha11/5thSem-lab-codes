#include <stdio.h>
int count = 0;
void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        count++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void displayFileContent(char *filename)
{
    FILE *file = fopen(filename, "r");

    int num;
    printf("Content of the file %s:\n", filename);
    while (fscanf(file, "%d", &num) == 1)
    {
        printf("%d ", num);
    }
    printf("\n");

    fclose(file);
}

int main()
{
    int choice;

    printf("\nMAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. EXIT\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        displayFileContent("inAsc.dat");
        {
            FILE *ip = fopen("inAsc.dat", "r");
            int n;
            fscanf(ip, "%d", &n);
            int arr[n];
            for (int i = 0; i < n; i++)
            {
                fscanf(ip, "%d", &arr[i]);
            }

            fclose(ip);

            mergeSort(arr, 0, n - 1);

            FILE *op = fopen("outAsc.dat", "w");
            for (int i = 0; i < n; i++)
            {
                fprintf(op, "%d ", arr[i]);
            }

            fclose(op);

            printf("After Sorting: Content of the output file\n");
            displayFileContent("outAsc.dat");
            printf("Number of comparisons = %d\n", count);
        }
        break;

    case 2:
        displayFileContent("inDesc.dat");

        {
            FILE *ip = fopen("inDesc.dat", "r");

            int n;
            fscanf(ip, "%d", &n);
            int arr[n];
            for (int i = 0; i < n; i++)
            {
                fscanf(ip, "%d", &arr[i]);
            }

            fclose(ip);

            mergeSort(arr, 0, n - 1);

            FILE *op = fopen("outDesc.dat", "w");

            for (int i = 0; i < n; i++)
            {
                fprintf(op, "%d ", arr[i]);
            }

            fclose(op);

            printf("After Sorting: Content of the output file\n");
            displayFileContent("outDesc.dat");
            printf("Number of comparisons = %d\n", count);
        }
        break;

    case 3:
        displayFileContent("inRand.dat");

        {
            FILE *ip = fopen("inRand.dat", "r");

            int n;
            fscanf(ip, "%d", &n);
            int arr[n];
            for (int i = 0; i < n; i++)
            {
                fscanf(ip, "%d", &arr[i]);
            }

            fclose(ip);

            mergeSort(arr, 0, n - 1);

            FILE *op = fopen("outRand.dat", "w");

            for (int i = 0; i < n; i++)
            {
                fprintf(op, "%d ", arr[i]);
            }

            fclose(op);

            printf("After Sorting: Content of the output file\n");
            displayFileContent("outRand.dat");
            printf("Number of comparisons = %d\n", count);
        }
        break;

    case 4:
        printf("Exiting...\n");
        break;

    default:
        printf("Invalid choice\n");
    }

    return 0;
}
