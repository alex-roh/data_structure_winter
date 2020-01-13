#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define INIT_CAPACITY 100

struct queue_type {
	// ť�� ����� �迭 (�����ͷ� �����Ͽ� ���� �޸� ���)
	Item* contents;
	int front;
	int rear;
	int size;     // ����� �������� ����
	int capacity; // �迭�� ũ��
};

void terminate(const char* message) {
	printf("%s\n", message);
	exit(1);
}

int get_size(Queue q) {
	return q->size;
}

Queue createQueue() {
	// ����ü ��ü�� ����
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL)
		terminate("Error in create: queue can't be created.");
	// ť�� ����� �迭�� ����
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

// ť�� ����.
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
	// rear�� ������ �� ĭ ������Ų��
	q->rear = (q->rear + 1) % (q->capacity);
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) {
	if (is_empty(q))
		terminate("Error in dequeue: queue is empty.");
	// ���� front�� �ִ� ���� ��ȯ
	Item result = q->contents[q->front];
	// front�� ������ �� ĭ ������Ų��
	q->front = (q->front + 1) % (q->capacity);
	q->size--;
	return result;
}

Item peekQueue(Queue q) {
	if (is_empty(q))
		terminate("Error in peek: queue is empty.");
	return q->contents[q->front];
}