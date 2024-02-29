#include "page_shooting.h"

int page_shooting() {

	system("cls");

	goal = 300;
	cursor_view();
	initiallize_setting();
	while (1) {
		init_shooting_timer();
		while (timer(start_shooting, end_shooting, speed)) {
			init_control_timer();
			while (timer(start_control, end_control, 10)) {
				if (_kbhit()) {
					button = get_input(_getch());
					control(button);
					make_total_map();
					check_score();
					print_shooting_game(0);
					break;
				}
				end_control = (int)clock();
			}
			move_shooting();
			make_total_map();
			check_score();
			print_shooting_game(0);
			end_shooting = (int)clock();
		}
		move_monster();
		make_monster();
		make_total_map();
		check_score();
		print_shooting_game(0);
		if (cur_step != shooting_step) {
			break;
		}
	}
	return 0;
}