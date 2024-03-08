#include "menu_module.h"
#include "page_difficulty.h"

char* difficulty_menus[] = {
		"1. Advance",
		"2. Challenge",
		"3. Impossible",
		"4. Exit"
};

void difficulty_page_menu_select(int cur_menu_selected) {

	if (cur_menu_selected == 3) {
		cur_menu_selected = 0;
		set_cur_step(init_step);
		return;
	}

	difficulty = cur_menu_selected + 1;
	set_cur_step(tetris_step);
}