#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

/**
 * struct queue - a structure to represent the queue
 *
 * @front: front of the queue
 * @rear: index of last element in the queue
 * @size: size of the queue array
 * @items: pointer to array of characters
 */
typedef struct
{
	int front;
	int rear;
	int size;
	char *items;
} Queue;

/**
 * createQueue - Create a queue
 * @size: size of the queue to create
 *
 * Return: Pointer to Queue
 */
Queue *createQueue(int size)
{
	Queue *queue = malloc(sizeof(Queue));

	queue->front = -1;
	queue->rear = -1;
	queue->size = size;
	queue->items = malloc(sizeof(char) * size);

	return queue;
}

/**
 * isFull - Checks of a queue is full
 *
 * @queue: pointer to queue
 *
 * Return: bool to indicate whether full or not
 */
bool isFull(Queue *queue)
{
	return queue->front != -1 && ((queue->rear + 1) % queue->size == queue->front);
}

/**
 * isEmpty - checks if a queue is empty
 *
 * @queue: pointer to queue
 *
 * Return: bool
 */
bool isEmpty(Queue *queue)
{
	return (queue->front == -1);
}

/**
 * enqueue - add an element to the queue
 *
 * @queue: pointer to the queue
 * @element: element to add to queue
 *
 * Return: bool
 */
bool enqueue(Queue *queue, char element)
{
	if (isFull(queue))
	{
		printf("Queue is full\n");
		return false;
	}

	if (isEmpty(queue))
	{
		queue->front = 0;
	}
	queue->rear = (queue->rear + 1) % queue->size;
	queue->items[queue->rear] = element;
	return true;
}

/**
 * dequeue - remove element from the front of a queue
 *
 * @queue: pointer to queue
 *
 * Return: removed element
 */
char dequeue(Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty\n");
		return -1;
	}

	char element = queue->items[queue->front];

	if (queue->front == queue->rear)
	{
		queue->front = -1;
		queue->rear = -1;
	}
	else
	{
		queue->front = (queue->front + 1) % queue->size;
	}

	return element;
}

/**
 * displayQueue - display the elements of a queue
 *
 * @queue: pointer to queue
 */
void displayQueue(Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue is empty\n");
		return;
	}

	printf("Elements: ");

	int i = queue->front;
	while (true)
	{
		printf("%c ", queue->items[i]);
		if (queue->rear == i)
		{
			break;
		}
		i = (i + 1) % queue->size;
	}
	printf("\n");
}

/**
 * lastElement - return the last element of a queue
 *
 * @queue: pointer to queue
 *
 * Return: last element in queue
 */
char lastElement(Queue queue)
{
	return queue.items[queue.rear];
}

/**
 * deleteQueue - frees queue from memory
 *
 * @queue: pointer to queue
 */
void deleteQueue(Queue *queue)
{
	free(queue->items);
	free(queue);
}

int main(void)
{
	// create Queue
	Queue *queue = createQueue(10);

	// insert A, B, C
	enqueue(queue, 'A');
	enqueue(queue, 'B');
	enqueue(queue, 'C');

	// seed random number generator
	srand(time(0));
	while (true)
	{
		int randomNumber = rand() % 10;

		if (randomNumber > 1)
		{
			if (isFull(queue))
			{
				break;
			}
			enqueue(queue, lastElement(*queue) + 1);
		}
		else
		{
			if (isEmpty(queue))
			{
				break;
			}
			dequeue(queue);
		}
		// display random number and queue
		printf("Random number: %i\n", randomNumber);
		displayQueue(queue);
	}

	// delete queue
	deleteQueue(queue);

	return 0;
}
