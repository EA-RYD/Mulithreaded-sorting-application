#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
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
void merge() {

}

//actual mergesort algorithm
void mergesort(std::vector<int> arr,int firstI,int lastI) {
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
void *manage_threads(void* arg) { 

}

//generates input,displays output,maybe measure performance in some way
int main() {

    return 0;
}