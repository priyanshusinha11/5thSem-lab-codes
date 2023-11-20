#include <stdio.h>
#include <limits.h>
int secondLargest(int arr_3[], int n_3)
{
    if (n_3 < 2)
        return -1;
    int large_3 = INT_MIN, slarge_3 = INT_MIN;
    int i_3;
    for (i_3 = 0; i_3 < n_3; i_3++)
    {
        if (arr_3[i_3] > large_3)
        {
            slarge_3 = large_3;
            large_3 = arr_3[i_3];
        }

        else if (arr_3[i_3] > slarge_3 && arr_3[i_3] != large_3)
        {
            slarge_3 = arr_3[i_3];
        }
    }
    return slarge_3;
}
int secondSmallest(int arr_3[], int n_3)
{
    if (n_3 < 2)
        return -1;
    int small_3 = INT_MAX;
    int ssmall_3 = INT_MAX;
    int i_3;
    for (i_3 = 0; i_3 < n_3; i_3++)
    {
        if (arr_3[i_3] < small_3)
        {
            ssmall_3 = small_3;
            small_3 = arr_3[i_3];
        }
        else if (arr_3[i_3] < ssmall_3 && arr_3[i_3] != small_3)
        {
            ssmall_3 = arr_3[i_3];
        }
    }
    return ssmall_3;
}
int main()
{
    printf("Priyanshu Kumar Sinha: 21051673\n");
    int n_3;
    FILE *fp;
    fp = fopen("./lab1data.dat", "r");
    fscanf(fp, "%d", &n_3);
    int arr_3[n_3];
    for (int i_3 = 0; i_3 < n_3; i_3++)
    {
        fscanf(fp, "%d", &arr_3[i_3]);
    }
    int slarge_3 = secondLargest(arr_3, n_3);
    int ssmall_3 = secondSmallest(arr_3, n_3);
    printf("Second largest = %d\n", slarge_3);
    printf("Second smallest = %d\n", ssmall_3);
    return 0;
}