#include "piece.h"

int piece_color = 0; // 0 为白色，1为黑色
extern bool is_exec_piece = true; // 执行下棋，当游戏结束后结束落棋子
Piece* piece_map[call_count][call_count]; // 初始化出地图一样的结构体数组

int main() {
	// EX_SHOWCONSOLE | EX_NOCLOSE 显示控制台，并且禁用关闭窗口
	HWND  hwnd = initgraph(boardX_extend, boardY_extend, EX_NOCLOSE); // 定义窗口大小
	HICON hIcon = (HICON)LoadImage(NULL, "盒子.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE); // 加载图标文件
	//SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon); // 设置任务栏图标 同步进行
	PostMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon); // 设置任务栏图标 异步进行
	SetWindowText(hwnd, "white666"); // 设置窗口标题
	// 创建按钮
	Button* replay = createButton(30, boardX + 30, 120, 40, "重玩", RGB(248, 227, 200), board_color);
	Button* playback = createButton(30 + 120 + 30, boardX + 30, 120, 40, "回放", RGB(248, 227, 200), board_color);
	Button* exit_play = createButton(30 + 120 + 120 + 30 + 30, boardX + 30, 120, 40, "退出游戏", RGB(248, 227, 200), board_color);

	initBoard(replay, playback, exit_play); // 初始化棋盘 得到一个头节点
	Piece* piece;
	piece = initPieceLink();// 初始化节点链表
	Piece* playback_piece;
	playback_piece = initPlayLinkNode();
	initArray(piece_map); // 初始化数组

	ExMessage mouse;// 声明鼠标消息结构体
	while (1) {
		BeginBatchDraw();
		getmessage(&mouse, EX_MOUSE); // 获取鼠标消息
		if (mouse.message == EX_WINDOW) { // 关闭窗口
			if (MessageBox(NULL, "确定要退出吗？", "提示", MB_YESNO) == IDYES) {
				closegraph();
			}
		}
		if (is_exec_piece && mouse.message == WM_LBUTTONDOWN) {// 是否是左击消息
			piece_color = leftClick(piece_color, mouse, piece, playback_piece, piece_map);
		}
		if (isClickButton(replay, mouse)) {// 点击按钮消息
			deleteLink(piece);// 销毁链表
			deleteLink(playback_piece);// 销毁链表
			deleteArray(piece_map); // 释放结构体数组

			initBoard(replay, playback, exit_play); // 初始化棋盘 得到一个头节点
			piece = initPieceLink();// 初始化节点链表
			playback_piece = initPlayLinkNode();
			initArray(piece_map); // 初始化数组
			piece_color = 0;
		}
		if (isClickButton(playback, mouse)) {// 点击按钮消息
			initBoard(replay, playback, exit_play); // 初始化棋盘 得到一个头节点
			back_play_piece(playback_piece); // 回放处理
		}
		if (isClickButton(exit_play, mouse)) {// 点击按钮消息
			deleteLink(piece);// 销毁链表
			deleteLink(playback_piece);// 销毁链表
			deleteArray(piece_map); // 释放结构体数组
			break;
		}
		FlushBatchDraw();  // 刷新缓存
	}
	EndBatchDraw();
	closegraph();
	//////// 测试用例 ///////////
	//initArray(piece_map);
	//for (int i = 0; i < call_count; i++)
	//	for (int j = 0; j < call_count; j++)
	//		printf("x>%d, y>%d, seat>%d\n", piece_map[i][j]);
	//initgraph(400, 400);
	//setbkcolor(RGB(248, 227, 200));
	//cleardevice();
	//settextcolor(RED); // 设置文字颜色
	//setbkmode(TRANSPARENT); // 去掉文字背景
	//settextstyle(35, 0, "楷体"); // 设置文字样式
	//char text[] = "白棋赢！";
	//outtextxy(10, 20, text);
	//while (1);
	//system("pause");
	///////////////////////////////
	return 0;
}