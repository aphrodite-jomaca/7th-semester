#include <stdio.h>
#include <vector>
#include <tuple>
#include <string.h> 
using namespace std;

//objX:(quantity,price),(),(),....
struct merchant
{
    vector<tuple<int, int> > objA;
    vector<tuple<int, int> > objB;
    vector<tuple<int, int> > objC;
};

vector<int> A, B, C, R1, R2, R3;

void knapsack(vector<tuple<int, int> > MO, vector<int> &O, int N)
{
    int count = 0, tmp = 0, k;
    
    for(int i=0; i<MO.size(); i++)
        count += get<0>(MO[i]);
    O.resize(min(count, N)+1); 
    O[0] = 0;
    for(int i=1; i<O.size(); i++)
        O[i]=__INT_MAX__;
    for(int i=0; i<MO.size(); i++)
    {
        int s = get<0>(MO[i]);
        int p = get<1>(MO[i]);
        tmp += s;
        for(int j=min(tmp, N); j>=1; j--)
        {
            k = max(j-s, 0);
            O[j] = min(O[j], O[k]+p);
        }

    }
}

void merge(vector<int> &T, vector<int> A, vector<int> B, vector<int> C)
{
    T.resize(min(min(A.size(), B.size()), C.size()));
    for(int i=0; i<(T.size()); i++) T[i] = A[i] + B[i] + C[i];
}

int main()
{
    int N, M;
    merchant merchant1, merchant2, merchant3;
    int res = __INT_MAX__;

    scanf("%d %d", &N, &M);

    char m, o;
    int q, p;
    for (int i = 0; i < M; i++)
    {
        getchar();
        m = getchar();
        o = getchar();
        scanf("%d %d", &q, &p);
        if (m == '1')
        {
            switch (o)
            {
            case 'A':
                merchant1.objA.push_back(make_tuple(q, p));
                break;
            case 'B':
                merchant1.objB.push_back(make_tuple(q, p));
                break;
            case 'C':
                merchant1.objC.push_back(make_tuple(q, p));
                break;
            default:
                printf("WTF\n");
                return 42;
            }
        }
        else if (m == '2')
        {
            switch (o)
            {
            case 'A':
                merchant2.objA.push_back(make_tuple(q, p));
                break;
            case 'B':
                merchant2.objB.push_back(make_tuple(q, p));
                break;
            case 'C':
                merchant2.objC.push_back(make_tuple(q, p));
                break;
            default:
                printf("WTF\n");
                return 42;
            }
        }
        else
        {
            switch (o)
            {
            case 'A':
                merchant3.objA.push_back(make_tuple(q, p));
                break;
            case 'B':
                merchant3.objB.push_back(make_tuple(q, p));
                break;
            case 'C':
                merchant3.objC.push_back(make_tuple(q, p));
                break;
            default:
                printf("WTF\n");
                return 42;
            }
        }
    }

    knapsack(merchant1.objA, A, N);
    knapsack(merchant1.objB, B, N);
    knapsack(merchant1.objC, C, N);
    merge(R1, A, B, C);

    knapsack(merchant2.objA, A, N);
    knapsack(merchant2.objB, B, N);
    knapsack(merchant2.objC, C, N);
    merge(R2, A, B, C);

    knapsack(merchant3.objA, A, N);
    knapsack(merchant3.objB, B, N);
    knapsack(merchant3.objC, C, N);
    merge(R3, A, B, C);

    if (R1.size() + R2.size() + R3.size() - 3 < N) 
    {
        printf("-1\n");
        return 0;
    }

    for(int i=0; i <= min(N, (int)R1.size()-1); i++)
        for(int j=0; j <= min(N-i, (int)R2.size()-1); j++)
            if(i + j + R3.size()-1 >= N)
                res = min(res, R1[i] + R2[j] + R3[N-i-j]);

    printf("%d\n", res);
    return 0;
}