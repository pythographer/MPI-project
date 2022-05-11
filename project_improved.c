#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct average{
    double time;
    double sum;
    int count;

} bubble, selection, insertion, Merge, heap, radix;

void randomize(int arr[],int size,int *seed);

void swap(int *x, int *y);
void copyArr(int input[], int output[], int size);

double BubbleSort(int input[], int output[], int size);

double SelectionSort(int input[], int output[], int size);

double InsertionSort(int input[], int output[], int size);

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);


void heapify(int output[], int size, int i);
double heapSort(int input[], int output[], int size);


int getMax(int arr[], int n);

void radixSort(int a[], int n);


int main(){

    printf("\n#Please note: the data set can be repeated if the same input is provided.\n");
    int size, seed = 1, tests;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    srand(seed);
    int arr[size], sortedArr[size];
    for(int i = 0; i < size; i++){
        arr[i] = rand() % size;
    }

    printf("\nThe data set is a randomized array of the form:\n\n");

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    printf(".......");    
    printf("\n\nHow many test would you like to run?\nA: ");
    scanf("%d", &tests);
    printf("\n\n###################################################################\n");
    for(int k = 1; k <= tests; k++){
        randomize(arr, size, &seed);
    
        BubbleSort(arr, sortedArr, size);
        SelectionSort(arr, sortedArr, size);
        InsertionSort(arr, sortedArr, size);
    
        copyArr(arr, sortedArr, size);
        double time_spent_merge = 0.0;
        clock_t begin = clock();
        mergeSort(sortedArr, 0, size - 1);
        clock_t end = clock();
        time_spent_merge = (double) (end - begin) / CLOCKS_PER_SEC;
        Merge.time = time_spent_merge;
        Merge.sum += Merge.time;
        Merge.count += 1;    
    
        heapSort(arr, sortedArr, size);

        copyArr(arr, sortedArr, size);
        double time_spent_radix = 0.0;
        begin = clock();
        radixSort(sortedArr, size);
        end = clock();
        time_spent_radix = (double) (end - begin) / CLOCKS_PER_SEC;
        radix.time = time_spent_radix;
        radix.sum += radix.time;
        radix.count += 1;    
        
    
    }
    printf("\nBubble sort executed in %.6f.\n" ,bubble.sum / bubble.count);
    printf("\nSelection sort executed in %.6f.\n" ,selection.sum / selection.count);
    printf("\nInsertion sort executed in %.6f.\n" ,insertion.sum / insertion.count);
    printf("\nMerge sort executed in %.6f.\n" ,Merge.sum / Merge.count);
    printf("\nHeap sort executed in %.6f.\n" ,heap.sum / heap.count);
    printf("\nRadix sort executed in %.6f.\n" ,radix.sum / radix.count);
    printf("\n###################################################################\n");

    return 0;
}

void randomize(int arr[],int size,int *seed){
    srand(*seed);
    for(int i = 0; i < size; i++){
        arr[i] = rand() % size;
    }
    *seed += 1;
}

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;

}

void copyArr(int input[], int output[], int size){
    for (int k = 0; k < size; k++) {
        output[k] = input[k];
    }
}


double BubbleSort(int input[], int output[], int size){
    double time_spent = 0.0;
    clock_t begin = clock();
    for (int k = 0; k < size; k ++) {
        output[k] = input[k];
    }
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size -i -1; j ++) {
            if (output[j] > output[j + 1]) {
                swap(&output[j], &output[j + 1]);
            }
        }
    }

    clock_t end = clock();
    time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
    
    bubble.time = time_spent;
    bubble.sum += bubble.time;
    bubble.count += 1;
    
    return time_spent;
}


double SelectionSort(int input[], int output[], int size){

    
    for (int k = 0; k < size; k ++) {
        output[k] = input[k];
    }
    double time_spent = 0.0;
    clock_t begin = clock();
    int min, i, j;
    for (i = 0; i < size - 1; i++) {
        min = i;
        for (j = i + 1; j < size; j++) {
            if (output[j] < output[min]) {
                min = j;
            }
        }
        swap(&output[min], &output[i]);
    }
    clock_t end = clock();
    time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
    
    selection.time = time_spent;
    selection.sum += selection.time;
    selection.count += 1;
    
    return time_spent;
    

}


double InsertionSort(int input[], int output[], int size){

    for (int k = 0; k < size; k ++) {
        output[k] = input[k];
    }
    double time_spent = 0.0;
    clock_t begin = clock();
    int key, j;
    for (int i = 0; i < size; i++) {
        key = output[i];
        j = i - 1; 
        while (j >= 0 && output[j] > key) {
            output[j + 1] = output[j];
            j -= 1;
        }
        output[j + 1] = key;
    }

    clock_t end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    
    insertion.time = time_spent;
    insertion.sum += insertion.time;
    insertion.count += 1;
    
    return time_spent;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    
    int L[n1], R[n2];
  
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {

        int m = l + (r - l) / 2;
  

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}


void heapify(int output[], int size, int i)
{
    
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
 
    
    if (l < size && output[l] > output[largest])
        largest = l;
 
    
    if (r < size && output[r] > output[largest])
        largest = r;
 
    
    if (largest != i) {
        swap(&output[i], &output[largest]);
 
        
        heapify(output, size, largest);
    }
}
 

double heapSort(int input[], int output[], int size)
{
    for (int k = 0; k < size; k ++) {
        output[k] = input[k];
    }
    double time_spent = 0.0;
    clock_t begin = clock();
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(output, size, i);
 
    
    for (int i = size - 1; i > 0; i--) {
        
        swap(&output[0], &output[i]);
 
        
        heapify(output, i, 0);
    }
    clock_t end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    
    heap.time = time_spent;
    heap.sum += heap.time;
    heap.count += 1;
    
    return time_spent;
}


int getMax(int arr[], int n) {

    int mx = arr[0];
    int i;

    for (i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];

    return mx;

}

void radixSort (int arr[], int n){
   int bucket[1000][1000], bucket_cnt[1000];
   int i, j, k, r, NOP = 0, divisor = 1, lar, pass;
   lar = getMax(arr, n);
   while (lar > 0){
      NOP++;
      lar /= 10;
   }
   for (pass = 0; pass < NOP; pass++){
      for (i = 0; i < 10; i++){
         bucket_cnt[i] = 0;
      }
      for (i = 0; i < n; i++){
         r = (arr[i] / divisor) % 10;
         bucket[r][bucket_cnt[r]] = arr[i];
         bucket_cnt[r] += 1;
      }
      i = 0;
      for (k = 0; k < 10; k++){
         for (j = 0; j < bucket_cnt[k]; j++){
            arr[i] = bucket[k][j];
            i++;
         }
      }
      divisor *= 10;      
   }
}

