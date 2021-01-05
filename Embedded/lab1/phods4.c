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

/*MACROS for the 2 loops that will be urolled*/
#define S_FORLOOP(s)\
    min1 = 255*B*B;\
    min2 = 255*B*B;\
    I_FORLOOP(-s);\
    I_FORLOOP(0);\
    I_FORLOOP(s);\
    v_x += bestx;\
    v_y += besty;

#define I_FORLOOP(i)\
    distx = 0;\
    disty = 0;\
    for(k=0; k<B; k++)\
    {\
        for(l=0; l<B; l++)\
        {\
            p1 = current[Bx+k][By+l];\
/*initially for x dimension*/ \
            if((Bx + v_x + i + k) < 0 ||\
            (Bx + v_x + i + k) > (N-1) ||\
            (By + v_y + l) < 0 ||\
            (By + v_y + l) > (M-1))\
            {\
                p2 = 0;\
            } else {\
                p2 = previous[Bx+v_x+i+k][By+v_y+l];\
            }\
/*initially for y dimension*/\
            if((Bx + v_x + k) <0 ||\
            (Bx + v_x + k) > (N-1) ||\
            (By + v_y + i + l) < 0 ||\
            (By + v_y + i + l) > (M-1))\
            {\
                q2 = 0;\
            } else {\
                q2 = previous[Bx+v_x+k][By+v_y+i+l];\
            }\
            distx += abs(p1-p2);\
            disty += abs(p1-q2);\
        }\
    }\
/*initially for x dimension*/ \
    if(distx < min1)\
    {\
        min1 = distx;\
        bestx = i;\
    }\
/*initially for y dimension*/ \
    if(disty < min2)\
    {\
        min2 = disty;\
        besty = i;\
    }                             


void read_sequence(int current[N][M], int previous[N][M], int B)
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

void phods_motion_estimation(int B, int current[N][M], int previous[N][M],
    int vectors_x[N/B][M/B],int vectors_y[N/B][M/B])
{
  int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;

  distx = 0;
  disty = 0;

  /*Initialize the vector motion matrices*/
  for(i=0; i<N/B; i++)
  {
    for(j=0; j<M/B; j++)
    {
      vectors_x[i][j] = 0;
      vectors_y[i][j] = 0;
    }
  }

  /*For all blocks in the current frame*/
  for(x=0; x<N/B; x++)
  {
    for(y=0; y<M/B; y++)
    {
      /*Get the value and store it to a variable so to exploit data reuse and reduce array accesses*/
        int Bx = B*x;
        int By = B*y;
        int v_x = vectors_x[x][y];
        int v_y = vectors_y[x][y];
        S_FORLOOP(4);
        S_FORLOOP(2);
        S_FORLOOP(1);
    }
  }
} 

int main(int argc, char *argv[])
{ 
  int B;
  sscanf(argv[1], "%d", &B);
  struct timeval start_time, end_time;
  int current[N][M], previous[N][M], motion_vectors_x[N/B][M/B],
      motion_vectors_y[N/B][M/B], i, j;

	read_sequence(current,previous,B);
  gettimeofday(&start_time, NULL);
  phods_motion_estimation(B,current,previous,motion_vectors_x,motion_vectors_y);
  gettimeofday(&end_time, NULL);
  printf("%ld ", (end_time.tv_sec - start_time.tv_sec)*1000000 + end_time.tv_usec - start_time.tv_usec);
  return 0;
}
