#include "piece.h"
// 初始化棋盘
void initBoard(int boardPoint[call_count][call_count]) { 
	initgraph(boardX_extend, boardY_extend); // 定义窗口大小
	FlushBatchDraw(); // 刷新指定区域的绘制缓存
	// 设置棋盘背景色
	setbkcolor(RGB(248, 227, 200));
	cleardevice(); // 清除设备信息
	// 设置棋盘线条
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
	// 设置棋盘视觉点
	// 中心点为 8，8
	setfillcolor(BLACK);
	//fillcircle(240, 240, 3);
	int x = boardX_extend / 4;
	int y = boardY_extend / 4;
	for (int m = 1; m < 4; m++) 
		for(int n = 1; n < 4; n++)
			fillcircle(x * m, y * n, 3); // 中心点
	// 初始化坐标数组
	for (int x = 0; x < call_count; x++)
		for (int y = 0; y < call_count; y++)
			boardPoint[x][y] = 0;
}
// 画棋子
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
// 鼠标左击
int leftClick(int pc, ExMessage mouse, int boardPoint[call_count][call_count]) {
	return drawPiece(pc, mouse.x, mouse.y);
	/*for (int x=0;x<call_count;x++)
		for (int y = 0; y < call_count; y++) {

		}*/
}