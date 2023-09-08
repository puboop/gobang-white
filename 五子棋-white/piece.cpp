#include "piece.h"
// ��ʼ������
void initBoard(int boardPoint[call_count][call_count]) { 
	initgraph(boardX_extend, boardY_extend); // ���崰�ڴ�С
	FlushBatchDraw(); // ˢ��ָ������Ļ��ƻ���
	// �������̱���ɫ
	setbkcolor(RGB(248, 227, 200));
	cleardevice(); // ����豸��Ϣ
	// ������������
	setlinecolor(BLACK);
	for (int x = 0; x < call_count; x++)
		line(x*call_size + board_extend, 
			board_extend, 
			x * call_size + board_extend, 
			boardX);
	for (int y = 0; y < call_count; y++)
		line(board_extend,
			y * call_size + board_extend,
			boardY,
			y * call_size + board_extend);
	// ���������Ӿ���
	// ���ĵ�Ϊ 8��8
	setfillcolor(BLACK);
	//fillcircle(240, 240, 3);
	int x = boardX_extend / 4;
	int y = boardY_extend / 4;
	for (int m = 1; m < 4; m++) 
		for(int n = 1; n < 4; n++)
			fillcircle(x * m, y * n, 3); // ���ĵ�
	// ��ʼ����������
	for (int x = 0; x < call_count; x++)
		for (int y = 0; y < call_count; y++)
			boardPoint[x][y] = 0;
}
// ������
int drawPiece(int pc, int x, int y) { 
	if (pc == 0) {
		setfillcolor(WHITE);
		pc = 1;
	}
	else {
		setfillcolor(BLACK);
		pc = 0;
	}
	fillcircle(x, y, 12);
	return pc;
}
// ������
int leftClick(int pc, ExMessage mouse, int boardPoint[call_count][call_count]) {
	return drawPiece(pc, mouse.x, mouse.y);
	/*for (int x=0;x<call_count;x++)
		for (int y = 0; y < call_count; y++) {

		}*/
}