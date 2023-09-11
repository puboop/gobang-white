#include "piece.h"

int piece_color = 0; // 0 Ϊ��ɫ��1Ϊ��ɫ
extern bool is_exec_piece = true; // ִ�����壬����Ϸ���������������
Piece* piece_map[call_count][call_count]; // ��ʼ������ͼһ���Ľṹ������

int main() {
	// EX_SHOWCONSOLE | EX_NOCLOSE ��ʾ����̨�����ҽ��ùرմ���
	HWND  hwnd = initgraph(boardX_extend, boardY_extend, EX_NOCLOSE); // ���崰�ڴ�С
	HICON hIcon = (HICON)LoadImage(NULL, "����.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE); // ����ͼ���ļ�
	//SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon); // ����������ͼ�� ͬ������
	PostMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon); // ����������ͼ�� �첽����
	SetWindowText(hwnd, "white666"); // ���ô��ڱ���
	// ������ť
	Button* replay = createButton(30, boardX + 30, 120, 40, "����", RGB(248, 227, 200), board_color);
	Button* playback = createButton(30 + 120 + 30, boardX + 30, 120, 40, "�ط�", RGB(248, 227, 200), board_color);
	Button* exit_play = createButton(30 + 120 + 120 + 30 + 30, boardX + 30, 120, 40, "�˳���Ϸ", RGB(248, 227, 200), board_color);

	initBoard(replay, playback, exit_play); // ��ʼ������ �õ�һ��ͷ�ڵ�
	Piece* piece;
	piece = initPieceLink();// ��ʼ���ڵ�����
	Piece* playback_piece;
	playback_piece = initPlayLinkNode();
	initArray(piece_map); // ��ʼ������

	ExMessage mouse;// ���������Ϣ�ṹ��
	while (1) {
		BeginBatchDraw();
		getmessage(&mouse, EX_MOUSE); // ��ȡ�����Ϣ
		if (mouse.message == EX_WINDOW) { // �رմ���
			if (MessageBox(NULL, "ȷ��Ҫ�˳���", "��ʾ", MB_YESNO) == IDYES) {
				closegraph();
			}
		}
		if (is_exec_piece && mouse.message == WM_LBUTTONDOWN) {// �Ƿ��������Ϣ
			piece_color = leftClick(piece_color, mouse, piece, playback_piece, piece_map);
		}
		if (isClickButton(replay, mouse)) {// �����ť��Ϣ
			deleteLink(piece);// ��������
			deleteLink(playback_piece);// ��������
			deleteArray(piece_map); // �ͷŽṹ������

			initBoard(replay, playback, exit_play); // ��ʼ������ �õ�һ��ͷ�ڵ�
			piece = initPieceLink();// ��ʼ���ڵ�����
			playback_piece = initPlayLinkNode();
			initArray(piece_map); // ��ʼ������
			piece_color = 0;
		}
		if (isClickButton(playback, mouse)) {// �����ť��Ϣ
			initBoard(replay, playback, exit_play); // ��ʼ������ �õ�һ��ͷ�ڵ�
			back_play_piece(playback_piece); // �طŴ���
		}
		if (isClickButton(exit_play, mouse)) {// �����ť��Ϣ
			deleteLink(piece);// ��������
			deleteLink(playback_piece);// ��������
			deleteArray(piece_map); // �ͷŽṹ������
			break;
		}
		FlushBatchDraw();  // ˢ�»���
	}
	EndBatchDraw();
	closegraph();
	//////// �������� ///////////
	//initArray(piece_map);
	//for (int i = 0; i < call_count; i++)
	//	for (int j = 0; j < call_count; j++)
	//		printf("x>%d, y>%d, seat>%d\n", piece_map[i][j]);
	//initgraph(400, 400);
	//setbkcolor(RGB(248, 227, 200));
	//cleardevice();
	//settextcolor(RED); // ����������ɫ
	//setbkmode(TRANSPARENT); // ȥ�����ֱ���
	//settextstyle(35, 0, "����"); // ����������ʽ
	//char text[] = "����Ӯ��";
	//outtextxy(10, 20, text);
	//while (1);
	//system("pause");
	///////////////////////////////
	return 0;
}