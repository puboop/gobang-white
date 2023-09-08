#pragma once
#include <graphics.h>
#include <stdio.h>
#define call_count 15 // 表示格子数 单位像素
#define call_size 30  // 表示每个格子的长 单位像素
#define board_extend call_size // 棋盘向外扩展的区域大小
#define boardX (call_count * call_size) // 棋盘区域大小
#define boardY (call_count * call_size) // 棋盘区域大小
#define boardX_extend (call_count * call_size + board_extend) // 棋盘扩展后的大小
#define boardY_extend (call_count * call_size + board_extend) // 棋盘扩展后的大小


void initBoard(int boardPoint[call_count][call_count]); // 初始化棋盘
int drawPiece(int pc, int x, int y); // 画棋子
int leftClick(int pc, ExMessage mouse, int boardPoint[call_count][call_count]); // 鼠标左击