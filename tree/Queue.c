#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define INIT_CAPACITY 100

struct queue_type {
	// 큐로 사용할 배열 (포인터로 선언하여 동적 메모리 사용)
	Item* contents;
	int front;
	int rear;
	int size;     // 저장된 데이터의 개수
	int capacity; // 배열의 크기
};

void terminate(const char* message) {
	printf("%s\n", message);
	exit(1);
}

int get_size(Queue q) {
	return q->size;
}

Queue createQueue() {
	// 구조체 객체를 생성
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL)
		terminate("Error in create: queue can't be created.");
	// 큐로 사용할 배열을 생성
	q->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item));
	if (q->contents == NULL) {
		free(q);
		terminate("Error in create: queue can't be created.");
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = INIT_CAPACITY;
	return q;
}

void destoryQueue(Queue q) {
	free(q->contents);
	free(q);
}

// 큐를 비운다.
void make_empty_Queue(Queue q) {
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty_Queue(Queue q) {
	return q->size == 0;
}

bool is_full(Queue q) {
	return (q->size == q->capacity);
}

void enqueue(Queue q, Item i) {
	if (is_full(q))
		reallocate(q);
	// rear를 앞으로 한 칸 전진시킨다
	q->rear = (q->rear + 1) % (q->capacity);
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) {
	if (is_empty(q))
		terminate("Error in dequeue: queue is empty.");
	// 현재 front에 있는 값을 반환
	Item result = q->contents[q->front];
	// front를 앞으로 한 칸 전진시킨다
	q->front = (q->front + 1) % (q->capacity);
	q->size--;
	return result;
}

Item peekQueue(Queue q) {
	if (is_empty(q))
		terminate("Error in peek: queue is empty.");
	return q->contents[q->front];
}