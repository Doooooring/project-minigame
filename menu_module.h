#include "main.h"
#define TITLE_X 4
#define STR_MAX_LEN 16

#ifndef __menu_define
typedef struct {
	int cur_selected;
	int menu_cnt;
	page_step cur_step;
	char* title;
	char** menus;
	void (*menu_select) (int cur_select);
} menu;
#define __menu_define 1
#endif

void execute_menu(menu* cur_menu);
menu* new_Menu(
	int menu_cnt,
	page_step cur_step,
	char* title,
	char** menus,
	void (*menu_select) (int cur_select)
);