#include "main.h"
#include "page_game_select.h"

int page_game_select() {

	set_init_game_select();
	print_game_title();

	while (1) {

		update_background(); // ��׶��� ������Ʈ
		print_background(); // ��׶��� �׸���
		print_game_menu(); // ���� ������ �׸���

		if (_kbhit()) {
			get_user_game_input(); // ���� �Է� �ޱ�
			continue;
		}
		Sleep(50);


		if (cur_step != game_select_step) break; // ���� ��ȿ�� Ȯ��
	}
}