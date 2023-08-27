#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int compare(const void *a, const void *b);

int readStudentRollNumbers(const char *filename, int rollNumbers[]);

void sortIntArray(int arr[], int size);

int mergeAndCountSelected(int p1[], int p2[], int p3[], int p4[], int n1, int n2, int n3, int n4);

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int readStudentRollNumbers(const char *filename, int rollNumbers[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int n;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &rollNumbers[i]);
    }

    fclose(fp);
    return n;
}

void sortIntArray(int arr[], int size)
{
    qsort(arr, size, sizeof(int), compare);
}

int mergeAndCountSelected(int p1[], int p2[], int p3[], int p4[], int n1, int n2, int n3, int n4)
{
    int count = 0;
    int i = 0, j = 0, k = 0, l = 0;

    while (i < n1 && j < n2 && k < n3 && l < n4)
    {
        if (p1[i] == p2[j] && p2[j] == p3[k] && p3[k] == p4[l])
        {
            count++;
            i++;
            j++;
            k++;
            l++;
        }
        else if (p1[i] <= p2[j] && p1[i] <= p3[k] && p1[i] <= p4[l])
            i++;
        else if (p2[j] <= p1[i] && p2[j] <= p3[k] && p2[j] <= p4[l])
            j++;
        else if (p3[k] <= p1[i] && p3[k] <= p2[j] && p3[k] <= p4[l])
            k++;
        else
            l++;
    }

    return count;
}

int main()
{
    int p1[MAX], p2[MAX], p3[MAX], p4[MAX];
    int n1, n2, n3, n4;

    n1 = readStudentRollNumbers("panel1.txt", p1);
    n2 = readStudentRollNumbers("panel2.txt", p2);
    n3 = readStudentRollNumbers("panel3.txt", p3);
    n4 = readStudentRollNumbers("panel4.txt", p4);

    sortIntArray(p1, n1);
    sortIntArray(p2, n2);
    sortIntArray(p3, n3);
    sortIntArray(p4, n4);

    int count = mergeAndCountSelected(p1, p2, p3, p4, n1, n2, n3, n4);

    printf("Number of students selected: %d\n", count);

    return 0;
}