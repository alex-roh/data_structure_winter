#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

node_ptr tree;

node_ptr make_node(char data) {

	node_ptr temp;
	temp = (node_ptr)malloc(sizeof(struct node));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;

}

void make_tree() {

	node_ptr temp1, temp2;
	// level 1 (root)
	tree = make_node('-');

	// level 2
	temp1 = tree->left = make_node('+');
	temp2 = tree->right = make_node('/');

	// level 3
	temp1->left = make_node('*');
	temp1->right = make_node('C');
	temp2->left = make_node('D');
	temp2->right = make_node('E');

	// level 4
	temp1->left->left = make_node('A');
	temp1->left->right = make_node('B');

}

int main(void) {

	make_tree();
	iterativeInorder(tree);
	printf("\n");

	return 0;
}
