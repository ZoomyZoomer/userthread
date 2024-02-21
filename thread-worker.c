// File:	thread-worker.c

// List all group member's name:
/*
 */
// username of iLab:
// iLab Server:


#include "thread-worker.h"
#include "thread_worker_types.h"

#define STACK_SIZE 16 * 1024
#define QUANTUM 10 * 1000


// INITIALIZE ALL YOUR OTHER VARIABLES HERE

// Define a structure for queue node
struct QueueNode {
    void *context; // Pointer to the context data type
    struct QueueNode* next;
};

// Define a structure for the queue
struct Queue {
    struct QueueNode *front, *rear;
    void (*enqueue)(struct Queue*, void*); // Function pointer for enqueue operation
    void* (*dequeue)(struct Queue*);       // Function pointer for dequeue operation
};

// Function to create a new queue node
struct QueueNode* newNode(void *context) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->context = context;
    temp->next = NULL;
    return temp;
}

// Function to create a new queue
void createQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, void *context) {
    struct QueueNode* temp = newNode(context);
    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}

// Function to dequeue an element from the queue
void* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    struct QueueNode* temp = queue->front;
    void* context = temp->context;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return context;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

struct Queue queue;
int init_scheduler_done = 0;
tcb* toEnqueue;
ucontext_t scheduleContext;

static void schedule();
/* create a new thread */
int worker_create(worker_t *thread, pthread_attr_t *attr, void* (*function)(void *), void *arg)
{


    // Create a new TCB (Thread Control Block)
    tcb *new_tcb = (tcb *)malloc(sizeof(tcb));
    if (new_tcb == NULL) {
        return -1;
    }

    // Set the initial state of the thread
    new_tcb->status = THREAD_CREATED;

    // - create and initialize the context of this worker thread
    ucontext_t cctx;

    if (getcontext(&cctx) < 0){
        perror("getcontext");
        exit(1);
    }

    // - allocate space of stack for this thread to run
    void *stack=malloc(STACK_SIZE);

    /* Setup context that we are going to use */
	cctx.uc_link=NULL;
	cctx.uc_stack.ss_sp=stack;
	cctx.uc_stack.ss_size=STACK_SIZE;
	cctx.uc_stack.ss_flags=0;

    makecontext(&cctx, (void (*)(void)) function, 0);
    new_tcb->context = cctx;
    new_tcb->thread_id = *(int *)arg;
	puts("Successfully modified context");

    toEnqueue = new_tcb;
    queue.enqueue(&queue, toEnqueue);
    if (init_scheduler_done == 0){
        schedule();
    }

    // after everything is set, push this thread into run queue and
    

    // - make it ready for the execution.
    return 0;
}

/* give CPU possession to other user-level worker threads voluntarily */
int worker_yield()
{

    // - change worker thread's state from Running to Ready
    // - save context of this thread to its thread control block
    // - switch from thread context to scheduler context
    return 0;

};

/* terminate a thread */
void worker_exit(void *value_ptr)
{
    // - if value_ptr is provided, save return value
    // - de-allocate any dynamic memory created when starting this thread (could be done here or elsewhere)
}

/* Wait for thread termination */
int worker_join(worker_t thread, void **value_ptr)
{

    // - wait for a specific thread to terminate
    // - if value_ptr is provided, retrieve return value from joining thread
    // - de-allocate any dynamic memory created by the joining thread
    return 0;

};

/* initialize the mutex lock */
int worker_mutex_init(worker_mutex_t *mutex,
                      const pthread_mutexattr_t *mutexattr)
{
    //- initialize data structures for this mutex
    return 0;

};

/* aquire the mutex lock */
int worker_mutex_lock(worker_mutex_t *mutex)
{

    // - use the built-in test-and-set atomic function to test the mutex
    // - if the mutex is acquired successfully, enter the critical section
    // - if acquiring mutex fails, push current thread into block list and
    // context switch to the scheduler thread
    return 0;

};

/* release the mutex lock */
int worker_mutex_unlock(worker_mutex_t *mutex)
{
    // - release mutex and make it available again.
    // - put one or more threads in block list to run queue
    // so that they could compete for mutex later.

    return 0;
};

/* destroy the mutex */
int worker_mutex_destroy(worker_mutex_t *mutex)
{
    // - make sure mutex is not being used
    // - de-allocate dynamic memory created in worker_mutex_init

    return 0;
};

static void initSchedule(){
    if (init_scheduler_done == 0){
        queue.enqueue = enqueue;
        queue.dequeue = dequeue;
        createQueue(&queue);
        init_scheduler_done = 1;

        if (getcontext(&scheduleContext) < 0){
            perror("getcontext");
            exit(1);
        }

        // - allocate space of stack for this thread to run
        void *stack=malloc(STACK_SIZE);

        /* Setup context that we are going to use */
        scheduleContext.uc_link=NULL;
        scheduleContext.uc_stack.ss_sp=stack;
        scheduleContext.uc_stack.ss_size=STACK_SIZE;
        scheduleContext.uc_stack.ss_flags=0;
    }
}

/* scheduler */
static void schedule()
{

    tcb* ptr = (tcb*)queue.dequeue(&queue);
    setcontext(&(ptr->context));

// - every time a timer interrupt occurs, your worker thread library
// should be contexted switched from a thread context to this
// schedule() function

// - invoke scheduling algorithms according to the policy (RR or MLFQ)

// - schedule policy
#ifndef MLFQ
    // Choose RR
    
#else
    // Choose MLFQ
    
#endif
}

static void sched_rr()
{
    // - your own implementation of RR
    // (feel free to modify arguments and return types)

}

/* Preemptive MLFQ scheduling algorithm */
static void sched_mlfq()
{
    // - your own implementation of MLFQ
    // (feel free to modify arguments and return types)

}

// Feel free to add any other functions you need.
// You can also create separate files for helper functions, structures, etc.
// But make sure that the Makefile is updated to account for the same.

void* test(){
    printf("bet");
    return NULL;
}

int main(int argc, char **argv)
{

	/* Implement HERE */

	printf("Starting main\n");
	worker_t thread;

    int id = 1;
    worker_create(&thread, NULL, &test, &id);

	return 0;
}
