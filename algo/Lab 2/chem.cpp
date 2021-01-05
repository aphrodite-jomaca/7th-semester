#include <stdio.h> //for any question dont hasitate to bother me. (i am bored to write comments)

int aux (int** minArray, int** minArrayIndex, int** powerDiff, int N, int i, int j, int L, int R) {
    int min = powerDiff[0][N-1];

    if (j == 0){
        return minArray[i][j] = powerDiff[j][i];
    }

    if (minArray[i][j] != -1) return minArray[i][j];

    for (int t = (L > 0 && L != -1? L : 0); t < (R < i && R != -1 ? R : i) ; t++) {
        int temp = aux(minArray, minArrayIndex, powerDiff, N, t, j - 1, L, R) + powerDiff[t+1][i];
        if (temp < min) {
            min = temp;
            minArrayIndex[i][j] = t;
        }
    }
    return minArray[i][j] = min;
}

int aux2(int L, int R, int bot, int top, int j, int** minArray, int** minArrayIndex, int** powerdiff, int N) {
    if (L >= R) {
        aux(minArray, minArrayIndex, powerdiff, N, L, j, bot - 1, top + 1);
    } else {
        int mid = (L + R) / 2;
        aux(minArray, minArrayIndex, powerdiff, N, mid, j, bot - 1, top + 1);
        aux2(L, mid - 1, bot, minArrayIndex[mid][j], j, minArray, minArrayIndex, powerdiff, N);
        aux2(mid + 1, R, minArrayIndex[mid][j], top, j, minArray, minArrayIndex, powerdiff, N);
    }
    return 42;
}

int solve(int** A, int** powerDiff, int N, int K) {
    int** minArray;
    int** minArrayIndex;

    minArray = new int*[N];
    minArrayIndex = new int*[N];

    for (int i = 0; i < N; i++){
        minArray[i] = new int[N];
        minArrayIndex[i] = new int[N];
        for (int j = 0; j < N; j++) {
            minArrayIndex[i][j] = minArray[i][j] = -1;
        }
    }

    for (int i = 0; i < K; i++) {
        aux2(0, N-1, 0, N-1, i, minArray, minArrayIndex, powerDiff, N);
    }


    return minArray[N-1][K-1];
}

int main () {
    int N, K;
    scanf("%d %d", &N, &K);
    int** A;
    int** sums;
    int** powerDiff;

    A = new int*[N];
    sums = new int*[N];
    powerDiff = new int*[N];

    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
        sums[i] = new int[N];
        powerDiff[i] = new int[N];       
    }

    int tempSum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j <= i) {
                A[i][j] = 0;
            } else {
                scanf("%d", &A[i][j]);
            }
            tempSum += A[i][j];
            sums[i][j] = tempSum;
        }
        tempSum = 0;
    }

    tempSum = 0;
    for (int i = 0; i < N; i++) {   
        for (int j = 0 ; j < N; j++) {
            tempSum += sums[N - j -1][i];
            powerDiff[N - j - 1][i] = tempSum;
        }
        tempSum = 0;
    }

    printf("%d\n", solve(A, powerDiff, N, K));
}