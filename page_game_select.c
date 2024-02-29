#include "main.h"
#include "page_game_select.h"

int page_game_select() {

	set_init_game_select();
	print_game_title();

	while (1) {

		update_background(); // 백그라운드 업데이트
		print_background(); // 백그라운드 그리기
		print_game_menu(); // 실제 컨텐츠 그리기

		if (_kbhit()) {
			get_user_game_input(); // 유저 입력 받기
			continue;
		}
		Sleep(50);


		if (cur_step != game_select_step) break; // 스텝 유효성 확인
	}
}