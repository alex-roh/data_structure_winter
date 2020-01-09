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

node_ptr board;                // ���� ����
char board_paint[SIZE + 1];     // ���� ���� ���¸� ĳ���ϴ� �迭
struct player players[PLAYERS + 1];   // �÷��̾�

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
		// �ʱ�ȭ �ȳ� �޼����� ���
		printf("\n\n");
		printf("                     ��������� ���ӿ� ���� ���� ȯ���մϴ�!��\n\n");
		printf("    1. �� �÷��̾ ����� �ֻ����� ������, ������ �� �� ������ �¸��մϴ�.\n");
		printf("    2. �ֻ����� �� �� ������, �ֻ��� ���� �տ� 3�� ���� ��ŭ �̵��մϴ�.\n");
		printf("    3. �� �ֻ��� ���� ���� 3 �����̸� ������ �ݴ�� ��ȯ�� �� 1ĭ �����մϴ�.\n");
		printf("    4. ��ź�� �ִ� ĭ�� �����ϸ� �������� 1 �����մϴ�. �������� 0�� �Ǹ� �й��մϴ�.\n");
		printf("\n");
	}

	if (type == STATUSMESSAGE)
	{
		printf("\n");
		printf("   �÷��̾� 1�� ������: %d                 �÷��̾� 2�� ������: %d\n", players[PLAYER1].life, players[PLAYER2].life);
		printf("   �÷��̾� 1�� �¸�Ƚ��: %d               �÷��̾� 2�� �¸�Ƚ��: %d\n\n", players[PLAYER1].win, players[PLAYER2].win);
	}
}

// ����� ��ȯ ����Ʈ �� �÷��̾� ����ü�� �ʱ�ȭ
node_ptr initialize() {

	node_ptr temp, list;
	int i;

	// �÷��̾� ����ü�� �ʱ�ȭ
	for (i = 1; i < (PLAYERS + 1); i++) {
		players[i].direction = FORWARD;
		players[i].life = LIFE;
		players[i].win = 0;
	}

	// ����� ��ȯ ����Ʈ�� �ʱ�ȭ
	temp = (node_ptr)malloc(sizeof(struct node));
	if (!temp) {
		printf("���� ��� ������ �޸𸮰� �����ϴ�. ���α׷��� �ߴ��մϴ�.\n");
		exit(1);
	}
	temp->is_occupied_by = PLAYER1;
	players[PLAYER1].current = temp; // ****�ϵ� �ڵ���**** 
	list = temp;

	for (i = 1; i < SIZE; i++) {
		if (i == 3) {
			players[PLAYER2].current = temp; // ****�ϵ� �ڵ���****
			temp->is_occupied_by = PLAYER2;
		}
		temp->right_node = (node_ptr)malloc(sizeof(struct node));
		if (!(temp->right_node)) {
			printf("���� ��� ������ �޸𸮰� �����ϴ�. ���α׷��� �ߴ��մϴ�.\n");
			exit(1);
		}
		temp->right_node->left_node = temp;
		temp = temp->right_node;
		temp->is_occupied_by = NONE;
	}

	temp->right_node = list;
	list->left_node = temp;

	// ���� �������� �� ���� ��ġ
	for (i = 0; i < BOMBS; i++)
	{
		setBombs(list);
	}

	// ��Ʈ�� �޼����� ���
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

// ���� ���� ����
void game_logic()
{
	int player = 1;
	int dice1, dice2, input;
	int count = 1000;

	while (count--) {

		printf("   ----------------------------------------------------------\n\n");

		printf("   -> �÷��̾� %d�� �����Դϴ�. �ֻ����� �����ϴ�.\n", player);
		roll_the_dice(&dice1, &dice2);

		// �ֻ����� ������ 
		if (dice1 + dice2 < 4) {
			printf("   -> �÷��̾� %d�� �ֻ��� ���� %d, %d�Դϴ�.\n",
				player, dice1, dice2);
			printf("   -> �ֻ��� ���� ���� 4 �̸��̹Ƿ� ������ �ݴ�� ��ȯ�ϰ� �� ĭ �̵��մϴ�.\n");
			players[player].direction = -(players[player].direction);
		}
		else {
			printf("   -> �÷��̾� %d�� �ֻ��� ���� %d, %d�̹Ƿ� %dĭ �̵��մϴ�.\n",
				player, dice1, dice2, (dice1 + dice2) / 3);
		}
		printf("\n");

		// �÷��̾ �̵���Ų�� 
		move_player(player, ((dice1 + dice2) / 3 == 0) ? (1) : (dice1 + dice2) / 3);

		// ���� ���带 ����Ѵ� 
		printBoard();

		// �й� ������ Ȯ���Ѵ� 
		check_failure(player);

		// �÷��̾� ������ ��ȯ 
		(player == 1) ? (player = 2) : (player = 1);

	}
}

void check_failure(int player) {

	// �������� 0�� ��� 
	if (players[player].life == -40)
	{
		printf("   -> �÷��̾� %d�� �������� 0�� �Ǿ����Ƿ� �й��մϴ�.\n", player);
		printf("   -> �����մϴ�! ���ڴ� �÷��̾�%d �Դϴ�.\n\n", (player == 1) ? (2) : (1));
		terminate(board);
		exit(0);
	}

	// �¸� Ƚ���� 3�� ��� 
	if (players[player].win == 3)
	{
		printf("   -> �÷��̾� %d�� �¸� Ƚ���� 3�� �Ǿ����Ƿ� �¸��մϴ�.\n", player);
		printf("   -> �����մϴ�! ���ڴ� �÷��̾�%d �Դϴ�.\n\n", player);
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

	// ��ź ���� üũ 
	if (players[player].current->is_occupied_by == BOMB)
	{
		printf("   -> �÷��̾� %d�� �̵��� �ڸ��� ��ź�� �־����ϴ�! �������� 1 �����մϴ�.\n\n",
			player);
		players[player].life--;
		setBombs(board); // ��ź ��ġ ���ġ 
	}

	// ������� ���� üũ 
	if ((player == PLAYER2 && players[player].current->is_occupied_by == PLAYER1) ||
		(player == PLAYER1 && players[player].current->is_occupied_by == PLAYER2))
	{
		printf("   -> �÷��̾� %d�� �÷��̾� %d�� ��ҽ��ϴ�! �¸� Ƚ���� 1 �����մϴ�.\n\n", player, (player == 1) ? (2) : (1));
		players[player].win++;
		players[player].current->is_occupied_by = TWOGETHER;
	}
	else {
		// ��ġ ���� 
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
		printf("               %d��° ����� ��: %d\n", count, temp->is_occupied_by);
		temp = temp->right_node;
		if (temp == board) break;
		count++;
	}

	printf("\n");
}

// �ֻ����� ������ �Լ�
void roll_the_dice(int* dice1, int* dice2) {

	srand(time(NULL));

	*dice1 = (rand() % 6) + 1;
	*dice2 = (rand() % 6) + 1;

}

// ���� ������ ��ġ
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

// ����� ��ȯ ����Ʈ�� ��ȸ�ϸ鼭 ���� ���� ����� ���� �迭�� ĳ��
void traverse() {

	int count = 1;
	node_ptr temp;
	temp = board;

	while (1)
	{
		// ��ź�� ���� ���
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

// ���� ���带 ���
void printBoard() {

	int i;

	// ����� ��ȯ ����Ʈ�� ��ȸ
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