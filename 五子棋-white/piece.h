#pragma once
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>
#include <assert.h>
#include <windows.h>

#define call_count 15 // ��ʾ������ ��λ����
#define call_size 30  // ��ʾÿ�����ӵĳ� ��λ����
#define board_extend call_size // ����������չ�������С
#define boardX (call_count * call_size) // ���������С
#define boardY (call_count * call_size) // ���������С
#define boardX_extend (call_count * call_size + board_extend) // ������չ��Ĵ�С
#define boardY_extend (call_count * call_size + board_extend*3) // ������չ��Ĵ�С
#define board_color RGB(248, 227, 200) // ������ɫ
typedef struct Piece { // ���ӽṹ��
	int x; // ��ǰ���ӵ�x����
	int y; // ��ǰ���ӵ�y����
	int seat; // ��ǰ�ŵ����� -1 δ�����ӣ�0 ������ 1 ������
	struct Piece* next; // ָ����һ���ڵ�
};

typedef struct Button { // ��ť�ṹ��
	int y;
	int x;
	int w;
	int h;
	COLORREF curColor; // ��ť��ǰ��ɫ
	COLORREF inColor; // ����ڰ�ť�������ɫ
	COLORREF outColor; // ��겻�ڰ�ť�е���ɫ
	char* text;
};

void initBoard(Button* replay, Button* playback, Button* exit_play); // ��ʼ������
Piece* initPieceLink(); // ��ʼ������ڵ�����
Piece* initPlayLinkNode();// ��ʼ���طŽڵ�����
void initArray(Piece* piece_map[call_count][call_count]); // ��ʼ������
int drawPiece(int piece_color, int x, int y); // ������
int leftClick(int piece_color, ExMessage mouse, Piece* piece, Piece* playback_piece, Piece *piece_map[call_count][call_count]); // ��������
bool isWin(Piece* piece_map[call_count][call_count]); // �ж���Ӯ
void textPrintf(char text[50]); // ����Ļ�������ı�
void ifIsWho(int seat); // �ж�˭Ӯ
Piece *check_back_node(); // ��ǰ�Ļط���������ӽڵ�
void back_play_piece(Piece* playback_piece);// ���нڵ�ط�
Button* createButton(int x, int y,
	int w, int h,
	const char* str,
	COLORREF inColor,
	COLORREF outColor); // ������ť
void drawButton(Button* pB); // ���ư�ť
bool isClickButton(Button* pB, ExMessage m); // �������ť
void deleteLink(Piece* link);// ��������
void deleteArray(Piece* piece_map[call_count][call_count]); // �ͷ�����