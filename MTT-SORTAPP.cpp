#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
 //<WIP> Everything subject to change including functions

//Function: Merge,MergeSort,Semaphore or Mutex, Main, Thread Creation?
// Start out with 4 threads and just reuse like in a thread pool?
//Things to consider: thread pool, global array, synchronization

//struct for shared data between threads?

//Each thread recursively performs mergesort on the portion of the array
//they are responsible for

//split up array into as many threads used, what to do with offset?

//race conditions/mutex should be in merge probably

/*
pthread_mutex_t mergeLock = PTHREAD_MUTEX_INITIALIZER; //lock
pthread_cond_t subarray_sort = PTHREAD_COND_INITIALIZER; //cond variable
bool arraySorted = 0; //state variable
const int THREAD_POOL_SIZE = 4;
*/

//merge the different subarrays handled by threads
void merge() {

}

//actual mergesort algorithm
void mergesort() {

}

//prevents race conditions using mutex or semaphore locks
void lock() { //can rename

}

//function that creates threads/manages threads
void threadcreation() { //rename later

}

//generates input,displays output,maybe measure performance in some way
int main() {

    return 0;
}