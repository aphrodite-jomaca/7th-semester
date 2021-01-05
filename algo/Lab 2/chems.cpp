#include <stdio.h>
#include <list>
#include <cstdlib>
using namespace std;

int aux(int **minArray, int **powerDiff, int N, int K, int i, int j)
{
    int min = powerDiff[0][N - 1];

    if (j == 0)
    {
        return minArray[i][j] = powerDiff[j][i];
    }

    if (minArray[i][j] != -1)
        return minArray[i][j];

    for (int t = 0; t < i; t++)
    {
        int temp = aux(minArray, powerDiff, N, K, t, j - 1) + powerDiff[t + 1][i];
        if (temp < min)
        {
            min = temp;
        }
    }
    return minArray[i][j]=min;
}

//minArray[n][k]

int main()
{
    //-------------INPUT READING--------------
    int N, K, tmp;

    scanf("%d %d", &N, &K);

    int A[N][N], sums[N][N], **energyFromTo, **minArray;
    energyFromTo = new int *[N];
    minArray = new int *[N];

    for (int i = 0; i < N; i++)
    {
        energyFromTo[i] = new int[N];
        minArray[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j <= i)
                A[i][j] = 0;
            else
                scanf("%d", &A[i][j]);
            tmp += A[i][j];
            sums[i][j] = tmp;
            minArray[i][j] = -1;
        }
        tmp = 0;
    }

    tmp = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tmp += sums[N - j - 1][i];
            energyFromTo[N - j - 1][i] = tmp;
        }
        tmp = 0;
    }

    printf("%d\n", aux(minArray, energyFromTo, N, K, N - 1, K - 1));

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", A[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", sums[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", energyFromTo[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", minArray[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}