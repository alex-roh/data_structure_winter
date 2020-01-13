#include <stdio.h>
#include "Header.h"
#include "Stack.h"
#include "Queue.h"

void postOrder(node_ptr ptr) {

	if (ptr) {
		postOrder(ptr->left);
		postOrder(ptr->right);
		printf("%c ", ptr->data);
	}
}

void inOrder(node_ptr ptr) {

	if (ptr) {
		inOrder(ptr->left);
		printf("%c ", ptr->data);
		inOrder(ptr->right);
	}
}

void preOrder(node_ptr ptr) {

	if (ptr) {
		printf("%c ", ptr->data);
		preOrder(ptr->left);
		preOrder(ptr->right);
	}
}

void iterativeInorder(node_ptr ptr) {

	Stack stack = createStack();

	for (; ;) 
	{
		for (; ptr; ptr = ptr->left)
			push(stack, ptr);
		ptr = pop(stack);
		if (!ptr) break;
		printf("%c ", ptr->data);
		ptr = ptr->right;
	}

}
