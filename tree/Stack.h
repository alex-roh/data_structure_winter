// 정수를 저장하는 스택
#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h> // C99 only, bool 타입을 지원한다.

typedef int Item; // int 자료형을 Item으로 aliasing (확장에 용이)
typedef struct stack_type* Stack; // 구조체 stack_type의 포인터를
																	// Stack이라는 이름으로 정의
																	// 코드 안에 * 연산자를 사용할 일 X
Stack createStack();
void destroyStack(Stack s);
void make_empty_stack(Stack s);
bool is_empty_stack(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peekStack(Stack s);

#endif