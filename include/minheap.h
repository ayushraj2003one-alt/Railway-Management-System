#ifndef MINHEAP_H
#define MINHEAP_H

/* Structure to represent a min heap node */
typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

/* Structure to represent a Min Heap with position tracking for O(log V) decreaseKey */
typedef struct MinHeap {
    int size;       /* Number of heap nodes currently present */
    int capacity;   /* Total capacity of min heap */
    int* pos;       /* Position tracker of node v in heap array */
    MinHeapNode** array;
} MinHeap;

/* Function prototypes */
MinHeapNode* newMinHeapNode(int v, int dist);
MinHeap* createMinHeap(int capacity);
void freeMinHeap(MinHeap* minHeap);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
int isInMinHeap(const MinHeap* minHeap, int v);

#endif /* MINHEAP_H */
