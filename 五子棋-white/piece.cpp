#include "piece.h"
// 分文件声明全局变量
extern bool is_exec_piece; // 执行下棋，当游戏结束后结束落棋子
// 初始化棋盘
void initBoard(Button* replay, Button*playback, Button* exit_play) {
	is_exec_piece = true; // 刷新可点
	FlushBatchDraw(); // 刷新指定区域的绘制缓存
	// 设置棋盘背景色
	setbkcolor(board_color);
	cleardevice(); // 清除设备信息
	// 设置棋盘线条
	setlinecolor(BLACK);
	for (int x = 0; x < call_count; x++)
		line(x*call_size + call_size, 
			call_size, 
			x * call_size + call_size, 
			boardX);
	for (int y = 0; y < call_count; y++)
		line(call_size,
			y * call_size + call_size,
			boardY,
			y * call_size + call_size);
	// 设置棋盘视觉点
	// 中心点为 8，8
	setfillcolor(BLACK);
	//fillcircle(240, 240, 3);
	int x = boardX_extend / 4;
	int y = boardY_extend / 4;
	for (int m = 1; m < 4; m++) 
		for(int n = 1; n < 4; n++)
			fillcircle(x * m, y * n, 3); // 中心点
	/////////初始化棋子坐标链表/////////////

	drawButton(replay); // 绘制按钮
	drawButton(playback); // 绘制按钮
	drawButton(exit_play); // 绘制按钮
	FlushBatchDraw();  // 刷新缓存

}
// 初始化节点链表
Piece* initPieceLink() {
	Piece* tmp = NULL;
	Piece* head = NULL;
	Piece* p = NULL;

	for (int x = 0; x < call_count; x++)
		for (int y = 0; y < call_count; y++) {
			tmp = (Piece*)malloc(sizeof(Piece));
			if (tmp != NULL) {
				tmp->x = x * call_size + call_size;
				tmp->y = y * call_size + call_size;
				tmp->seat = -1;
				tmp->next = NULL;
			}
			if (head == NULL)// 第一个节点赋值
			{
				head = tmp; // 设定头节点
				p = head; // 头节点赋值
				continue;
			}
			p->next = tmp; // 下一节点赋值
			p = p->next; // 更新当前节点指向
			//printf("x坐标>%d, y坐标>%d, 当前棋子状态>%d\n", p->x, p->y, p->seat);
		}
	return head; // 返回头节点
}
// 初始化回放节点链表
Piece* initPlayLinkNode() {
	Piece*tmp = (Piece*)malloc(sizeof(Piece));
	tmp->x = 0;
	tmp->y = 0;
	tmp->seat = -1;
	tmp->next = NULL;
	return tmp;
}
// 初始化数组
void initArray(Piece* piece_map[call_count][call_count]) {
	Piece* tmp;
	for (int i = 0; i < call_count; i++)
		for (int j = 0; j < call_count; j++) {
			tmp = (Piece*)malloc(sizeof(Piece));
			tmp->x = 0;
			tmp->y = 0;
			tmp->seat = -1;
			tmp->next = NULL;
			piece_map[i][j] = tmp;
		}
}
// 画棋子
int drawPiece(int piece_color, int x, int y) {
	if (piece_color == 0) {
		setfillcolor(WHITE);
		piece_color = 1;
	}
	else {
		setfillcolor(BLACK);
		piece_color = 0;
	}

	fillcircle(x, y, 12);
	return piece_color;
}
// 鼠标左击进行下棋
int leftClick(int piece_color, ExMessage mouse, Piece* piece, Piece* playback_piece, Piece* piece_map[call_count][call_count]) {
	// 下棋范围判断
	int x = round(round(mouse.x) / call_size) * call_size;
	int y = round(round(mouse.y) / call_size) * call_size;
	Piece* p = piece;
	Piece* tmp_p = playback_piece;
	// 遍历棋子单链表 查看指定坐标棋子是否被占用
	while (p) {
		if ((p->x == x) && (p->y == y) && (p->seat != -1))
			return piece_color; // 同一位置不处理
		// 未被占用，则进行落子
		if ((p->x == x) && (p->y == y) && (p->seat == -1)) {
			p->seat = piece_color;
			// 落子位置设置
			int i = x / call_size;
			int j = y / call_size;
			piece_map[i][j]->x = x;
			piece_map[i][j]->y = y;
			piece_map[i][j]->seat = piece_color;
			// 回放节点存放
			while (tmp_p) {
				if (tmp_p->next == NULL)
					break;
				tmp_p = tmp_p->next;
			}
			tmp_p->x = x;
			tmp_p->y = y;
			tmp_p->seat = piece_color;
			tmp_p->next = check_back_node(); // 增加一个节点
			// 画子
			piece_color = drawPiece(piece_color, x, y);
			// 输赢判断
			if (isWin(piece_map)) {// 判断输赢
				is_exec_piece = false;  //结束落棋子
			};
			return piece_color;
		}
		p = p->next;
	}
}
// 判断输赢
bool isWin(Piece *piece_map[call_count][call_count]) {
	int seat;
	for(int i=0;i<call_count;i++)
		for (int j = 0; j < call_count; j++) {
			if ((piece_map[i][j]->seat == 0) ||
				(piece_map[i][j]->seat == 1)) {
				seat = piece_map[i][j]->seat;
				/*判断思路：
				* 1.从遇到的第一个子为基准；
				* 2.向上，向下，向左，向右，四个水平方向；
				* 3.向斜左上，向斜右上，向斜左下，向斜右下，四个斜向；
				* 4.总共8个方向，判断是否有相同的子；
				*/
				// 向上 向下
				if ((seat == piece_map[i][j - 1]->seat) && // 向上一个坐标
					(seat == piece_map[i][j - 2]->seat) &&
					(seat == piece_map[i][j - 3]->seat) &&
					(seat == piece_map[i][j - 4]->seat)) {
					ifIsWho(seat);
					return true;
				}
				// 向左 向右
				if ((seat == piece_map[i - 1][j]->seat) && // 向上一个坐标
					(seat == piece_map[i - 2][j]->seat) &&
					(seat == piece_map[i - 3][j]->seat) &&
					(seat == piece_map[i - 4][j]->seat)) {
					ifIsWho(seat);
					return true;
				}
				// 斜右上 右下
				if ((seat == piece_map[i + 1][j + 1]->seat) && // 向上一个坐标
					(seat == piece_map[i + 2][j + 2]->seat) &&
					(seat == piece_map[i + 3][j + 3]->seat) &&
					(seat == piece_map[i + 4][j + 4]->seat)) {
					ifIsWho(seat);
					return true;
				}
				// 斜左上 左下
				if ((seat == piece_map[i - 1][j + 1]->seat) && // 向上一个坐标
					(seat == piece_map[i - 2][j + 2]->seat) &&
					(seat == piece_map[i - 3][j + 3]->seat) &&
					(seat == piece_map[i - 4][j + 4]->seat)) {
					ifIsWho(seat);
					return true;
				}
			}
		}
	return false;
}
// 判断谁赢 并打印字符串
void ifIsWho(int seat) {
	if (seat == 0) {
		char text[] = "白棋赢！";
		textPrintf(text);
	}
	else if (seat == 1) {
		char text[] = "黑棋赢！";
		textPrintf(text);
	}
}
// 向当前的回放链表中添加节点
Piece* check_back_node() {
	Piece* tmp = (Piece*)malloc(sizeof(Piece));
	assert(tmp);
	tmp->x = 0;
	tmp->y = 0;
	tmp->seat = -1;
	tmp->next = NULL;
	return tmp;
}
// 进行节点回放
void back_play_piece(Piece* playback_piece) {
	Piece* p = playback_piece;
	int x, y, color, tmp;
	is_exec_piece = false; // 不可点
	EndBatchDraw();
	Sleep(500);
	while (p!=NULL && p->seat != -1) {
		x = p->x;
		y = p->y;
		color = p->seat;
		tmp = drawPiece(color, x, y);
		Sleep(800);
		p = p->next;
	}
}
// 向屏幕中输出文本
void textPrintf(char text[50]) {
	settextcolor(RED); // 设置文字颜色
	setbkmode(TRANSPARENT); // 去掉文字背景
	settextstyle(35, 0, "楷体"); // 设置文字样式
	//outtextxy(boardX_extend /2, boardY_extend/2, text);
	outtextxy(10, 30, text);
}
// 输出单链表
void show_piece(Piece* piece) {
	Piece* p = piece;
	while (p) {
		printf("x坐标>%d, y坐标>%d, 当前棋子状态>%d\n", p->x, p->y, p->seat);
		p = p->next;
	}
}

// 创建按钮
Button* createButton(int x, int y,
	int w, int h,
	const char* str,
	COLORREF inColor,
	COLORREF outColor) {
	struct Button* pB = (struct Button*)malloc(sizeof(struct Button));
	assert(pB);
	pB->x = x;
	pB->y = y;
	pB->w = w;
	pB->h = h;
	pB->inColor = inColor;
	pB->outColor = outColor;
	pB->curColor = pB->outColor;
	int textLength = strlen(str) + 1; // +1 在字符串末尾有个/0
	pB->text = (char*)malloc(sizeof(char) * textLength);
	assert(pB->text);
	strcpy_s(pB->text, textLength, str); // 字符串拷贝
	return pB;
}
// 画按钮
void drawButton(Button* pB) {
	// 1.按钮就是个矩形
	setlinecolor(BLACK);
	setfillcolor(pB->curColor);
	// 指定矩形大小
	fillrectangle(pB->x, pB->y, pB->x + pB->w, pB->y + pB->h);
	// 画文字
	settextcolor(BLACK); // 设置文字颜色
	setbkmode(TRANSPARENT); // 去掉文字背景
	settextstyle(15, 0, "楷体"); // 设置文字样式
	// 文字如何居中
	// textwidth(str), textheight(str);
	int textw = textwidth(pB->text);  // 文字宽度
	int texth = textheight(pB->text); // 文字高度
	int xx = pB->x + (pB->w - textw) / 2;
	int yy = pB->y + (pB->h - texth) / 2;
	outtextxy(xx, yy, pB->text);
}

// 鼠标是否在按钮中
bool isInButton(Button* pB, ExMessage m) {
	if (m.x > pB->x && m.x < pB->x + pB->w &&
		m.y > pB->y && m.y < pB->y + pB->h) {
		pB->curColor = pB->inColor;
		return true;
	}
	pB->curColor = pB->outColor;
	return false;

}

// 鼠标点击
bool isClickButton(Button* pB, ExMessage m) {
	// WM_LBUTTONDOWN 左键按下消息
	if (isInButton(pB, m) && m.message == WM_LBUTTONDOWN) {
		return true;
	}
	return false;
}
// 销毁链表
void deleteLink(Piece* link) {
	Piece* tmp = link;
	Piece* next;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
// 销毁数组
void deleteArray(Piece* piece_map[call_count][call_count]) {
	for (int i = 0; i < call_count; i++) {
		for (int j = 0; j < call_count; j++) {
			free(piece_map[i][j]);
		}
	}
}