// ������ �����ϴ� ����
#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h> // C99 only, bool Ÿ���� �����Ѵ�.

typedef int Item; // int �ڷ����� Item���� aliasing (Ȯ�忡 ����)
typedef struct stack_type* Stack; // ����ü stack_type�� �����͸�
																	// Stack�̶�� �̸����� ����
																	// �ڵ� �ȿ� * �����ڸ� ����� �� X
Stack createStack();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif