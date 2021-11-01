#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>


pthread_mutex_t mergeLock = PTHREAD_MUTEX_INITIALIZER; //lock
pthread_cond_t subarray_sort = PTHREAD_COND_INITIALIZER; //cond variable
//bool arraySorted = 0; //state variable
int numOfThreads = 4;
int arraySize = 20;
int subsection = 0;
std::vector<int> threadsDone = {0,0,0,0};
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
        //std::cout << arr[k] << " ";
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

//function that distributes threads/manages threads
void *sort_threads(void* arg) { 
    int threadNum = subsection;
    int subsectionSize = arraySize/numOfThreads;
    subsection++;
    int firstI = threadNum  * subsectionSize;
    int lastI = (threadNum + 1) * subsectionSize - 1;
    int midI = (firstI+lastI)/2;

    if(firstI<lastI) { //making sure subarray isnt too small
        int mid = (firstI+lastI)/2;
        mergesort(firstI,mid);
        mergesort(mid+1,lastI);
        merge(firstI,mid,lastI);
    } 
    return NULL;
}

/*
void *merge_thread(void* arg) {
    std::vector<int> temp(arraySize);

}
*/
//generates input,displays output,maybe measure performance in some way
int main() {
    //std::vector<int> original_array;
    //std::vector<int> sorted_array;

    
	//arr = std::vector<int>(arraySize);
    /*
	std::cout << "Enter Elements of Vector : ";
	for (int i = 0; i < arraySize; i++) {
		std::cin >> arr[i];
	}
    */
    
    arr = {5,8,2,6,8,9,3,6,8,9,2,1,1,4,4,3,1,8,2,9};

    std::cout << "Vector before sorting:\n";
	for (int i = 0; i < arraySize; i++) {
		std::cout << arr[i]<<" ";
	}
    std::cout << std::endl;
    
    pthread_t tid[numOfThreads]; //ids of sorting threads
    for(long i=0;i<numOfThreads;i++) { //creation of sorting threads
        pthread_create(&tid[i],NULL,sort_threads,NULL);
    }

    for(long i=0;i<numOfThreads;i++) { //joining sorting threads to make sure they complete
        pthread_join(tid[i], NULL);
    }
    
    pthread_t tid_merge; //merging thread
    //pthread_create(&tid_merge,NULL,merge_thread)


	std::cout << "\nVector Obtained After Sorting\n";
	for (int i = 0; i < arraySize; i++) 
    {
		std::cout << arr[i] << ' ';
	}
    //hello
    return 0;
}