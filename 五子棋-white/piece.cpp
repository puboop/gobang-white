#include "piece.h"
// ���ļ�����ȫ�ֱ���
extern bool is_exec_piece; // ִ�����壬����Ϸ���������������
// ��ʼ������
void initBoard(Button* replay, Button*playback, Button* exit_play) {
	is_exec_piece = true; // ˢ�¿ɵ�
	FlushBatchDraw(); // ˢ��ָ������Ļ��ƻ���
	// �������̱���ɫ
	setbkcolor(board_color);
	cleardevice(); // ����豸��Ϣ
	// ������������
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
	// ���������Ӿ���
	// ���ĵ�Ϊ 8��8
	setfillcolor(BLACK);
	//fillcircle(240, 240, 3);
	int x = boardX_extend / 4;
	int y = boardY_extend / 4;
	for (int m = 1; m < 4; m++) 
		for(int n = 1; n < 4; n++)
			fillcircle(x * m, y * n, 3); // ���ĵ�
	/////////��ʼ��������������/////////////

	drawButton(replay); // ���ư�ť
	drawButton(playback); // ���ư�ť
	drawButton(exit_play); // ���ư�ť
	FlushBatchDraw();  // ˢ�»���

}
// ��ʼ���ڵ�����
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
			if (head == NULL)// ��һ���ڵ㸳ֵ
			{
				head = tmp; // �趨ͷ�ڵ�
				p = head; // ͷ�ڵ㸳ֵ
				continue;
			}
			p->next = tmp; // ��һ�ڵ㸳ֵ
			p = p->next; // ���µ�ǰ�ڵ�ָ��
			//printf("x����>%d, y����>%d, ��ǰ����״̬>%d\n", p->x, p->y, p->seat);
		}
	return head; // ����ͷ�ڵ�
}
// ��ʼ���طŽڵ�����
Piece* initPlayLinkNode() {
	Piece*tmp = (Piece*)malloc(sizeof(Piece));
	tmp->x = 0;
	tmp->y = 0;
	tmp->seat = -1;
	tmp->next = NULL;
	return tmp;
}
// ��ʼ������
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
// ������
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
// ��������������
int leftClick(int piece_color, ExMessage mouse, Piece* piece, Piece* playback_piece, Piece* piece_map[call_count][call_count]) {
	// ���巶Χ�ж�
	int x = round(round(mouse.x) / call_size) * call_size;
	int y = round(round(mouse.y) / call_size) * call_size;
	Piece* p = piece;
	Piece* tmp_p = playback_piece;
	// �������ӵ����� �鿴ָ�����������Ƿ�ռ��
	while (p) {
		if ((p->x == x) && (p->y == y) && (p->seat != -1))
			return piece_color; // ͬһλ�ò�����
		// δ��ռ�ã����������
		if ((p->x == x) && (p->y == y) && (p->seat == -1)) {
			p->seat = piece_color;
			// ����λ������
			int i = x / call_size;
			int j = y / call_size;
			piece_map[i][j]->x = x;
			piece_map[i][j]->y = y;
			piece_map[i][j]->seat = piece_color;
			// �طŽڵ���
			while (tmp_p) {
				if (tmp_p->next == NULL)
					break;
				tmp_p = tmp_p->next;
			}
			tmp_p->x = x;
			tmp_p->y = y;
			tmp_p->seat = piece_color;
			tmp_p->next = check_back_node(); // ����һ���ڵ�
			// ����
			piece_color = drawPiece(piece_color, x, y);
			// ��Ӯ�ж�
			if (isWin(piece_map)) {// �ж���Ӯ
				is_exec_piece = false;  //����������
			};
			return piece_color;
		}
		p = p->next;
	}
}
// �ж���Ӯ
bool isWin(Piece *piece_map[call_count][call_count]) {
	int seat;
	for(int i=0;i<call_count;i++)
		for (int j = 0; j < call_count; j++) {
			if ((piece_map[i][j]->seat == 0) ||
				(piece_map[i][j]->seat == 1)) {
				seat = piece_map[i][j]->seat;
				/*�ж�˼·��
				* 1.�������ĵ�һ����Ϊ��׼��
				* 2.���ϣ����£��������ң��ĸ�ˮƽ����
				* 3.��б���ϣ���б���ϣ���б���£���б���£��ĸ�б��
				* 4.�ܹ�8�������ж��Ƿ�����ͬ���ӣ�
				*/
				// ���� ����
				if ((seat == piece_map[i][j - 1]->seat) && // ����һ������
					(seat == piece_map[i][j - 2]->seat) &&
					(seat == piece_map[i][j - 3]->seat) &&
					(seat == piece_map[i][j - 4]->seat)) {
					ifIsWho(seat);
					return true;
				}
				// ���� ����
				if ((seat == piece_map[i - 1][j]->seat) && // ����һ������
					(seat == piece_map[i - 2][j]->seat) &&
					(seat == piece_map[i - 3][j]->seat) &&
					(seat == piece_map[i - 4][j]->seat)) {
					ifIsWho(seat);
					return true;
				}
				// б���� ����
				if ((seat == piece_map[i + 1][j + 1]->seat) && // ����һ������
					(seat == piece_map[i + 2][j + 2]->seat) &&
					(seat == piece_map[i + 3][j + 3]->seat) &&
					(seat == piece_map[i + 4][j + 4]->seat)) {
					ifIsWho(seat);
					return true;
				}
				// б���� ����
				if ((seat == piece_map[i - 1][j + 1]->seat) && // ����һ������
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
// �ж�˭Ӯ ����ӡ�ַ���
void ifIsWho(int seat) {
	if (seat == 0) {
		char text[] = "����Ӯ��";
		textPrintf(text);
	}
	else if (seat == 1) {
		char text[] = "����Ӯ��";
		textPrintf(text);
	}
}
// ��ǰ�Ļط���������ӽڵ�
Piece* check_back_node() {
	Piece* tmp = (Piece*)malloc(sizeof(Piece));
	assert(tmp);
	tmp->x = 0;
	tmp->y = 0;
	tmp->seat = -1;
	tmp->next = NULL;
	return tmp;
}
// ���нڵ�ط�
void back_play_piece(Piece* playback_piece) {
	Piece* p = playback_piece;
	int x, y, color, tmp;
	is_exec_piece = false; // ���ɵ�
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
// ����Ļ������ı�
void textPrintf(char text[50]) {
	settextcolor(RED); // ����������ɫ
	setbkmode(TRANSPARENT); // ȥ�����ֱ���
	settextstyle(35, 0, "����"); // ����������ʽ
	//outtextxy(boardX_extend /2, boardY_extend/2, text);
	outtextxy(10, 30, text);
}
// ���������
void show_piece(Piece* piece) {
	Piece* p = piece;
	while (p) {
		printf("x����>%d, y����>%d, ��ǰ����״̬>%d\n", p->x, p->y, p->seat);
		p = p->next;
	}
}

// ������ť
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
	int textLength = strlen(str) + 1; // +1 ���ַ���ĩβ�и�/0
	pB->text = (char*)malloc(sizeof(char) * textLength);
	assert(pB->text);
	strcpy_s(pB->text, textLength, str); // �ַ�������
	return pB;
}
// ����ť
void drawButton(Button* pB) {
	// 1.��ť���Ǹ�����
	setlinecolor(BLACK);
	setfillcolor(pB->curColor);
	// ָ�����δ�С
	fillrectangle(pB->x, pB->y, pB->x + pB->w, pB->y + pB->h);
	// ������
	settextcolor(BLACK); // ����������ɫ
	setbkmode(TRANSPARENT); // ȥ�����ֱ���
	settextstyle(15, 0, "����"); // ����������ʽ
	// ������ξ���
	// textwidth(str), textheight(str);
	int textw = textwidth(pB->text);  // ���ֿ��
	int texth = textheight(pB->text); // ���ָ߶�
	int xx = pB->x + (pB->w - textw) / 2;
	int yy = pB->y + (pB->h - texth) / 2;
	outtextxy(xx, yy, pB->text);
}

// ����Ƿ��ڰ�ť��
bool isInButton(Button* pB, ExMessage m) {
	if (m.x > pB->x && m.x < pB->x + pB->w &&
		m.y > pB->y && m.y < pB->y + pB->h) {
		pB->curColor = pB->inColor;
		return true;
	}
	pB->curColor = pB->outColor;
	return false;

}

// �����
bool isClickButton(Button* pB, ExMessage m) {
	// WM_LBUTTONDOWN ���������Ϣ
	if (isInButton(pB, m) && m.message == WM_LBUTTONDOWN) {
		return true;
	}
	return false;
}
// ��������
void deleteLink(Piece* link) {
	Piece* tmp = link;
	Piece* next;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
// ��������
void deleteArray(Piece* piece_map[call_count][call_count]) {
	for (int i = 0; i < call_count; i++) {
		for (int j = 0; j < call_count; j++) {
			free(piece_map[i][j]);
		}
	}
}