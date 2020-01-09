#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header.h"

struct node {
	int is_occupied_by;

	node_ptr left_node;
	node_ptr right_node;
};

struct player {
	node_ptr current;
	int life;
	int direction;
	int win;
};

node_ptr board;                // 게임 보드
char board_paint[SIZE + 1];     // 게임 보드 상태를 캐싱하는 배열
struct player players[PLAYERS + 1];   // 플레이어

int main(void) {

	int i;
	board = initialize();
	printBoard();
	game_logic();
	terminate(board);
	return 0;
}

void printMessage(int type) {

	if (type == INTROMESSAGE)
	{
		// 초기화 안내 메세지를 출력
		printf("\n\n");
		printf("                     《술래잡기 게임에 오신 것을 환영합니다!》\n\n");
		printf("    1. 두 플레이어가 교대로 주사위를 던지고, 상대방을 세 번 잡으면 승리합니다.\n");
		printf("    2. 주사위는 두 번 던지되, 주사위 눈의 합에 3을 나눈 만큼 이동합니다.\n");
		printf("    3. 두 주사위 눈의 합이 3 이하이면 방향을 반대로 전환한 후 1칸 전진합니다.\n");
		printf("    4. 폭탄이 있는 칸에 도착하면 라이프가 1 감소합니다. 라이프가 0이 되면 패배합니다.\n");
		printf("\n");
	}

	if (type == STATUSMESSAGE)
	{
		printf("\n");
		printf("   플레이어 1의 라이프: %d                 플레이어 2의 라이프: %d\n", players[PLAYER1].life, players[PLAYER2].life);
		printf("   플레이어 1의 승리횟수: %d               플레이어 2의 승리횟수: %d\n\n", players[PLAYER1].win, players[PLAYER2].win);
	}
}

// 양방향 순환 리스트 및 플레이어 구조체를 초기화
node_ptr initialize() {

	node_ptr temp, list;
	int i;

	// 플레이어 구조체를 초기화
	for (i = 1; i < (PLAYERS + 1); i++) {
		players[i].direction = FORWARD;
		players[i].life = LIFE;
		players[i].win = 0;
	}

	// 양방향 순환 리스트를 초기화
	temp = (node_ptr)malloc(sizeof(struct node));
	if (!temp) {
		printf("현재 사용 가능한 메모리가 없습니다. 프로그램을 중단합니다.\n");
		exit(1);
	}
	temp->is_occupied_by = PLAYER1;
	players[PLAYER1].current = temp; // ****하드 코딩됨**** 
	list = temp;

	for (i = 1; i < SIZE; i++) {
		if (i == 3) {
			players[PLAYER2].current = temp; // ****하드 코딩됨****
			temp->is_occupied_by = PLAYER2;
		}
		temp->right_node = (node_ptr)malloc(sizeof(struct node));
		if (!(temp->right_node)) {
			printf("현재 사용 가능한 메모리가 없습니다. 프로그램을 중단합니다.\n");
			exit(1);
		}
		temp->right_node->left_node = temp;
		temp = temp->right_node;
		temp->is_occupied_by = NONE;
	}

	temp->right_node = list;
	list->left_node = temp;

	// 함정 아이템을 세 곳에 배치
	for (i = 0; i < BOMBS; i++)
	{
		setBombs(list);
	}

	// 인트로 메세지를 출력
	printMessage(INTROMESSAGE);

	return list;
}

void terminate(node_ptr list) {

	int i = 1;
	node_ptr temp;

	// free list
	while (i <= SIZE) {
		temp = list;
		list = list->right_node;
		free(temp);
		i++;
	}
}

// 게임 메인 로직
void game_logic()
{
	int player = 1;
	int dice1, dice2, input;
	int count = 1000;

	while (count--) {

		printf("   ----------------------------------------------------------\n\n");

		printf("   -> 플레이어 %d의 차례입니다. 주사위를 던집니다.\n", player);
		roll_the_dice(&dice1, &dice2);

		// 주사위를 던진다 
		if (dice1 + dice2 < 4) {
			printf("   -> 플레이어 %d의 주사위 눈은 %d, %d입니다.\n",
				player, dice1, dice2);
			printf("   -> 주사위 눈의 합이 4 미만이므로 방향을 반대로 전환하고 한 칸 이동합니다.\n");
			players[player].direction = -(players[player].direction);
		}
		else {
			printf("   -> 플레이어 %d의 주사위 눈은 %d, %d이므로 %d칸 이동합니다.\n",
				player, dice1, dice2, (dice1 + dice2) / 3);
		}
		printf("\n");

		// 플레이어를 이동시킨다 
		move_player(player, ((dice1 + dice2) / 3 == 0) ? (1) : (dice1 + dice2) / 3);

		// 게임 보드를 출력한다 
		printBoard();

		// 패배 유무를 확인한다 
		check_failure(player);

		// 플레이어 순서를 변환 
		(player == 1) ? (player = 2) : (player = 1);

	}
}

void check_failure(int player) {

	// 라이프가 0인 경우 
	if (players[player].life == -40)
	{
		printf("   -> 플레이어 %d의 라이프가 0이 되었으므로 패배합니다.\n", player);
		printf("   -> 축하합니다! 승자는 플레이어%d 입니다.\n\n", (player == 1) ? (2) : (1));
		terminate(board);
		exit(0);
	}

	// 승리 횟수가 3인 경우 
	if (players[player].win == 3)
	{
		printf("   -> 플레이어 %d의 승리 횟수가 3이 되었으므로 승리합니다.\n", player);
		printf("   -> 축하합니다! 승자는 플레이어%d 입니다.\n\n", player);
		terminate(board);
		exit(0);
	}
}

void move_player(int player, int movement) {

	if (players[player].current->is_occupied_by == TWOGETHER)
		(player == 1) ? (players[player].current->is_occupied_by = PLAYER2) : (players[player].current->is_occupied_by = PLAYER1);
	else
		players[player].current->is_occupied_by = NONE;

	while (movement--)
	{
		if (players[player].direction == FORWARD)
			players[player].current = players[player].current->right_node;
		else
			players[player].current = players[player].current->left_node;
	}

	// 폭탄 여부 체크 
	if (players[player].current->is_occupied_by == BOMB)
	{
		printf("   -> 플레이어 %d가 이동한 자리에 폭탄이 있었습니다! 라이프가 1 감소합니다.\n\n",
			player);
		players[player].life--;
		setBombs(board); // 폭탄 위치 재배치 
	}

	// 술래잡기 여부 체크 
	if ((player == PLAYER2 && players[player].current->is_occupied_by == PLAYER1) ||
		(player == PLAYER1 && players[player].current->is_occupied_by == PLAYER2))
	{
		printf("   -> 플레이어 %d가 플레이어 %d를 잡았습니다! 승리 횟수가 1 증가합니다.\n\n", player, (player == 1) ? (2) : (1));
		players[player].win++;
		players[player].current->is_occupied_by = TWOGETHER;
	}
	else {
		// 위치 변경 
		if (player == 1) {
			players[player].current->is_occupied_by = PLAYER1;
		}
		else {
			players[player].current->is_occupied_by = PLAYER2;
		}
	}
}

void debug()
{
	int count = 1;
	node_ptr temp;
	temp = board;

	printf("\n");

	while (1)
	{
		printf("               %d번째 노드의 값: %d\n", count, temp->is_occupied_by);
		temp = temp->right_node;
		if (temp == board) break;
		count++;
	}

	printf("\n");
}

// 주사위를 던지는 함수
void roll_the_dice(int* dice1, int* dice2) {

	srand(time(NULL));

	*dice1 = (rand() % 6) + 1;
	*dice2 = (rand() % 6) + 1;

}

// 함정 아이템 배치
void setBombs(node_ptr list)
{
	srand(time(NULL));
	node_ptr temp;
	temp = list;
	int forward = rand() % 12;

	while (1) {
		while (forward--)
			temp = temp->right_node;
		if (temp->is_occupied_by == BOMB
			|| temp->is_occupied_by == PLAYER1
			|| temp->is_occupied_by == PLAYER2)
			forward = rand() % 12;
		else {
			temp->is_occupied_by = BOMB;
			break;
		}
	}
}

// 양방향 순환 리스트를 순회하면서 게임 보드 출력을 위한 배열에 캐싱
void traverse() {

	int count = 1;
	node_ptr temp;
	temp = board;

	while (1)
	{
		// 폭탄이 있을 경우
		if (temp->is_occupied_by == BOMB)
		{
			board_paint[count] = 'B';
		}
		else if (temp->is_occupied_by == PLAYER1)
		{
			board_paint[count] = '1';
		}
		else if (temp->is_occupied_by == PLAYER2)
		{
			board_paint[count] = '2';
		}
		else if (temp->is_occupied_by == TWOGETHER)
		{
			board_paint[count] = 'T';
		}
		else {
			board_paint[count] = ' ';
		}
		temp = temp->right_node;
		count++;
		if (temp == board) break;
	}

}

// 게임 보드를 출력
void printBoard() {

	int i;

	// 양방향 순환 리스트를 순회
	traverse();

	// 1, 2, 3, 4
	printf("               ------   ------   ------   ------                    \n");
	printf("               |  %c |   |  %c |   |  %c |   |  %c |                    \n",
		board_paint[1], board_paint[2], board_paint[3], board_paint[4]);
	printf("               ------   ------   ------   ------                    \n");

	// 12, 5
	printf("               ------                     ------                    \n");
	printf("               |  %c |                     |  %c |                    \n",
		board_paint[12], board_paint[5]);
	printf("               ------                     ------                    \n");

	// 11, 6
	printf("               ------                     ------                    \n");
	printf("               |  %c |                     |  %c |                    \n",
		board_paint[11], board_paint[6]);
	printf("               ------                     ------                    \n");

	// 10, 9, 8, 7
	printf("               ------   ------   ------   ------                    \n");
	printf("               |  %c |   |  %c |   |  %c |   |  %c |                    \n",
		board_paint[10], board_paint[9], board_paint[8], board_paint[7]);
	printf("               ------   ------   ------   ------                    \n");

	printMessage(STATUSMESSAGE);

}