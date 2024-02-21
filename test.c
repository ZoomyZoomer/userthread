#include <stdio.h>
#include <unistd.h>
#include "thread-worker.h"

/* A scratch program template on which to call and
 * test thread-worker library functions as you implement
 * them.
 *
 * You can modify and use this program as much as possible.
 * This will not be graded.
 */

int main(int argc, char **argv)
{

	/* Implement HERE */

	printf("Starting main\n");
	worker_t thread;

    int id = 1;
    worker_create(&thread, NULL, NULL, &id);

	return 0;
}
