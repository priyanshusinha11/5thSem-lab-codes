#include <stdio.h>

void solution(int arr_3[], int n_3)
{
    int maxi_3 = arr_3[0];
    for (int i_3 = 0; i_3 < n_3; i_3++)
    {
        maxi_3 = maxi_3 > arr_3[i_3] ? maxi_3 : arr_3[i_3];
    }
    int hash_3[maxi_3 + 1];
    for (int i_3 = 0; i_3 <= maxi_3; i_3++)
    {
        hash_3[i_3] = 0;
    }
    for (int i_3 = 0; i_3 < n_3; i_3++)
    {
        hash_3[arr_3[i_3]]++;
    }
    int count_3 = 0;
    for (int i_3 = 0; i_3 <= maxi_3; i_3++)
    {
        if (hash_3[i_3] > 1)
            count_3++;
    }
    int maxi2_3 = hash_3[0];
    int maxel_3 = 0;
    for (int i_3 = 0; i_3 <= maxi_3; i_3++)
    {
        if (hash_3[i_3] > maxi2_3)
        {
            maxi2_3 = hash_3[i_3];
            maxel_3 = i_3;
        }
    }
    printf("Number of duplicate elements: %d\n", count_3);
    printf("Most repeated element = %d", maxel_3);
}

int main()
{
    printf("Priyanshu Kumar Sinha: 21051673\n");
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
    solution(arr_3, n_3);
    return 0;
}
