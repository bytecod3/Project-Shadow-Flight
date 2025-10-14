#include "stdio.h"
#define BUFFER_MAX_SIZE 10

typedef struct _buffer {
    int size;
    int head;
    int tail;
} ring_buffer_t;

/*ring buffer functions */
void buffer_init(int size);
int buffer_read();
void add_item();
void buffer_is_empty();
void buffer_is_full();

/**
* create memory to hold size items 
*/
void buffer_init(int size) {
    ring_buffer_t ring_buffer;
    ring_buffer.size = size;
    ring_buffer.head = 0;
    ring_buffer.tail = 0;

}

int buffer_read() {
}

