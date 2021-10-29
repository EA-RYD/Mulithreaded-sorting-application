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

std::vector<int> original_array;
std::vector<int> sorted_array;

//merge the different subarrays handled by threads
void merge(std::vector<int> &arr,int firstI,int mid,int lastI) {

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
void mergesort(std::vector<int> &arr,int firstI,int lastI) {
    if(firstI<lastI) { //making sure subarray isnt too small
        int mid = (firstI+lastI)/2;
        mergesort(arr,firstI,mid);
        mergesort(arr,mid+1,lastI);
        merge(arr,firstI,mid,lastI);
    } 

}

/*
//prevents race conditions using mutex or semaphore locks
void lock() { //can rename

}
*/

//function that distributes threads/manages threads
/*void *manage_threads(void* arg) { 

}*/

//generates input,displays output,maybe measure performance in some way
int main() {

    //std::vector<int> original_array;
    //std::vector<int> sorted_array;

	int n;
	std::vector<int> arr;

	std::cout << "Enter Size of Vector : ";
	std::cin >> n;

	arr = std::vector<int>(n);
	std::cout << "Enter Elements of Vector : ";
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

    std::cout << "Vector before sorting: ";
	for (int i = 0; i < n; i++) {
		std::cout << arr[i]<<" ";
	}
	mergesort(arr, 0, n - 1);

	std::cout << "\nVector Obtained After Sorting: ";
	for (int i = 0; i < n; i++) 
    {
		std::cout << arr[i] << ' ';
	}
    return 0;
}