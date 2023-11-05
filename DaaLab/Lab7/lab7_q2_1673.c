#include <stdio.h>
#include <string.h>

// Function to find the length of the Longest Common Subsequence (LCS)
int lcs(char *s2, char *s1, char *result)
{
    int n = strlen(s1);
    int m = strlen(s2);

    int dp[n + 1][m + 1]; // Create a DP table

    // Initialize the base cases
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= m; i++)
    {
        dp[0][i] = 0;
    }

    // Fill in the DP table to calculate the length of LCS
    for (int ind1 = 1; ind1 <= n; ind1++)
    {
        for (int ind2 = 1; ind2 <= m; ind2++)
        {
            if (s1[ind1 - 1] == s2[ind2 - 1])
                dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1]; // Characters match, increment LCS length
            else
                dp[ind1][ind2] = (dp[ind1 - 1][ind2] > dp[ind1][ind2 - 1]) ? dp[ind1 - 1][ind2] : dp[ind1][ind2 - 1]; // Characters don't match, consider the maximum from left or above
        }
    }

    // Backtrack to construct the LCS string
    int index = dp[n][m];
    result[index] = '\0'; // Null-terminate the result string
    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        // If current characters in s1 and s2 are same, then they are part of LCS
        if (s1[i - 1] == s2[j - 1])
        {
            result[index - 1] = s1[i - 1];
            i--;
            j--;
            index--;
        }
        // If not same, then find the larger of two and go in the direction of larger value
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    return dp[n][m]; // Return the length of the Longest Common Subsequence
}

int main()
{
    char s1[1000];
    char s2[1000];
    char result[1000];

    printf("Enter the first string into an array: ");
    scanf("%s", s1);

    printf("Enter the second string into an array: ");
    scanf("%s", s2);

    // Call the function to find and output the length of the Longest Common Subsequence
    int length = lcs(s1, s2, result);
    printf("LCS: %s\n", result);
    printf("LCS length: %d\n", length);

    return 0; // Return 0 to indicate successful program execution
}
