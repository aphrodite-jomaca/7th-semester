#include <stdio.h>
#include <cstdlib>
using namespace std;

struct car
{
    int rental;
    int capacity;
}c;

int ccompare(const void * a, const void * b)
{
    const struct car* c1 = (const struct car*)a;
    const struct car* c2 = (const struct car*)b;
    return(c1->capacity - c2->capacity);
}

int dcompare(const void * a, const void * b)
{
    return (*(int*)a - *(int*) b);
}

bool check_car(car c, int T, int dist[], int K, int Cf, int Cs, int Tf, int Ts)
{
    int total_time = 0;
    double d_sport, d_eco;
    for(int i=0; i<K+1; i++)
    {
        d_sport = (c.capacity - Cs*dist[i])/(Cf - Cs);
        d_eco = dist[i] - d_sport;
        if(d_sport > dist[i])          //dist can be done driving only sport?
        {
            d_sport = dist[i];
        }
        if((d_sport*Cf + d_eco*Cs > c.capacity) or d_sport < 0)
        {
            return false;
        }
        if((total_time += d_eco*Ts + d_sport*Tf) > T)
        {
            return false;
        }  
    }
    return (total_time <= T);
    
}

int binary_search(int left, int right, int index, car carray[], int T, int dist[], int K, int Cf, int Cs, int Tf, int Ts) {
	if (left >= right)
		return index;
	else {
		int mid = (left + right) / 2;
        //printf("mid=%d\n",mid);
		if (check_car(carray[mid], T, dist, K, Cf, Cs, Tf, Ts)) 
        {
			return binary_search(left, mid - 1, mid, carray, T, dist, K, Cf, Cs, Tf, Ts);
		}
		else 
        {
			return binary_search(mid + 1, right, index, carray, T, dist, K, Cf, Cs, Tf, Ts);
		}

	}
}

int main()
{
//-------------INPUT READING--------------
    int N, K, D, T, Ts, Cs, Tf, Cf;

    scanf("%d %d %d %d", &N, &K, &D, &T);

    car *carray = new car[N];

    for (int i=0; i<N; i++)
        scanf("%d %d", &carray[i].rental, &carray[i].capacity);
    

    int d[K];
    for (int i=0; i<K; i++)
        scanf("%d", &d[i]);

    scanf("%d %d %d %d", &Ts, &Cs, &Tf, &Cf);

//----------COMPUTE THE DISTANCES BETWEEN TWO STATIONS--------
    int dist[K+1];
    qsort(d, K, sizeof(int), dcompare);
  /*  for (int i=0; i<K; i++)
    {
        printf("%d, ", d[i]);
    }
    printf("\n");
*/
    dist[0] = D - d[K-1];
    dist[K] = d[0];
    for(int i=1; i < K; i++)
    {
        dist[i] = abs(d[i-1] - d[i]);
    }
   /* for(int i=0; i < K+1; i++)
    {
        printf("%d,",dist[i]);
    }
    printf("\n");
*/
//-------------SORTING--------------
    qsort(carray,N,sizeof(car),ccompare);

//--------------SOLVE----------------
    int party_car = binary_search(0, N, -1, carray, T, dist, K, Cf, Cs, Tf, Ts);
    if (party_car == -1) printf("-1\n");
    else
    {
        int min = carray[party_car].rental;
		for (int i = party_car; i < N; i++)
		{
			if (carray[i].rental < min) min = carray[i].rental;
		}
		printf("%d\n",min);
    }

    return 0;
}
