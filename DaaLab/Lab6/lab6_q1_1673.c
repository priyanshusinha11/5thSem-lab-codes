#include <stdio.h>
#include <stdlib.h>

struct Item
{
    int value;
    int weight;
};

typedef struct Item Item;

int compare(const void *a, const void *b)
{
    double r1 = (double)(((Item *)b)->value) / (double)(((Item *)b)->weight);
    double r2 = (double)(((Item *)a)->value) / (double)(((Item *)a)->weight);
    if (r1 > r2)
        return 1;
    else if (r1 < r2)
        return -1;
    else
        return 0;
}

double maximumValue(int items[][2], int n, int w)
{
    Item arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i].value = items[i][1];
        arr[i].weight = items[i][0];
    }

    qsort(arr, n, sizeof(Item), compare);

    int wt = 0;
    double ans = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (wt + arr[i].weight <= w)
        {
            wt += arr[i].weight;
            ans += arr[i].value;
        }
        else
        {
            int remain = w - wt;
            ans += (arr[i].value / (double)arr[i].weight) * (double)remain;
            break;
        }
    }

    return ans;
}

int main()
{
    int items[][2] = {{2, 40}, {3, 50}, {5, 60}};
    int n = 3;
    int w = 7;

    double result = maximumValue(items, n, w);

    printf("Maximum value obtained: %.2lf\n", result);

    return 0;
}
