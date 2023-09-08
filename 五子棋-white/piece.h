#pragma once
#include <graphics.h>
#include <stdio.h>
#define call_count 15 // ��ʾ������ ��λ����
#define call_size 30  // ��ʾÿ�����ӵĳ� ��λ����
#define board_extend call_size // ����������չ�������С
#define boardX (call_count * call_size) // ���������С
#define boardY (call_count * call_size) // ���������С
#define boardX_extend (call_count * call_size + board_extend) // ������չ��Ĵ�С
#define boardY_extend (call_count * call_size + board_extend) // ������չ��Ĵ�С


void initBoard(int boardPoint[call_count][call_count]); // ��ʼ������
int drawPiece(int pc, int x, int y); // ������
int leftClick(int pc, ExMessage mouse, int boardPoint[call_count][call_count]); // ������