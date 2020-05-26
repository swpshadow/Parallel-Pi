#include <stdio.h>
#include"mpi.h"
#include <stdlib.h>
#include<time.h>

int main(int argc, char **argv){
  clock_t start;
  clock_t end;
  int rank;
  int comm_sz;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  long long number_of_tosses = 0;
  long long total_in_circle = 0;
  long long total_number_of_tosses = 100000000000;
  if (rank == 0){
    number_of_tosses = 100000000000;
    number_of_tosses /= comm_sz;
  }
  start = clock();
  MPI_Bcast(&number_of_tosses, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
  if (rank == 0){
    number_of_tosses += 100000000000 % comm_sz; //this ensures we have exactly 1e11 tosses
  }
  long long number_in_circle = 0;
  double x = 0, y = 0;
  long long toss = 0;
  double distance_squared = 0;
  srand(rank + 256);
  for(toss = 0; toss < number_of_tosses; toss++){
    x = (double)rand()/RAND_MAX * 2.0 - 1;
    y = (double)rand()/RAND_MAX * 2.0 - 1;
    distance_squared = x * x + y * y;
    if (distance_squared <= 1){
      number_in_circle += 1;
    }
  }

  MPI_Reduce(&number_in_circle, &total_in_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Finalize();
  if (rank==0){
    printf("%d %s\n", rank, "is done" );
    end = clock();
    printf("%lld\n", total_in_circle );
    printf("%lld\n", number_of_tosses );
    double pi_estimate = 4 * total_in_circle/((double) total_number_of_tosses);
    printf("%lf\n", pi_estimate);
    printf("total clock ticks for core %d: %ld\n",rank, end - start );
    printf("%lf\n",(double)(end-start)/CLOCKS_PER_SEC);
  }

}
