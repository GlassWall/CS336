#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"

#define MAX_SIZE 1000000


void generate_list(int * x, int n) {
   int i,j,t;
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
      printf("%d ",x[i]);
   }
}
void qs(int *v, int first, int last) {
  int start[2], end[2], pivot, i, temp;

  if (first < last) {
     start[1] = first;
     end[0] = last;
     pivot = v[(first + last) / 2];
     while (start[1] <= end[0]) {
       while (v[start[1]] < pivot)
         start[1]++;
       while (pivot < v[end[0]])
         end[0]--;
       if (start[1] <= end[0]) {
         temp = v[start[1]];
         v[start[1]] = v[end[0]];
         v[end[0]] = temp;
         start[1]++;
         end[0]--;
       }
     }
     start[0] = first; 
     end[1]   = last; 

#pragma omp parallel 
{
#pragma omp for nowait
     for(i = 0; i <= 1; i++) {
       qs(v, start[i], end[i]);
     }
}
     
   }
}


int main()
{
   int n = 100000;


   int data[MAX_SIZE], tmp[MAX_SIZE];

   generate_list(data, n);
   printf("List Before Sorting...\n");
   print_list(data, n);

    //mergesort(data, n, tmp);
    qs(data, 0, n);

   printf("\nList After Sorting...\n");
   print_list(data, n);
   //printf("\nTime: %g\n",stop-start);
}