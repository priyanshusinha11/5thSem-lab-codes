#include <stdio.h>

void insertionSort(int arr[], int n)
{
    int j, i, k, comparisons = 0;
    for (i = 1; i < n; i++)
    {
        k = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > k)
        {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }
        arr[j + 1] = k;
    }

    printf("Number of Comparisons: %d\n", comparisons);
}

void displayFileContent(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

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

    printf("\nMAIN MENU (INSERTION SORT)\n");
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

            insertionSort(arr, n);

            FILE *op = fopen("outAsc.dat", "w");
            for (int i = 0; i < n; i++)
            {
                fprintf(op, "%d ", arr[i]);
            }

            fclose(op);

            printf("After Sorting: Content of the output file\n");
            displayFileContent("outAsc.dat");
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

            insertionSort(arr, n);

            FILE *op = fopen("outDesc.dat", "w");

            for (int i = 0; i < n; i++)
            {
                fprintf(op, "%d ", arr[i]);
            }

            fclose(op);

            printf("After Sorting: Content of the output file\n");
            displayFileContent("outDesc.dat");
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

            insertionSort(arr, n);

            FILE *op = fopen("outRand.dat", "w");

            for (int i = 0; i < n; i++)
            {
                fprintf(op, "%d ", arr[i]);
            }

            fclose(op);

            printf("After Sorting: Content of the output file\n");
            displayFileContent("outRand.dat");
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
