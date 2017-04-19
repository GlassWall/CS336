#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
void print_listd(double * x, int n) {
   int i;
   for (i = 0; i < n; i++) {
      printf("%f ",x[i]);
   }
}
void swap(int *arr, int i, int j)
{
	int tmp=arr[i];
	arr[i]=arr[j];
	arr[j]=tmp;
}
int pivoter(int *a, int p, int r)
{
	int pivot=a[p];
	int i=p-1;
	int j=r+1;
	while(1)
	{
		do{
			j--;
		}while((a[j]>pivot)&&(j>p)&&(j<=r));
		do{
			i++;
		}while((a[i]<pivot)&&(i<r)&&(i>=p));
		if(i<j)
			swap(a,i,j);
		else
			return j;
	}
}

void quickSort(int *array, int beg, int end) {


  if (beg < end) {
	int pivot1 = pivoter(array,beg,end);
#pragma omp task default(none) firstprivate(array, pivot1, beg, end)
		quickSort(array,beg,pivot1);
		quickSort(array,pivot1+1,end);
}
}
 void quick(int *arr, const int n)
	{
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                quickSort(arr, 0, n - 1);
            }
        }
    }
	void quickSortserial(int *array, int beg, int end) {


  if (beg < end) {
	int pivot1 = pivoter(array,beg,end);

		quickSort(array,beg,pivot1);
		quickSort(array,pivot1+1,end);
}
}
 void quickSerial(int *arr, const int n)
	{
        
                quickSort(arr, 0, n - 1);
         
    }


int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


int main()
{
   int n = 500000;
	//omp_set_num_threads(3);

   int data[MAX_SIZE], temp[MAX_SIZE], tmp[MAX_SIZE];
  
   generate_list(data, n);
	for(int i = 0;i<n;i++){
	temp[i]=data[i];
	}  

//reinitializing data array to temp values for rudimentary qsort
	
	clock_t begin1 = clock();
   qsort(data, n, sizeof(int), cmpfunc);
	clock_t end1 = clock();
double time_spent1 = (double)(end1-begin1)/CLOCKS_PER_SEC;
 //reinitializing data array to temp values for normal qsort
	for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
	clock_t begin2 = clock();
   quickSerial(data,n);
	clock_t end2 = clock();
double time_spent2 = (double)(end2-begin2)/CLOCKS_PER_SEC;
//parallel
for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
 printf("List before sorting...\n");
   print_list(data, n);
struct timeval start, end;
gettimeofday(&start, NULL);
    quick(data, n);
gettimeofday(&end, NULL);
double delta =1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
 

   printf("\nList after Sorting...\n");
   print_list(data, n);
   printf("\nInput TYPE=integer SIZE = %d\n",n );
  printf("\nRudimentary quick sort Elapsed: %f seconds \n", time_spent1);
  printf("Normal quick sort Elapsed: %f seconds \n", time_spent2);
  printf("Parallel quick sort Elapsed: %f seconds \n", delta/1000000);//we divide by 1000000 because delta is in microseconds

//n=100000 type = int
  n=100000;
  generate_list(data, n);
	for(int i = 0;i<n;i++){
	temp[i]=data[i];
	}  
	 begin1 = clock();
   qsort(data, n, sizeof(int), cmpfunc);
	 end1 = clock();
 time_spent1 = (double)(end1-begin1)/CLOCKS_PER_SEC;
 //reinitializing data array to temp values for normal qsort
	for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
	 begin2 = clock();
   quickSerial(data,n);
	 end2 = clock();
 time_spent2 = (double)(end2-begin2)/CLOCKS_PER_SEC;
//parallel
for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
 //printf("List before sorting...\n");
   //print_list(data, n);
//struct timeval start, end;
gettimeofday(&start, NULL);


    quick(data, n);

gettimeofday(&end, NULL);
 delta =1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
 

   
   printf("\nInput TYPE=integer SIZE = %d\n",n );
  printf("\nRudimentary quick sort Elapsed: %f seconds \n", time_spent1);
  printf("Normal quick sort Elapsed: %f seconds \n", time_spent2);
  printf("Parallel quick sort Elapsed: %f seconds \n", delta/1000000);

//n=10000 type = int
  n=10000;
  generate_list(data, n);
	for(int i = 0;i<n;i++){
	temp[i]=data[i];
	}  
	 begin1 = clock();
   qsort(data, n, sizeof(int), cmpfunc);
	 end1 = clock();
 time_spent1 = (double)(end1-begin1)/CLOCKS_PER_SEC;
 //reinitializing data array to temp values for normal qsort
	for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
	 begin2 = clock();
   quickSerial(data,n);
	 end2 = clock();
 time_spent2 = (double)(end2-begin2)/CLOCKS_PER_SEC;
//parallel
for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
 //printf("List before sorting...\n");
   //print_list(data, n);
//struct timeval start, end;
gettimeofday(&start, NULL);


    quick(data, n);

gettimeofday(&end, NULL);
 delta =1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
 

   
   printf("\nInput TYPE=integer SIZE = %d\n",n );
  printf("\nRudimentary quick sort Elapsed: %f seconds \n", time_spent1);
  printf("Normal quick sort Elapsed: %f seconds \n", time_spent2);
  printf("Parallel quick sort Elapsed: %f seconds \n", delta/1000000);


 //n=1000
    n=1000;
  generate_list(data, n);
	for(int i = 0;i<n;i++){
	temp[i]=data[i];
	}  
	 begin1 = clock();
   qsort(data, n, sizeof(int), cmpfunc);
	 end1 = clock();
 time_spent1 = (double)(end1-begin1)/CLOCKS_PER_SEC;
 //reinitializing data array to temp values for normal qsort
	for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
	 begin2 = clock();
   quickSerial(data,n);
	 end2 = clock();
 time_spent2 = (double)(end2-begin2)/CLOCKS_PER_SEC;
//parallel
for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
 //printf("List before sorting...\n");
   //print_list(data, n);
//struct timeval start, end;
gettimeofday(&start, NULL);


    quick(data, n);

gettimeofday(&end, NULL);
 delta =1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
 

   
   printf("\nInput TYPE=integer SIZE = %d\n",n );
  printf("\nRudimentary quick sort Elapsed: %f seconds \n", time_spent1);
  printf("Normal quick sort Elapsed: %f seconds \n", time_spent2);
  printf("Parallel quick sort Elapsed: %f seconds \n", delta/1000000);
//n=100
  n=100;
  generate_list(data, n);
	for(int i = 0;i<n;i++){
	temp[i]=data[i];
	}  
	 begin1 = clock();
   qsort(data, n, sizeof(int), cmpfunc);
	 end1 = clock();
 time_spent1 = (double)(end1-begin1)/CLOCKS_PER_SEC;
 //reinitializing data array to temp values for normal qsort
	for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
	 begin2 = clock();
   quickSerial(data,n);
	 end2 = clock();
 time_spent2 = (double)(end2-begin2)/CLOCKS_PER_SEC;
//parallel
for(int i = 0;i<n;i++){
	data[i]=temp[i];
	}  
 //printf("List before sorting...\n");
   //print_list(data, n);
//struct timeval start, end;
gettimeofday(&start, NULL);


    quick(data, n);

gettimeofday(&end, NULL);
 delta =1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
 

   
   printf("\nInput TYPE=integer SIZE = %d\n",n );
  printf("\nRudimentary quick sort Elapsed: %f seconds \n", time_spent1);
  printf("Normal quick sort Elapsed: %f seconds \n", time_spent2);
  printf("Parallel quick sort Elapsed: %f seconds \n", delta/1000000);


}
