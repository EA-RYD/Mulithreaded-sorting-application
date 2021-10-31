#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
 //<WIP> Everything subject to change including functions
//Hello world
//Function: Merge,MergeSort,Semaphore or Mutex, Main, Thread Creation?
// Start out with 4 threads and just reuse like in a thread pool?
//Things to consider: thread pool, global array, synchronization

//struct for shared data between threads?

//Each thread recursively performs mergesort on the portion of the array
//they are responsible for

//split up array into as many threads used, what to do with offset?

//race conditions/mutex should be in merge probably
//need to wait until all subarrays are sorted to be able to merge them

//do we even need mutex?

//could just have 2 sorting threads like prompt suggests

/*
pthread_mutex_t mergeLock = PTHREAD_MUTEX_INITIALIZER; //lock
pthread_cond_t subarray_sort = PTHREAD_COND_INITIALIZER; //cond variable
bool arraySorted = 0; //state variable
const int THREAD_POOL_SIZE = 4;
*/
int arraySize = 20;
int numOfThreads = 4;
int subsection = 0;
std::vector<int> arr;

//merge the different subarrays handled by threads
void merge(int firstI,int mid,int lastI) {

    std::vector<int> temp;
    int n1, n2;//splitting array into left and right
    n1= firstI;
    n2= mid +1;

    while(n1<= mid && n2<= lastI)
    {
        if (arr[n1] <= arr[n2]) {
			temp.push_back(arr[n1]);
			n1++;
		}
		else {
			temp.push_back(arr[n2]);
			n2++;
		}

    }

    while (n1 <= mid) {
		temp.push_back(arr[n1]);
		n1++;
	}

	while (n2 <= lastI) {
		temp.push_back(arr[n2]);
		n2++;
	}

	for (int k = firstI; k <= lastI; k++)
    {
		arr[k] = temp[k - firstI];
    }

}

//actual mergesort algorithm
void mergesort(int firstI,int lastI) {
    if(firstI<lastI) { //making sure subarray isnt too small
        int mid = (firstI+lastI)/2;
        mergesort(firstI,mid);
        mergesort(mid+1,lastI);
        merge(firstI,mid,lastI);
    } 

}

/*
//prevents race conditions using mutex or semaphore locks
void lock() { //can rename

}
*/

//function that distributes threads/manages threads
void * merge_sort_threads(void* thread_id) { 
    int threadNum = subsection;
    int subsectionSize = arraySize/threadNum;
    subsection++;
    int firstI = threadNum  * subsectionSize;
    int lastI = (threadNum + 1 * subsectionSize) - 1;
    int midI = (firstI+lastI)/2;

    if(firstI<lastI) { //making sure subarray isnt too small
        int mid = (firstI+lastI)/2;
        mergesort(firstI,mid);
        mergesort(mid+1,lastI);
        merge(firstI,mid,lastI);
    } 

}

//generates input,displays output,maybe measure performance in some way
int main() {

    //std::vector<int> original_array;
    //std::vector<int> sorted_array;

    /*
	arr = std::vector<int>(arraySize);
	std::cout << "Enter Elements of Vector : ";
	for (int i = 0; i < arraySize; i++) {
		std::cin >> arr[i];
	}
    */
    arr = {5,8,2,6,8,9,3,6,8,9,2,1,1,4,4,3,1,8,2,9};

    std::cout << "Vector before sorting: ";
	for (int i = 0; i < arraySize; i++) {
		std::cout << arr[i]<<" ";
	}
	// mergesort(0, n - 1);

    pthread_t tid[numOfThreads];

    for(int i=0;i<numOfThreads;i++) {
        pthread_create(&tid[i],NULL,merge_sort_threads,(void *)&tid[i]);
    }

    for(int i=0;i<numOfThreads;i++) {
        pthread_join(tid[i],NULL);
    }




	std::cout << "\nVector Obtained After Sorting: ";
	for (int i = 0; i < arraySize; i++) 
    {
		std::cout << arr[i] << ' ';
	}
    return 0;
}