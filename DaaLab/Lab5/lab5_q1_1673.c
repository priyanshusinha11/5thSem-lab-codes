#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct person
struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

// Function to swap two person structures
void swap(struct person *x, struct person *y)
{
    struct person temp = *x;
    *x = *y;
    *y = temp;
}

// Function to maintain the min-heap property
void minHeapify(struct person *arr, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Function to build a min-heap
void buildMinHeap(struct person *arr, int n)
{
    int i;
    for (i = (n / 2) - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

// Function to display the struct person
void displayPerson(struct person p)
{
    printf("ID: %d\n", p.id);
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Height: %d\n", p.height);
    printf("Weight: %d\n", p.weight);
    printf("\n");
}

// Function to read data from a file and store it in a dynamically allocated array
struct person *readData(int *n)
{
    FILE *file = fopen("input.dat", "r");
    if (file == NULL)
    {
        printf("Error: Cannot open the file.\n");
        exit(1);
    }

    fscanf(file, "%d", n);
    struct person *arr = (struct person *)malloc(*n * sizeof(struct person));

    for (int i = 0; i < *n; i++)
    {
        arr[i].id = i + 1;
        arr[i].name = (char *)malloc(50 * sizeof(char));
        fscanf(file, "%s %d %d %d", arr[i].name, &arr[i].age, &arr[i].height, &arr[i].weight);
    }

    fclose(file);
    return arr;
}

int main()
{
    int choice, n;
    struct person *arr = NULL;

    while (1)
    {
        printf("MAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on age\n");
        printf("3. Create a Max-heap based on weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (arr != NULL)
            {
                free(arr);
                arr = NULL;
            }
            arr = readData(&n);
            printf("Data read successfully.\n");
            break;

        case 2:
            if (arr == NULL)
            {
                printf("Error: Data not read yet.\n");
                break;
            }
            buildMinHeap(arr, n);
            printf("Min-heap created based on age.\n");
            break;

        case 3:
            if (arr == NULL)
            {
                printf("Error: Data not read yet.\n");
                break;
            }
            // Create a Max-heap based on weight
            for (int i = n / 2 - 1; i >= 0; i--)
            {
                int largest = i;
                int left = 2 * i + 1;
                int right = 2 * i + 2;

                if (left < n && arr[left].weight > arr[largest].weight)
                    largest = left;

                if (right < n && arr[right].weight > arr[largest].weight)
                    largest = right;

                if (largest != i)
                {
                    swap(&arr[i], &arr[largest]);
                }
            }
            printf("Max-heap created based on weight.\n");
            break;

        case 4:
            if (arr == NULL)
            {
                printf("Error: Data not read yet.\n");
                break;
            }
            printf("Weight of the youngest person: %d\n", arr[0].weight);
            break;

        case 5:
            if (arr == NULL)
            {
                printf("Error: Data not read yet.\n");
                break;
            }
            n++;
            arr = realloc(arr, n * sizeof(struct person));
            if (arr == NULL)
            {
                printf("Memory allocation failed.\n");
                exit(1);
            }
            arr[n - 1].id = n;
            arr[n - 1].name = (char *)malloc(50 * sizeof(char));
            printf("Enter name: ");
            scanf("%s", arr[n - 1].name);
            printf("Enter age: ");
            scanf("%d", &arr[n - 1].age);
            printf("Enter height: ");
            scanf("%d", &arr[n - 1].height);
            printf("Enter weight: ");
            scanf("%d", &arr[n - 1].weight);
            // Rebuild the min-heap
            for (int i = (n / 2) - 1; i >= 0; i--)
            {
                minHeapify(arr, n, i);
            }
            printf("New person inserted into the Min-heap.\n");
            break;

        case 6:
            if (arr == NULL)
            {
                printf("Error: Data not read yet.\n");
                break;
            }
            if (n == 0)
            {
                printf("Heap is empty.\n");
                break;
            }
            // Delete the oldest person (root of the min-heap)
            free(arr[0].name);
            arr[0] = arr[n - 1];
            n--;
            arr = realloc(arr, n * sizeof(struct person));
            // Rebuild the min-heap
            for (int i = (n / 2) - 1; i >= 0; i--)
            {
                minHeapify(arr, n, i);
            }
            printf("Oldest person deleted from the Min-heap.\n");
            break;

        case 7:
            if (arr != NULL)
            {
                for (int i = 0; i < n; i++)
                {
                    free(arr[i].name);
                }
                free(arr);
            }
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
