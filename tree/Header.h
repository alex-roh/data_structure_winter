#ifndef _HEADER_GUARD_
#define _HEADER_GUARD_

typedef struct node* node_ptr;

struct node {

	char data;
	node_ptr left;
	node_ptr right;

};

void postOrder(node_ptr ptr);
void inOrder(node_ptr ptr);
void preOrder(node_ptr ptr);
void iterativeInorder(node_ptr ptr);
void levelOrder(node_ptr ptr);

#endif
