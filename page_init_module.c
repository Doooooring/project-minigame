#include "page_init.h"

char* init_menus[3] = {
		"1. Game Start",
		"2. Rank",
		"3. Exit",
};

void init_page_menu_select(int cur_menu_selected) {
	switch (cur_menu_selected) {
	case(0):
		cur_step = game_select_step;
		break;
	case(1):
		cur_step = ranking_step;
		break;
	case(2):
		exit("������ ����Ǿ����ϴ�.");
	}
}