#include "queue.h"


/* creates a new queue with a given size */
queue_t* create_queue(int capacity){
	queue_t *q_p;
	q_p = (queue_t*)malloc(sizeof(queue_t));
	q_p->data = (void**)malloc(capacity*sizeof(void*));
	q_p->head = 0;
	q_p->tail = 0;
	q_p->counter = 0;
	q_p->size = capacity;
	
	return q_p;
}

// ^ done


/* 
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data){
  if(queue->counter == queue->size){
    return false;
  }
  if(queue->tail == queue->size){
    queue->tail = 0;
  }
  queue->data[queue->tail] = data;
  ++queue->tail;
  ++queue->counter;
  return true;
}  

// ^ done

/* 
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue){
	if(queue->counter == 0){
		return NULL;
	}
	else{
		void* data = queue->data[queue->head];
		queue->data[queue->head] = NULL;
		if(queue->head == queue->size - 1){
			queue->head = 0;
		}
		else{
			++queue->head;
		}
		--queue->counter;
		return data;
	}
}

// ^ done



	
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue){
  free(queue->data);
  free(queue);
}

// ^ done

/* 
 * gets idx-th element from the queue
 * returns the element that will be popped after idx calls of the pop_from_queue() 
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx){
  if(idx < 0 || idx >= queue->counter){
  	return NULL;
  }
  int index = queue->head + idx;
  if(index > queue->size) index -= queue->size;
  return queue->data[index];
}

// ^done

/* gets number of stored elements */
int get_queue_size(queue_t *queue){
	return queue->counter;
}	
	
// ^ done
