#include <stdio.h>
#include <stdlib.h>

void sort(float arr1[], int arr2[], int arr3[], int n)
{
    int maxind;
    for (int i = 0; i < n - 1; i++)
    {
        maxind = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr1[j] > arr1[maxind])
            {
                maxind = j;
            }
        }
        float temp = arr1[maxind];
        arr1[maxind] = arr1[i];
        arr1[i] = temp;
        int temp2 = arr2[maxind];
        arr2[maxind] = arr2[i];
        arr2[i] = temp2;
        int temp3 = arr3[maxind];
        arr3[maxind] = arr3[i];
        arr3[i] = temp3;
    }
}

void main()
{
    int cap, item;
    float total_profit = 0;
    printf("Enter the capacity of the Knapack:");
    scanf("%d", &cap);
    printf("Enter the number of items:");
    scanf("%d", &item);
    int wt[item], profit[item];
    printf("Enter the profit and weight of the items:\n");
    for (int i = 0; i < item; i++)
    {
        scanf("%d %d", &profit[i], &wt[i]);
    }
    float PW[item];
    for (int i = 0; i < item; i++)
    {
        PW[i] = (float)profit[i] / wt[i];
    }
  
    sort(PW, wt, profit, item);
    printf("Profit\tWeight\tPW\n");
    for (int i = 0; i < item; i++)
    {
        printf("%d\t%d\t%f\n", profit[i], wt[i], PW[i]);
    }
    printf("Fraction of items taken\n");
    for (int i = 0; i < item; i++)
    {
        if (wt[i] <= cap)
        {
            cap = cap - wt[i];
            total_profit = total_profit + profit[i];
            printf("%f ", 1.0);
        }
        else
        {
            total_profit = total_profit + cap * PW[i];
            printf("%f ", (float)cap / wt[i]);
            cap = 0;
        }
    }
    printf("\nTotal Profit: %f.\n", total_profit);
}