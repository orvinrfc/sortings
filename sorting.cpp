/*
*@author Orvin Tritama
*This program gives the analysis of different kind of sorts (Selection , Quick and Merge Sort)
*/
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

//Function Prototypes
void createArray(int A[], int size);
void selectionSort(int A[], int n);
void selectionSort(int A[], int size,int start);
int partition (int A[], int low, int high);
void quickSort(int A[], int low, int high);
void quickSort(int A[], int n);
void mergeSort(int A[],int low, int high, int W[]);
void merge(int A[], int astart, int aend, int bstart, int bend, int W[]);
void mergeSort(int A[],int W[], int n);
void countTime(int A[],int W[], int n);


int main(){
   srand(time(0));
   const int size = 32000; //Declaring constant integer size for array 32000
   int A[size]; //Declaring new array of size 32000
   int W[size]; //Declaring new array for working space of merge sort of size 32000
   
   countTime(A,W,1000); //Calling function countTime to count the clock ticks for all the types of sorts.
   
   return 0;
}

/*This function is to create array filled with random integers
*@param integer array
*@param integer size
*returns nothing
*/
void createArray(int A[], int size){
   for(int i=0;i<size;i++){
      A[i] = rand();
   }
}

/*This function as a helper function for selection sort
*@param integer array
*@param integer size
*@param int start as a helper (0)
*returns nothing
*/
void selectionSort(int A[], int size,int start){
   if(start > size){
      return;
   }else if(start!=size){
      int minPos = start;
      for(int i =0;i<size;i++){
         if(A[i] > A[minPos]){
            int temp = A[i];
            A[i] = A[minPos];
            A[minPos] = temp;
         }
      }
      selectionSort(A,size,start+1);
   }
}

/*This function is to do selection sort
*@param integer array
*@param integer n as size of the array
*returns nothing
*/
void selectionSort(int A[], int n){
   return selectionSort(A,n,0);
}

/*This function is to divide the size of array for quicksort
*@param integer array
*@param integer low (0)
*@param integer high (size of array)
*returns integer value of the smallest array size after dividing
*/
int partition (int A[], int low, int high){
   int pivot = A[high];
   int i = (low - 1);
   for (int j = low; j <= high- 1; j++){
      if (A[j] <= pivot){
         i++;
         swap(A[i], A[j]);
      }
   }
   swap(A[i + 1], A[high]);
   return (i + 1);
}

/*This function as a helper for quicksort
*@param integer array
*@param integer low (0)
*@param integer high (size of array)
*returns nothing
*/
void quickSort(int A[], int low, int high){
   if (low < high){
      int mid = partition(A, low, high);
      quickSort(A, low, mid - 1);
      quickSort(A, mid + 1, high);
   }
}

/*This function is to do quicksort
*@param integer array
*@param integer n (size of array)
*/
void quickSort(int A[], int n){
   return quickSort(A,0,n-1);
}

/*This function as a helper for merge sort
*@param integer array
*@param integer low (0)
*@param integer high (size of array)
*@param integer array W as working space to do merge
*returns nothing
*/
void mergeSort(int A[],int low, int high, int W[]){
   if(low==high){
      return;
   }else{
      int mid = (high+low) / 2;
      mergeSort(A,low,mid,W);
      mergeSort(A,mid+1, high,W);
      merge(A,low,mid,mid+1,high,W);
   }
}
/*This function is to merge the sorted array into a new array
*@param integer array
*@param integer astart (start of the first array)
*@param integer aend (end of the first array)
*@param integer bstart (start of the second array)
*@param integer bend (end of the second array)
*@param integer array W as a working space to merge the sorted array A
*returns nothing
*/
void merge(int A[], int astart, int aend, int bstart, int bend, int W[]){
   int i = astart;
   int j = bstart;
   int k = astart;
   while(i <= aend && j <= bend){
      if(A[i] < A[j]){
         W[k++] = A[i++];
      }else if(A[i] > A[j]){
         W[k++] = A[j++];
      }else if(A[i] == A[j]){
         W[k++] = A[j++];
         W[k++] = A[i++];
      }
   }
   while(i <= aend){
      W[k++] = A[i++];
   }
   while(j <= bend){
      W[k++] = A[j++];
   }
   for(int i = astart; i <= bend;i++){
      A[i] = W[i];
   }
}
 
/*This function to do the merge sort
*@param integer array
*@param integer array W (working space)
*@param integer n (size of array)
*returns nothing
*/
void mergeSort(int A[],int W[], int n){
   return mergeSort(A,0,n,W);
}

/*This function is to print off the time taken to do all the sorts m time for different sizes of array (1000,2000,4000,8000,16000,32000)
*@param integer array A
*@param integer array W
*@param integer size 
*returns nothing
*/
void countTime(int A[],int W[], int size){
   while(size <= 32000){
      double time = 0; //Set time to 0
      
      for(int i = 0; i < 100 ; i++){
         createArray(A,size);
         long start = clock();
         selectionSort(A,size);
         long stop = clock();
         time += (stop-start);
      }
      cout << size << "\t" <<  time / 100.0 << "\t";
      cout << size << "\t" << (time/ 100.0 ) / (pow(size,2)) << "\t";
      
      time = 0; //Reset time to 0
      
      for(int i = 0; i < 1000 ;i++){
         createArray(A,size);
         long start = clock();
         quickSort(A,size);
         long stop = clock();
         time += (stop-start);
      }
      cout << size << "\t" << (time/ 1000.0 ) << "\t";
      cout << size << "\t" << (time/ 1000.0) / (size*log2(size)) << "\t";
      
      time = 0; //Reset time to 0
   
      for(int i = 0; i < 1000 ;i++){
         createArray(A,size);
         long start = clock();
         mergeSort(A,W,size);
         long stop = clock();
         time += (stop-start);
      }
      cout << size << "\t" << (time/ 1000.0 ) << "\t";
      cout << size << "\t" << (time/ 1000.0 ) / (size*log2(size));
      
      cout << endl;
      
      size=size*2; //Multiply the size of array by 2 starting from 1000 to 32000
   }
}
      
   
   
   

