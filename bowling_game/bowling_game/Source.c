#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

struct frame 
{
	int first;
	int second;
	int result;
	frame_ptr right_node;
};

struct score
{
	int first;
	int second;
};

frame_ptr list;
score test[MAX_FRAME + 1] = {8, 0, 4, 3, 8, 2, 4, 6, 2, 6,
						  10, 0, 9, 0, 10, 0, 8, 2, 10, 0,
						  10, 10};
score s[MAX_FRAME + 1];

// 유저로부터 점수를 입력받는 함수
void readFromInput() {

	int i = 0, j = 0;
	int input = 0;

	printf("\n");

	while (i < MAX_FRAME + 1) {
		for (j = 0; j < 2; j++) 
		{
			(i == MAX_FRAME) ?
				(printf("보너스 프레임의 %d번째 점수를 입력해 주세요: ", 1)) 
				: (printf("%d번째 프레임의 %d번째 점수를 입력해 주세요: ", i + 1, j + 1));
			scanf("%d", &input);
			(j == 0) ? (s[i].first = input) : (s[i].second = input);	
			fflush(stdin);
			if (input > 10 || input < 0) { inputError(); return; }; // 입력 예외 처리
		}
		i++;
	}
	
	printf("\n");

}

void inputError() {
	int i;
	for (i = 0; i < MAX_FRAME + 1; i++) {
		s[i].first = test[i].first;
		s[i].second = test[i].second;
	}
}

int main(void) {

	int i = 0, sum = 0;
	frame_ptr temp;

	initialize();
	readFromInput();

	temp = list;

	while (i < MAX_FRAME) 
	{	
		temp->first = s[i].first;
		temp->second = s[i].second;

		if (s[i].first == 10) 
		{	
			sum += s[i].first + s[i + 1].first + s[i + 1].second;
			temp->result = STRIKE;
			if (i != 9 && s[i + 1].first == 10)
				sum += s[i + 2].first;
		}
		else if ((s[i].first + s[i].second) == 10)
		{
			temp->result = SPARE;
			sum += s[i].first + s[i].second + s[i + 1].first;
		}
		else 
		{
			temp->result = NONE;
			sum += s[i].first + s[i].second;
		}

		// 결과 출력
		switch (temp->result) 
		{
			case STRIKE:
				printf("%d/%d : %d STRIKE!\n", temp->first, temp->second, sum);
				break;

			case SPARE:
				printf("%d/%d : %d Spare\n", temp->first, temp->second, sum);
				break;

			default:
				printf("%d/%d : %d\n", temp->first, temp->second, sum);
				break;
		}
		temp = temp->right_node;
		i++;
	}

	// 보너스 프레임
	temp->result = NONE;
	if(s[MAX_FRAME].first != 0)
		printf("(Bonus : %d, %d)\n", (temp->first = s[MAX_FRAME].first),
			(temp->second = s[MAX_FRAME].second));

	printf("total : %d\n", sum);

	// 동적 메모리 할당 해제
	terminate();

	return 0;
}

void initialize() {

	int i;
	frame_ptr temp;

	list = (frame_ptr)malloc(sizeof(struct frame));
	temp = list;

	for (i = 0; i < MAX_FRAME; i++) {
		temp->right_node = (frame_ptr)malloc(sizeof(struct frame));
		temp = temp->right_node;
	}
	
}

void terminate() {

	int i;
	frame_ptr temp;

	for (i = 0; i < MAX_FRAME; i++) {
		temp = list;
		list = list->right_node;
		free(temp);
	}

}

void debug() {

	int i;
	frame_ptr temp;
	temp = list;

	printf("\n");

	for (i = 0; i < MAX_FRAME + 1; i++) {
		printf("%d번째 노드의 first: %d, second: %d, result: %d\n",
			i + 1, temp->first, temp->second, temp->result);
		temp = temp->right_node;
	}
	
	printf("\n");

}