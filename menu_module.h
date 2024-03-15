#include "main.h"
#define TITLE_X 4
#define STR_MAX_LEN 16

#ifndef __menu_define

	typedef struct {
		// 현재 선택 메뉴
		int cur_selected;
		// 메뉴 개수
		int menu_cnt;
		// 현재 페이지 스텝
		page_step cur_step;
		// 제목
		char* title;
		// 메뉴 목록
		char** menus;
		// 메뉴 선택시 액션
		void (*menu_select) (int cur_select);
	} menu;

#define __menu_define 1
#endif

void initialize_page_map(menu* cur_menu);
void execute_menu(menu* cur_menu);

menu* new_Menu(
	int menu_cnt,
	page_step cur_step,
	char* title,
	char** menus,
	void (*menu_select) (int cur_select)
);