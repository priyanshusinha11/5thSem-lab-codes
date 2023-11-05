#include <stdio.h>

void printOptimalParenthesis(int s[][100], int i, int j)
{
    if (i == j)
        printf("A%d", i);
    else
    {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int p[], int n, int m[][100], int s[][100])
{
    int i, j, k, l, q;
    for (i = 1; i <= n; i++)
        m[i][i] = 0;
    for (l = 2; l <= n; l++)
    {
        for (i = 1; i <= n - l + 1; i++)
        {
            j = i + l - 1;
            m[i][j] = 99999999;
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    int p[n + 1];
    int m[100][100], s[100][100];

    for (int i = 1; i <= n; i++)
    {
        printf("Enter row and column size of A%d: ", i);
        scanf("%d %d", &p[i - 1], &p[i]);
    }

    matrixChainOrder(p, n, m, s);

    printf("M Table:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i <= j)
                printf("%d ", m[i][j]);
            else
                printf("0 ");
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i < j)
                printf("%d ", s[i][j]);
            else
                printf("0 ");
        }
        printf("\n");
    }

    printf("Optimal parenthesization: ");
    printOptimalParenthesis(s, 1, n);
    printf("\n");

    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);
    return 0;
}
