#include "main.h"


// 커서 감추기
void cursor_view()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 커서 특정 위치로 이동
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// char 출력 (되도록 print_str로 찍기)
void print_char(int x, int y, char c) {
	gotoxy(y, x);
	printf("%c", c);
}

// str 출력
void print_str(int x, int y, char* s) {
	gotoxy(y, x);
	printf("%s", s);
}

void print_num(int x, int y, int n) {
	gotoxy(y, x);
	printf("%d", n);
}

// str 추가 출력
void print_str_int_format(int x, int y, char* s, int d) {
	gotoxy(y, x);
	printf(s, d);
}

// str 가운데 출력
void print_str_row(int x, char* s) {
	int i_y = (WIDTH + 2 - strlen(s)) / 2;
	print_str(x, i_y, s);
}

// str 그룹 중앙 출력
void print_str_cen(char(*s)[15], int count) {
	int i_x = (MAPHEIGHT - count) / 2;
	int i_y = (WIDTH - 15) / 2;
	for (int i = 0; i < count; i++) {
		int c_x = i_x + 2 * i;
		print_str(c_x, i_y, s + i, COLOR_RESET);
	}
}

// line 지우기
void erase_line(int x) {
	char erase[23] = "";

	for (int i = 0; i < 22; i++) {
		strcat(erase, " ");
	}
	print_str_row(x, erase);
}

// 전체 지우기
void erase_all() {
	printf("%s", COLOR_RESET);
	system("cls");
}

// 맵 생성
void generate_map() {
	
	for (int i = 0; i < MAPHEIGHT + 2; i++) {
		for (int j = 0; j < WIDTH + 2; j++) {
			if (i == 0 || i == MAPHEIGHT + 1 || j == 0 || j == WIDTH + 1) {
				map[i][j] = 1;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
	
}

/// map 출력
void print_all() {
	printf("%s", COLOR_RESET);
	for (int i = 0; i < MAPHEIGHT + 2; i++) {
		for (int j = 0; j < WIDTH + 2; j++) {
			char c = map[i][j];
			if (c == 1) {
				print_str(i, j, white);
			}
			else {
				print_str(i, j, blank);
			}
		}
	}
}

