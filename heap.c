

#include "heap.h"

HEAP *new_heap(int capacity) {
	HEAP *hp = (HEAP *) malloc(sizeof(HEAP));
	hp->capacity = capacity;
	hp->hnap = (HNODE *) malloc(sizeof(HEAP) * capacity);
	hp->size = 0;
	return hp;
}
/* this inserts the given node data a into the heap; When the heap size is equal to the capacity, the inserting process needs
 * first to expand data array by doubling its amount. This may need to copy the data of old array to new array,
 * secondly insert the new data element into the end of the array and update size.*/
void insert(HEAP *heap, HNODE new_node) {
	if (heap->size < heap->capacity) {
		heap->hnap[heap->size] = new_node;
	} else {
		heap->capacity *= 2;

		HNODE *temp = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);

		if (temp) {
			heap->hnap = temp;
		} else {
			temp = malloc(sizeof(HNODE) * heap->capacity);

			if (temp) {
				memcpy(temp, heap->hnap, sizeof(HNODE) * heap->size);
				free(heap->hnap);
				heap->hnap = temp;
			} else {
				printf("array resize failed\n");
			}
		}
		heap->hnap[heap->size] = new_node;
	}
	heap->size++;
	int current = heap->size - 1;
	int parent = (current - 1) / 2;

	while (cmp(heap->hnap[current].key, heap->hnap[parent].key) == -1) {
		HNODE temp = heap->hnap[current];
		heap->hnap[current] = heap->hnap[parent];
		heap->hnap[parent] = temp;
		current = parent;
		parent = (current - 1) / 2;
	}



}

HNODE extract_min(HEAP *heap) {
	HNODE min = heap->hnap[0];
	heap->hnap[0] = heap->hnap[heap->size - 1];
	free(heap->hnap + heap->size - 1);
	heap->size--;
	int current = 0;

	int child =
			2 * current + 2 < heap->size ?
					cmp(heap->hnap[2 * current + 1].key,
							heap->hnap[2 * current + 2].key) == -1 ?
							2 * current + 1 : 2 * current + 2
			: 2 * current + 1 < heap->size ? 2 * current + 1 : current;

	while (cmp(heap->hnap[current].key, heap->hnap[child].key) == 1) {
		HNODE temp = heap->hnap[current];
		heap->hnap[current] = heap->hnap[child];
		heap->hnap[child] = temp;
		current = child;
		child = 2 * current + 2 < heap->size ?
				cmp(heap->hnap[2 * current + 1].key,
						heap->hnap[2 * current + 2].key) == -1 ?
						2 * current + 1 : 2 * current + 2
				: 2 * current + 1 < heap->size ? 2 * current + 1 : current;
	}
	if (heap->size < heap->capacity / 2) {
		heap->capacity /= 2;
		HNODE *temp = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);
		if (temp) {
			heap->hnap = temp;
		} else {
			temp = malloc(sizeof(HNODE) * heap->capacity);
			if (temp) {
				memcpy(temp, heap->hnap, sizeof(HNODE) * heap->size);
				free(heap->hnap);
				heap->hnap = temp;
			} else {
				printf("array resize failed\n");
			}
		}
	}
	return min;
}

void decrease_key(HEAP *heap, int node_index, KEYTYPE key_value) {
	if (heap->hnap[node_index].key > key_value) {
		heap->hnap[node_index].key = key_value;
		int current = 0;
		int child =
				2 * current + 2 < heap->size ?
						cmp(heap->hnap[2 * current + 1].key,
								heap->hnap[2 * current + 2].key) == -1 ?
								2 * current + 1 : 2 * current + 2
				: 2 * current + 1 < heap->size ? 2 * current + 1 : current;
		while (cmp(heap->hnap[current].key, heap->hnap[child].key) == 1) {
			HNODE temp = heap->hnap[current];
			heap->hnap[current] = heap->hnap[child];
			heap->hnap[child] = temp;
			current = child;
			child = 2 * current + 2 < heap->size ?
					cmp(heap->hnap[2 * current + 1].key,
							heap->hnap[2 * current + 2].key) == -1 ?
							2 * current + 1 : 2 * current + 2
					: 2 * current + 1 < heap->size ? 2 * current + 1 : current;
		}
	} else {
		heap->hnap[node_index].key = key_value;
		int current = heap->size - 1;
		int parent = (current - 1) / 2;

		while (cmp(heap->hnap[current].key, heap->hnap[parent].key) == -1) {
			HNODE temp = heap->hnap[current];
			heap->hnap[current] = heap->hnap[parent];
			heap->hnap[parent] = temp;
			current = parent;
			parent = (current - 1) / 2;
		}
	}
}

int find_index(HEAP *heap, DATA value) {
	for (int i = 0; i < heap->size; i++) {
		if (heap->hnap[i].data == value) {
			return i;
		}
	}
	return -1;
}

void display_heap(HEAP *hp) {
	printf("\nsize:%d\ncapacity:%d\n", hp->size, hp->capacity);
	printf("(index, key, data):\n");
	int i;
	for (i = 0; i < hp->size; i++) {
		printf("(%d %d %d) ", i, hp->hnap[i].key, hp->hnap[i].data);
		if (i % 10 == 9)
			printf("\n");
	}
	printf("\n");
}

int cmp(KEYTYPE a, KEYTYPE b) {
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
