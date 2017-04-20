#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>

#define MAX_SIZE 110000


void generate_list(int * x, int n) {
	int i, j, t;
	for (i = 0; i < n; i++) 
		x[i] = i;
	for (i = 0; i < n; i++) { 
		j = rand() % n;       
		t = x[i];             
		x[i] = x[j];
		x[j] = t;
	}
}
void print_list(int * x, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");
}

void bubbleSort(int numbers[], int n)
{
  int i, j, temp;

  for (i = (n - 1); i >= 0; i--)
  {
    for (j = 1; j <= i; j++)
    {
      if (numbers[j-1] > numbers[j])
      {
        temp = numbers[j-1];
        numbers[j-1] = numbers[j];
        numbers[j] = temp;
      }
    }
  }
}
void bubbleSortp(int numbers[], int n){
	int tmp;
	for (int k = 0; k < n-2; ++k)
	{	
	#pragma omp parallel private(tmp) num_threads(10)
    	{
		if(k%2==0){
			#pragma omp for
			for (int i = 0; i < (n/2); ++i)
			{
				if(numbers[2*i]>numbers[(2*i)+1]){
					tmp= numbers[2*i];
					numbers[2*i]  = numbers[(2*i)+1];
					numbers[(2*i)+1] = tmp;
				}
			}
		}
		else{
			#pragma omp for
			for (int i = 0; i < (n/2)-1; ++i)
			{
				if(numbers[(2*i)+1]>numbers[(2*i)+2]){
				tmp = numbers[2*i+1];
				numbers[(2*i)+1]  = numbers[(2*i)+2];
				numbers[(2*i)+2] = tmp;
				}
			}
		}
	  }
	}
}

int main()
{
	int n = 100000;
	double start, stop1, stop2, stop3, d1, d2, r;
	int data[MAX_SIZE], tmp[MAX_SIZE], data_s[MAX_SIZE];

	for (n; n > 7; n / 10)
	{
		printf( "n: %d \n", n);
		generate_list(data, n);
		for (int i = 0; i < n; i++)
		{
			data_s[i] = data[i];
		}
		if (n < 101)
		{
			printf("List Before Sorting...\n");
			print_list(data, n);
		}		
		start = omp_get_wtime();
		bubbleSortp(data, n);
		stop1 = omp_get_wtime();
		if (n < 101)
		{
			printf("\nList After Sorting by using parallel code...\n");
			print_list(data, n);
		}
		d1 = stop1 - start;
		printf("\nSorting by using parallel code Time: %2.8f", d1);

		stop2 = omp_get_wtime();
		bubbleSort(data_s, n);
		stop3 = omp_get_wtime();
		d2 = stop3 - stop2;
		printf("\nSorting by using serial code Time: %2.8f\n", d2);
		
		r = d2 / d1;
		printf("\n Speedup factor: %2.8f\n\n\n", r);

		n = n / 10;
	}
	system("pause");
}
