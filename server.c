#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include "util.h"
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#define MAX_THREADS 100
#define MAX_queue_len 100
#define MAX_CE 100
#define INVALID -1
#define BUFF_SIZE 1024
#define PERMS 0666

/*
  THE CODE STRUCTURE GIVEN BELOW IS JUST A SUGGESTION. FEEL FREE TO MODIFY AS NEEDED
*/

// structs:
typedef struct request_queue {
   int fd;
   char *request;
} request_t;

typedef struct cache_entry {
    int len;
    char *request;
    char *content;
} cache_entry_t;

/* ******************** Dynamic Pool Code  [Extra Credit A] **********************/
// Extra Credit: This function implements the policy to change the worker thread pool dynamically
// depending on the number of requests
void * dynamic_pool_size_update(void *arg) {
  while(1) {
    // Run at regular intervals
    // Increase / decrease dynamically based on your policy
  }
}
/**********************************************************************************/

/* ************************ Cache Code [Extra Credit B] **************************/

// Function to check whether the given request is present in cache
int getCacheIndex(char *request){
  /// return the index if the request is present in the cache
}

// Function to add the request and its file content into the cache
void addIntoCache(char *mybuf, char *memory , int memory_size){
  // It should add the request at an index according to the cache replacement policy
  // Make sure to allocate/free memory when adding or replacing cache entries
}

// clear the memory allocated to the cache
void deleteCache(){
  // De-allocate/free the cache memory
}

// Function to initialize the cache
void initCache(){
  // Allocating memory and initializing the cache array
}

/**********************************************************************************/

/* ************************************ Utilities ********************************/
// Function to get the content type from the request
char* getContentType(char * mybuf) {
  // Should return the content type based on the file type in the request
  // (See Section 5 in Project description for more details)
}

// Function to open and read the file from the disk into the memory
// Add necessary arguments as needed
int readFromDisk(/*necessary arguments*/) {
    // Open and read the contents of file given the request
}

/**********************************************************************************/

// Function to receive the request from the client and add to the queue
void * dispatch(void *arg) {

  while (1) {
    printf("Here in dispatcher\n");
    break;
    // Accept client connection

    // Get request from the client

    // Add the request into the queue

   }
   return NULL;
}

/**********************************************************************************/

// Function to retrieve the request from the queue, process it and then return a result to the client
void * worker(void *arg) {

   while (1) {

    printf("here in worker\n");
    break;
    // Get the request from the queue

    // Get the data from the disk or the cache (extra credit B)

    // Log the request into the file and terminal

    // return the result
  }
  return NULL;
}

/**********************************************************************************/

static volatile sig_atomic_t doneFlag = 0;

void gracefulTerminate(int signal){
  doneFlag = 1;
}


int main(int argc, char **argv) {

  // Error check on number of arguments
  if(argc != 8){
    printf("usage: %s port path num_dispatcher num_workers dynamic_flag queue_length cache_size\n", argv[0]);
    return -1;
  }

  // Get the input args

  int port = atoi(argv[1]);
  char* path = argv[2];
  int num_dispatcher = atoi(argv[3]);
  int num_workers = atoi(argv[4]);
  bool dynamic_flag = atoi(argv[5]);
  int queue_length = atoi(argv[6]);
  int cache_size = atoi(argv[7]);
  //printf("Port: %d\nPath: %s\nNum dispatchers: %d\nNum workers: %d\nDynamic Flag: %d\nQueue Length: %d\nCache Size: %d\n", port, path, num_dispatcher, num_workers, dynamic_flag, queue_length, cache_size);

  // Perform error checks on the input arguments
  
  if(port < 1025 || port > 65535) {
    printf("You may only use ports 1025-65535.\n");
    return -1;
  } 
  if(queue_length <= 0){
    printf("Queue length must be greater than 0.\n");
    return -1; 
  }

  // Change SIGINT action for grace termination
  
  struct sigaction act;
  act.sa_handler = gracefulTerminate;
  act.sa_flags = 0;
  if(sigemptyset(&act.sa_mask) == -1 || sigaction(SIGINT, &act, NULL) == -1){
    printf("Failed to set SIGINT handler.\n");
    return -1;
  } 

  // Open log file

  int logfile = open(path, O_WRONLY | O_CREAT, PERMS);
  if(logfile == -1){
    printf("Failed to open %s.\n", path);
    return -1;
  }

  // Change the current working directory to server root directory

  // Initialize cache (extra credit B)

  // Start the server

  // Create dispatcher and worker threads (all threads should be detachable)

  for(int n = 0; n < num_dispatcher; n++){
    pthread_t p;
    pthread_create(&p, NULL, dispatch, NULL);
  }
  for(int n = 0; n < num_workers; n++){
    pthread_t p;
    pthread_create(&p, NULL, worker, NULL);
  }

  // Create dynamic pool manager thread (extra credit A)


  // Terminate server gracefully
  while(!doneFlag){

  
  }

  // Print the number of pending requests in the request queue

  printf("\nNumber of pending requests in queue: %d\n", 5);

  // close log file

  close(logfile);

  // Remove cache (extra credit B)


  return 0;
}
