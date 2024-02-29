#include "main.h"
#include "page_difficulty.h"

int page_difficulty() {

	set_difficulty_page();
	print_difficulty_title();

	while (1) {

		update_background();
		print_background();
		print_difficulties();

		if (_kbhit()) {
			get_user_difficulty_input();
			continue;
		}

		Sleep(50);

		if (cur_step != difficult_select_step) break;
	}
}