#pragma once

#pragma once

#define NONE 0         // �ƹ��͵� ���� ���
#define BOMB -1         // ��ź�� ���� ��ȣ
#define PLAYER1 1       // �÷��̾� 1�� ���� ��ȣ
#define PLAYER2 2       // �÷��̾� 2�� ���� ��ȣ
#define TWOGETHER 3     // �÷��̾� 1�� �÷��̾� 2�� ���� ��忡 ���� ���� ���� �� 
#define SIZE 12         // ����� ����
#define PLAYERS 2       // �÷��̾��� ��
#define BOMBS 3         // ��ź�� ����
#define LIFE 3          // ������ ����
#define MAX 80          // ���ڿ��� �ִ�ȣ ����
#define INTROMESSAGE 1  // ��Ʈ�� �޼���
#define STATUSMESSAGE 2 // ���� �޼���
#define FORWARD 1       // ������ �̵�
#define BACKWARD -1      // ������ �̵�
#define FILEPATH "data.txt"  // ���� �����͸� ������ �ؽ�Ʈ ����

typedef struct node* node_ptr;

node_ptr initialize();
void traverse();
void printBoard();
void updataData(int count);
void game_logic();
void setBombs(node_ptr list);
void roll_the_dice(int* dice1, int* dice2);
void terminate(node_ptr list);
void printMessage(int type);
void move_player(int player, int movement);
void debug();
void check_failure(int player);

