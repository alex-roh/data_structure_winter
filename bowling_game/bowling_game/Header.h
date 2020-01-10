#pragma once

#define MAX_FRAME 10
#define STRIKE 0
#define SPARE 1
#define NONE 2

typedef struct frame* frame_ptr;
typedef struct score score;

void debug();
void initialize();
void readFromInput();
void inputError();
