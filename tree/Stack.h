// ������ �����ϴ� ����
#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h> // C99 only, bool Ÿ���� �����Ѵ�.

typedef int Item; // int �ڷ����� Item���� aliasing (Ȯ�忡 ����)
typedef struct stack_type* Stack; // ����ü stack_type�� �����͸�
																	// Stack�̶�� �̸����� ����
																	// �ڵ� �ȿ� * �����ڸ� ����� �� X
Stack createStack();
void destroyStack(Stack s);
void make_empty_stack(Stack s);
bool is_empty_stack(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peekStack(Stack s);

#endif