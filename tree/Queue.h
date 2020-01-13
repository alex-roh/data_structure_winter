#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdbool.h> // C99 only

typedef int Item;
typedef struct queue_type* Queue;

Queue createQueue();
void destoryQueue(Queue q);
void make_empty_Queue(Queue q);
bool is_empty_Queue(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peekQueue(Queue q);
int get_size(Queue q); // ť�� ���ð� �޸� ���� ������ ������
											 // �˾ƾ� �� ���� ����� ����.

#endif