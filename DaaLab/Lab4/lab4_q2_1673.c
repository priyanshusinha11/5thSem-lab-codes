#include <stdio.h>

int count = 0;

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            count++;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    count++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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

    printf("\nMAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. EXIT\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        count = 0; // Reset count for each scenario
        displayFileContent("inAsc.dat");
        FILE *ip = fopen("inAsc.dat", "r");

        if (ip == NULL)
        {
            printf("Error opening file inAsc.dat\n");
            break;
        }

        int n;
        fscanf(ip, "%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            fscanf(ip, "%d", &arr[i]);
        }

        fclose(ip);

        quickSort(arr, 0, n - 1);

        FILE *op = fopen("outAsc.dat", "w");
        if (op == NULL)
        {
            printf("Error opening file outAsc.dat\n");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            fprintf(op, "%d ", arr[i]);
        }

        fclose(op);

        printf("After Sorting: Content of the output file\n");
        displayFileContent("outAsc.dat");
        printf("Number of comparisons = %d\n", count);
        break;
    }

    case 2:
    {
        count = 0; // Reset count for each scenario
        displayFileContent("inDesc.dat");
        FILE *ip = fopen("inDesc.dat", "r");

        if (ip == NULL)
        {
            printf("Error opening file inDesc.dat\n");
            break;
        }

        int n;
        fscanf(ip, "%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            fscanf(ip, "%d", &arr[i]);
        }

        fclose(ip);

        quickSort(arr, 0, n - 1);

        FILE *op = fopen("outDesc.dat", "w");
        if (op == NULL)
        {
            printf("Error opening file outDesc.dat\n");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            fprintf(op, "%d ", arr[i]);
        }

        fclose(op);

        printf("After Sorting: Content of the output file\n");
        displayFileContent("outDesc.dat");
        printf("Number of comparisons = %d\n", count);
        break;
    }

    case 3:
    {
        count = 0; // Reset count for each scenario
        displayFileContent("inRand.dat");
        FILE *ip = fopen("inRand.dat", "r");

        if (ip == NULL)
        {
            printf("Error opening file inRand.dat\n");
            break;
        }

        int n;
        fscanf(ip, "%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            fscanf(ip, "%d", &arr[i]);
        }

        fclose(ip);

        quickSort(arr, 0, n - 1);

        FILE *op = fopen("outRand.dat", "w");
        if (op == NULL)
        {
            printf("Error opening file outRand.dat\n");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            fprintf(op, "%d ", arr[i]);
        }

        fclose(op);

        printf("After Sorting: Content of the output file\n");
        displayFileContent("outRand.dat");
        printf("Number of comparisons = %d\n", count);
        break;
    }

    case 4:
        printf("Exiting...\n");
        break;

    default:
        printf("Invalid choice\n");
    }

    return 0;
}
