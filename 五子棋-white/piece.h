#pragma once
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>
#include <assert.h>
#include <windows.h>

#define call_count 15 // 表示格子数 单位像素
#define call_size 30  // 表示每个格子的长 单位像素
#define board_extend call_size // 棋盘向外扩展的区域大小
#define boardX (call_count * call_size) // 棋盘区域大小
#define boardY (call_count * call_size) // 棋盘区域大小
#define boardX_extend (call_count * call_size + board_extend) // 棋盘扩展后的大小
#define boardY_extend (call_count * call_size + board_extend*3) // 棋盘扩展后的大小
#define board_color RGB(248, 227, 200) // 棋盘颜色
typedef struct Piece { // 棋子结构体
	int x; // 当前棋子的x坐标
	int y; // 当前棋子的y坐标
	int seat; // 当前放的棋子 -1 未放棋子，0 白棋子 1 黑棋子
	struct Piece* next; // 指向下一个节点
};

typedef struct Button { // 按钮结构体
	int y;
	int x;
	int w;
	int h;
	COLORREF curColor; // 按钮当前颜色
	COLORREF inColor; // 鼠标在按钮里面的颜色
	COLORREF outColor; // 鼠标不在按钮中的颜色
	char* text;
};

void initBoard(Button* replay, Button* playback, Button* exit_play); // 初始化棋盘
Piece* initPieceLink(); // 初始化坐标节点链表
Piece* initPlayLinkNode();// 初始化回放节点链表
void initArray(Piece* piece_map[call_count][call_count]); // 初始化数组
int drawPiece(int piece_color, int x, int y); // 画棋子
int leftClick(int piece_color, ExMessage mouse, Piece* piece, Piece* playback_piece, Piece *piece_map[call_count][call_count]); // 左点击布棋
bool isWin(Piece* piece_map[call_count][call_count]); // 判断输赢
void textPrintf(char text[50]); // 向屏幕中输入文本
void ifIsWho(int seat); // 判断谁赢
Piece *check_back_node(); // 向当前的回放链表中添加节点
void back_play_piece(Piece* playback_piece);// 进行节点回放
Button* createButton(int x, int y,
	int w, int h,
	const char* str,
	COLORREF inColor,
	COLORREF outColor); // 创建按钮
void drawButton(Button* pB); // 绘制按钮
bool isClickButton(Button* pB, ExMessage m); // 鼠标点击按钮
void deleteLink(Piece* link);// 销毁链表
void deleteArray(Piece* piece_map[call_count][call_count]); // 释放数组