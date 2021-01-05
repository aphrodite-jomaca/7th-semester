/*Parallel Hierarchical One-Dimensional Search for motion estimation*/
/*Initial algorithm - Used for simulation and profiling             */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 144     /*Frame dimension for QCIF format*/
#define M 176     /*Frame dimension for QCIF format*/
//#define B 16      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/
int Bx, By;

#define I_FORLOOP(i)\
    distx = 0;\
    disty = 0;\
    for(k=0; k<Bx; k++)\
    {\
        for(l=0; l<By; l++)                                                      \
        {                                                                       \
            p1 = current[Bxx+k][Byy+l];                                         \
            if((Bxx + v_x + i + k) < 0 ||                                       \
            (Bxx + v_x + i + k) > (N-1) ||                                      \
            (Byy + v_y + l) < 0 ||                                              \
            (Byy + v_y + l) > (M-1))                                \
            {                                                                   \
                p2 = 0;                                                         \
            } else {                                                            \
                p2 = previous[Bxx+v_x+i+k][Byy+v_y+l];  \
            }                                                                   \
            if((Bxx + v_x + k) <0 ||                                \
            (Bxx + v_x + k) > (N-1) ||                              \
            (Byy + v_y + i + l) < 0 ||                              \
            (Byy + v_y + i + l) > (M-1))                            \
            {                                                                   \
                q2 = 0;                                                         \
            } else {                                                            \
                q2 = previous[Bxx+v_x+k][Byy+v_y+i+l];  \
            }                                                                   \
            distx += abs(p1-p2);                                                \
            disty += abs(p1-q2);                                                \
        }                                                                       \
    }                                                                           \
    if(distx < min1)                                                            \
    {                                                                           \
        min1 = distx;                                                           \
        bestx = i;                                                              \
    }                                                                           \
    if(disty < min2)                                                            \
    {                                                                           \
        min2 = disty;                                                           \
        besty = i;                                                              \
    }                             

#define S_FORLOOP(s)                                                           \
    min1 = 255*Bx*By;                                                             \
    min2 = 255*Bx*By;                                                             \
    I_FORLOOP(-s);                                                             \
    I_FORLOOP(0);                                                              \
    I_FORLOOP(s);                                                              \
    v_x += bestx;                                                   \
    v_y += besty;



void read_sequence(int current[N][M], int previous[N][M])
{ 
	FILE *picture0, *picture1;
	int i, j;

	if((picture0=fopen("akiyo0.y","rb")) == NULL)
	{
		printf("Previous frame doesn't exist.\n");
		exit(-1);
	}

	if((picture1=fopen("akiyo1.y","rb")) == NULL) 
	{
		printf("Current frame doesn't exist.\n");
		exit(-1);
	}

  /*Input for the previous frame*/
  for(i=0; i<N; i++)
  {
    for(j=0; j<M; j++)
    {
      previous[i][j] = fgetc(picture0);
    }
  }

	/*Input for the current frame*/
	for(i=0; i<N; i++)
  {
		for(j=0; j<M; j++)
    {
			current[i][j] = fgetc(picture1);
    }
  }

	fclose(picture0);
	fclose(picture1);
}

void phods_motion_estimation(int current[N][M], int previous[N][M],
    int vectors_x[N/Bx][M/By],int vectors_y[N/Bx][M/By])
{
  int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;

  distx = 0;
  disty = 0;

  /*Initialize the vector motion matrices*/
  for(i=0; i<N/Bx; i++)
  {
    for(j=0; j<M/By; j++)
    {
      vectors_x[i][j] = 0;
      vectors_y[i][j] = 0;
    }
  }

  /*For all blocks in the current frame*/
  for(x=0; x<N/Bx; x++)
  {
    for(y=0; y<M/By; y++)
    {
        int Bxx = Bx*x;
        int Byy = By*y;
        int v_x = vectors_x[x][y];
        int v_y = vectors_y[x][y];
        S_FORLOOP(4);
        S_FORLOOP(2);
        S_FORLOOP(1);
    }
  }
} 

int main( int argc, char *argv[])
{ 
  
  sscanf(argv[1], "%d", &Bx);
  sscanf(argv[2], "%d", &By);

  struct timeval start_time, end_time;
  int current[N][M], previous[N][M], motion_vectors_x[N/Bx][M/By],
      motion_vectors_y[N/Bx][M/By], i, j;

	read_sequence(current,previous);
  gettimeofday(&start_time, NULL);
  phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);
  gettimeofday(&end_time, NULL);
  printf("%ld ", (end_time.tv_sec - start_time.tv_sec)*1000000 + end_time.tv_usec - start_time.tv_usec);
  return 0;
}