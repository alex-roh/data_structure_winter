#pragma once

#pragma once

#define NONE 0         // 아무것도 없는 노드
#define BOMB -1         // 폭탄의 고유 번호
#define PLAYER1 1       // 플레이어 1의 고유 번호
#define PLAYER2 2       // 플레이어 2의 고유 번호
#define TWOGETHER 3     // 플레이어 1과 플레이어 2가 같은 노드에 있을 때의 고유 번 
#define SIZE 12         // 노드의 개수
#define PLAYERS 2       // 플레이어의 수
#define BOMBS 3         // 폭탄의 개수
#define LIFE 3          // 라이프 개수
#define MAX 80          // 문자열의 최대호 길이
#define INTROMESSAGE 1  // 인트로 메세지
#define STATUSMESSAGE 2 // 상태 메세지
#define FORWARD 1       // 정방향 이동
#define BACKWARD -1      // 역방향 이동
#define FILEPATH "data.txt"  // 게임 데이터를 저장할 텍스트 파일

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

