#include <stdio.h>
#include <list>
#include <cstdlib>
using namespace std;

struct portal
{
    int width;
    int edge[2];
};

struct subset {
    int parent;
    int rank;
};

int find(struct subset parents[], int x)
{
    if (parents[x].parent != x)
        parents[x].parent = find(parents, parents[x].parent);
 
    return parents[x].parent;
}

void Union(struct subset parents[], int xroot, int yroot)
{
    if (parents[xroot].rank < parents[yroot].rank)
        parents[xroot].parent = yroot;
    else if (parents[xroot].rank > parents[yroot].rank)
        parents[yroot].parent = xroot;
    else 
    {
        parents[yroot].parent = xroot;
        parents[xroot].rank++;
    }
}

int pcompare(const void * a, const void * b)
{
    const struct portal* p1 = (const struct portal*)a;
    const struct portal* p2 = (const struct portal*)b;
    return(p1->width - p2->width);
}

bool check_portal(portal portals[], int N, int M, int mid, std::list<int> lost, int c[])
{
    subset *parents = new subset[N+1];
    for (int i = 1; i < N+1; i++) 
    {
        parents[i].parent = i;
        parents[i].rank = 0;
    }

    for (int i = mid; i < M; i++) 
    {
            int x = find(parents, portals[i].edge[0]);
            int y = find(parents, portals[i].edge[1]);
            Union(parents, x, y);
    }
    for (std::list<int>::iterator i = lost.begin(); i != lost.end(); i++)
    {
        if (find(parents, *i) != find(parents, c[*i])) return false;
    }
    return true;    
}

int binary_search(int left, int right, int previous, portal portals[], int N, int M,std::list<int> lost, int c[]) 
{
	if (left <= right)  
    {
		int mid = (left + right) / 2;
		if (check_portal(portals, N, M, mid, lost, c)) 
        {
			return binary_search(mid+1, right, portals[mid].width, portals, N, M, lost, c);
		}
		else 
        {
			return binary_search(left, mid-1, previous, portals, N, M, lost, c);
		}

	}
    else
    {
        if(check_portal(portals,N,M,left,lost, c))   
            previous = portals[0].width; 
        return previous;
    }
}

int main()
{
//-------------INPUT READING--------------
    int N, M;

    scanf("%d %d", &N, &M);

    portal *portals = new portal[M];

    int c[N+1];
    std::list<int> lost;


    int j=0;
    for (int i=1; i<N+1; i++)
    {
        scanf("%d", &c[i]);
        if (c[i] != i)
        {
            lost.push_back(i);
        }
    } 


    for (int i=0; i<M; i++)
        scanf("%d %d %d", &portals[i].edge[0], &portals[i].edge[1], &portals[i].width);

//-------------SORTING--------------
    qsort(portals,M,sizeof(portal),pcompare);
//--------------SOLVE----------------
    int minmax = binary_search(0, M, -1, portals, N, M, lost, c);
    printf("%d\n",minmax);
    return 0;
}
