#ifndef TW_TYPES_H
#define TW_TYPES_H

#include <ucontext.h>

typedef unsigned int worker_t;

/* Define thread states */
typedef enum {
    THREAD_CREATED,
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_BLOCKED,
    THREAD_TERMINATED
} thread_state;

/* Define thread context structure */
typedef struct {
    /* Add thread context information as needed */
    // For example, registers, instruction pointer, stack pointer, etc.
    // Assuming a simple structure here for demonstration purposes
    void* registers;
    void* instruction_pointer;
    void* stack_pointer;
} thread_context;

/* Define thread stack structure */
typedef struct {
    /* Add thread stack information as needed */
    // For example, base address, size, etc.
    void* base_address;
    size_t size;
} thread_stack;

/* Define TCB structure */
typedef struct TCB
{
    /* Add important states in a thread control block */
    worker_t thread_id;         // Thread ID (a unique ID to identify each worker thread)
    thread_state status;        // Thread status
    thread_context context;     // Thread context
    thread_stack stack;         // Thread stack
    int priority;               // Thread priority (if applicable)
    // And more, depending on your requirements...

    // YOUR CODE HERE

} tcb;

#endif
