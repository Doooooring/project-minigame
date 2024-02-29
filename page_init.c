#include "main.h"
#include "page_init.h"

int page_init() {

	init_cur_menu_selected();
	set_init_page_map();
	print_init_title();

	while (1) {

		update_background();
		print_background();
		print_menu();

		if (_kbhit()) {
			get_user_menu_input();
			continue;
		}
		
		Sleep(75);

		if (cur_step != init_step) break;
	}
}