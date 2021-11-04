#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <time.h>

int numOfThreads;
int arraySize;
int subsection = 0;

std::vector<std::pair<int,int>> subarrayIndice; //first and last indice of each subarray
std::vector<int> arr;
std::vector<int> result;

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

    if(arraySize % numOfThreads != 0) {
        if(threadNum == numOfThreads - 1) {
            lastI = arraySize - 1;
            midI = (firstI+lastI)/2;
        } 
    }

    if(firstI<lastI) { //making sure subarray isnt too small
        int mid = (firstI+lastI)/2;
        mergesort(firstI,mid);
        mergesort(mid+1,lastI);
        merge(firstI,mid,lastI);
    } 
    std::pair<int,int> location = {firstI,lastI};
    //std::cout << std::endl << "firstI: " << firstI <<  " lastI: " << lastI << std::endl;
    subarrayIndice.push_back(location);

    return NULL;
}


void *merge_thread(void* arg) {
   int firstI = 0;
   int lastI;
   int midI;
   
   for (int i = 0; i < numOfThreads-1; i++) { //loops ot join 
       if (i == numOfThreads) {
           lastI = subarrayIndice[i].second;
       } else {
           lastI = subarrayIndice[i+1].second;
       }
       midI = subarrayIndice[i+1].first - 1;
       //std::cout << std::endl << "firstI: " << firstI << " midI: " << midI << " lastI: " << lastI << std::endl;
       merge(firstI,midI,lastI); 
       
   }
    return NULL;
}

//generates input,displays output,maybe measure performance in some way
int main() {
    int lowerLimit = 0;
    int upperLimit = 11;
    int n = 57;
    srand(100);
    for (int i = 0; i < n; i++) { //generates n random integers from 0 to 10 and inserts into array
        arr.push_back(lowerLimit + (upperLimit - lowerLimit) * ((double)rand() / RAND_MAX));
        
    }
    clock_t t1, t2;
    
    numOfThreads = 4;
    t1 = clock();
    //double startTime = omp_get_wtime();
    //arr = {5,8,2,6,8,9,3,6,8,9,2,-1,1,4,4,3,1,8,2,9,5,1};
    arraySize = arr.size();
    std::cout << std::endl << arraySize << std::endl;

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
  
    
    // merging the threads
    pthread_t tid_merge; //merging thread
    pthread_create(&tid_merge,NULL,merge_thread,NULL);
    pthread_join(tid_merge,NULL);

    t2 = clock();
     
	std::cout << "\nVector Obtained After Sorting\n";
	for (int i = 0; i < arraySize; i++) 
    {
		std::cout << arr[i] << ' ';
	}
    std::cout<<std::endl;
    double secsElapsed = (t2 - t1)/(double)CLOCKS_PER_SEC;
    std::cout<<secsElapsed<<std::endl;
    return 0;
}