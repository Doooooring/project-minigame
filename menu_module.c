#include "menu_module.h"

menu* new_Menu(
	int menu_cnt,
	page_step cur_step,
	char* title,
	char** menus,
	void (*menu_select) (int cur_select)
) {

	menu* menu_ptr = (menu*)malloc(sizeof(menu));

	if (menu_ptr == NULL) return;

	menu_ptr->cur_selected = 0;
	menu_ptr->menu_cnt = menu_cnt;
	menu_ptr->cur_step = cur_step;
	menu_ptr->title = title;
	menu_ptr->menus = menus;
	menu_ptr->menu_select = menu_select;

	return menu_ptr;
}

void menu_select_up(menu* cur_menu) {
	if (cur_menu->cur_selected == 0) return;
	cur_menu->cur_selected--;
}

void menu_select_down(menu* cur_menu) {
	if (cur_menu->cur_selected + 1 == cur_menu->menu_cnt) return;
	cur_menu->cur_selected++;
}

void menu_selected(menu* cur_menu) {
	cur_menu->menu_select(cur_menu->cur_selected);
}

bool get_user_menu_input(menu* cur_menu) {
	int input;
	input = _getch();

	switch (input) {
	case (ARROW_DOWN):
	case (ARROW_RIGHT):
		menu_select_down(cur_menu);
		break;
	case (ARROW_UP):
	case (ARROW_LEFT):
		menu_select_up(cur_menu);
		break;
	case (SPACEBAR):
		menu_selected(cur_menu);
		return false;
	}
	return true;
}

void print_menu_title(menu* cur_menu) {
	print_str_row(TITLE_X, cur_menu->title);
}

void set_cur_page(menu* cur_menu) {
	int title_len = strlen(cur_menu->title);
	int title_start_y = (WIDTH - title_len) / 2;

	for (int i = 0; i < title_len + 1; i++) {
		map[TITLE_X][title_start_y + i] = 1;
	}

	int menu_start_x = (MAPHEIGHT - 2 * cur_menu->menu_cnt) / 2;
	int menu_start_y = (WIDTH - STR_MAX_LEN) / 2;

	for (int i = 0; i < 4; i++) {
		char cur_str_len = strlen((cur_menu->menus)[i]);

		for (int j = 0; j < cur_str_len; j++) {
			map[menu_start_x + 2 * i][menu_start_y + j] = 1;
		}
	}
}

bool print_menu(menu* cur_menu) {

	if (is_cursor_using) return false;

	is_cursor_using = true;

	int menu_start_x = (MAPHEIGHT - 2 * cur_menu->menu_cnt) / 2;
	int menu_start_y = (WIDTH - STR_MAX_LEN) / 2;

	for (int i = 0; i < cur_menu->menu_cnt; i++) {

		char* cur = (cur_menu->menus)[i];

		if (i == cur_menu->cur_selected) {
			print_str(menu_start_x + 2 * i, menu_start_y, COLOR_RED);
			print_str(menu_start_x + 2 * i, menu_start_y, cur);
			printf("%s", COLOR_RESET);
		}
		else {
			print_str(menu_start_x + 2 * i, menu_start_y, COLOR_RESET);
			print_str(menu_start_x + 2 * i, menu_start_y, cur);
		}

	}

	is_cursor_using = false;
	return true;
}

void execute_menu(menu* cur_menu) {

	print_menu_title(cur_menu);

	while (1) {
		while (!print_menu(cur_menu)) {
			Sleep(10);
		}

		if (_kbhit()) {
			get_user_menu_input(cur_menu);
		}

		if (cur_step != cur_menu->cur_step) {
			free(cur_menu);
			break;
		};
		Sleep(50);
	}
}
