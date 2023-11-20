#include <stdio.h>

void prefixSum(int arr_3[], int n_3)
{
    int psum_3[n_3];
    psum_3[0] = arr_3[0];
    for (int i_3 = 1; i_3 < n_3; i_3++)
    {
        psum_3[i_3] = psum_3[i_3 - 1] + arr_3[i_3];
    }
    printf("Prefix sum array: \n");
    for (int i_3 = 0; i_3 < n_3; i_3++)
    {
        printf("%d ", psum_3[i_3]);
    }
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
    prefixSum(arr_3, n_3);
    return 0;
}