#include <stdio.h>
#include <stdlib.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void read_data(struct person *students, int n)
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d %s %d %d %d", &students[i].id, students[i].name, &students[i].age,
               &students[i].height, &students[i].weight);
    }

    fclose(fp);
}

void min_heapify(struct person *students, int i, int n)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && students[left].age < students[smallest].age)
    {
        smallest = left;
    }

    if (right < n && students[right].age < students[smallest].age)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        struct person temp = students[i];
        students[i] = students[smallest];
        students[smallest] = temp;

        min_heapify(students, smallest, n);
    }
}

void build_min_heap(struct person *students, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        min_heapify(students, i, n);
    }
}

void max_heapify(struct person *students, int i, int n)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && students[left].weight > students[largest].weight)
    {
        largest = left;
    }

    if (right < n && students[right].weight > students[largest].weight)
    {
        largest = right;
    }

    if (largest != i)
    {
        struct person temp = students[i];
        students[i] = students[largest];
        students[largest] = temp;

        max_heapify(students, largest, n);
    }
}

void build_max_heap(struct person *students, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        max_heapify(students, i, n);
    }
}

int get_min_element(struct person *students, int n)
{
    return students[0].weight;
}

int get_max_element(struct person *students, int n)
{
    return students[0].weight;
}

void insert_element(struct person *students, int n, struct person new_student)
{
    students[n] = new_student;

    int i = n;
    while (i > 0 && students[i].age < students[(i - 1) / 2].age)
    {
        struct person temp = students[i];
        students[i] = students[(i - 1) / 2];
        students[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

void delete_element(struct person *students, int n)
{
    students[0] = students[n - 1];
    n--;

    min_heapify(students, 0, n);
}

int main()
{
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct person *students = malloc(n * sizeof(struct person));
    read_data(students, n);
