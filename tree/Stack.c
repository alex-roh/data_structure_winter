#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define INIT_CAPACITY 100

struct stack_type {
	Item* contents; // ���� �迭
	int top;
	int size; // �迭�� ũ��
};

// ���� ��Ȳ�� ���� �޼����� ����ϰ� ���α׷��� ����
static void terminate(const char* message) {
	printf("%s\n", message);
	exit(1);
}

// ���� ����ü ��ü�� �����Ͽ�, �� �����͸� ��ȯ
Stack createStack() {
	Stack s = (Stack)malloc(sizeof(struct stack_type));
	if (s == NULL)
		terminate("Error in create: stack couldn't be created.");
	s->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item));
	if (s->contents == NULL) {
		free(s);
		terminate("Error in create: stack couldn't be created.");
	}
	s->top = -1;
	s->size = INIT_CAPACITY;
	return s;
}

// ������ ���� ���� �� ��� �ø� ���� ���Ҵ��Ѵ�.
void reallocate(Stack s) {
	Item* tmp = (Item*)malloc(2 * s->size * sizeof(Item));
	if (tmp == NULL) {
		terminate("Error in create: stack couldn't be created.");
	}
	for (int i = 0; i < s->size; i++)
		tmp[i] = s->contents[i];
	free(s->contents);
	s->contents = tmp;
	s->size *= 2;
}

void destroyStack(Stack s) {
	free(s->contents);
	free(s);
}

bool is_full_stack(Stack s) {
	return (s->top == s->size - 1);
}

void push(Stack s, Item i) {
	if (is_full_stack(s))
		reallocate(s);
	s->top++;
	s->contents[s->top] = i;
}

Item pop(Stack s) {
	if (is_empty_stack(s))
		return NULL;
	s->top--;
	return s->contents[s->top + 1];
}

Item peekStack(Stack s) {
	if (is_empty_stack(s))
		return NULL;
	return s->contents[s->top];
}

// ������ �����ϱ� ���� �Լ�
void make_empty_stack(Stack s) {
	s->top = -1;
}

bool is_empty_stack(Stack s) {
	return (s->top == -1);
}