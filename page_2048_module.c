#include "main.h"
#include "page_2048.h"

int arr_2048[4][4] = { 0 };
bool is_updated = true;

#define INITIAL_X 1
#define INITIAL_Y 1
#define GAP 9

#define WIDTH_2048 GAP * 4
#define HEADER_2048 5

char color_map[12][30] = {
	COLOR_WHITE_DARK_GRAY,
	COLOR_WHITE_PASTEL_ORANGE,
	COLOR_WHITE_PASTEL_BLUE,
	COLOR_WHITE_PASTEL_PINK,
	COLOR_WHITE_PASTEL_BROWN
	COLOR_WHITE_PASTEL_CYAN,
	COLOR_WHITE_PASTEL_LIGHT_GREY,
	COLOR_WHITE_PASTEL_PURPLE,
	COLOR_WHITE_PASTEL_YELLOW,
	COLOR_WHITE_PASTEL_MAGENTA,
	COLOR_WHITE_PASTEL_BROWN,
	COLOR_WHITE_PASTEL_LIGHT_GREY
};

int get_color_ind(int num) {
	int color_ind = 0;
	int tmp = num;

	while (tmp >= 1) {
		tmp = tmp >> 1;
		color_ind++;
	}

	return color_ind;
}

void initiate_2048_arr() {
	is_updated = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arr_2048[i][j] = 0;
		}
	}
}


void generate_rand_num() {

	if (is_updated == false) return;

	int cnt = 0;
	int rand_x = 0;
	int rand_y = 0;

	time_t seed = time(NULL);
	srand(seed);
	int num = rand() % 16;
	int gen_cnt = 1;
	rand_x = num / 4;
	rand_y = num % 4;

	while (arr_2048[rand_x][rand_y] > 0 && gen_cnt <= 16) {

		rand_x = num / 4;
		rand_y = num % 4;

		num = (num + 1) % 16;
		gen_cnt++;
	}


	arr_2048[rand_x][rand_y] = 1;
	is_updated = false;
}


void check_2048_validate() {

	int dd[4][2] = { {1,0}, {0, 1}, {-1, 0}, {0, -1} };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr_2048[i][j] == 0) return;

			for (int k = 0; k < 4; k++) {
				int* d = dd[k];
				int dx = d[0], dy = d[1];
				int nx = i + dx, ny = j + dy;
				if (0 <= nx && nx < 4 && 0 <= ny && ny < 4) {
					if (arr_2048[nx][ny] == arr_2048[i][j]) return;
				}
			}
		}
	}

	set_cur_step(ranking_step);
}



void move_left() {
	for (int i = 0; i < 4; i++) {
		int sub_arr[4] = { 0 };
		int cur = 0;
		int sub_arr_ind = 0;


		int prev_line[4];
		for (int j = 0; j < 4; j++) {
			prev_line[j] = arr_2048[i][j];
		}

		while (true) {
			while (cur < 4 && arr_2048[i][cur] == 0) cur++;
			if (cur == 4) break;
			int ne = cur + 1;
			while (ne < 4 && arr_2048[i][ne] == 0) ne++;
			if (ne < 4 && arr_2048[i][cur] == arr_2048[i][ne]) {
				sub_arr[sub_arr_ind] = arr_2048[i][cur] * 2;
				score += arr_2048[i][cur];
				arr_2048[i][cur] = 0;
				arr_2048[i][ne] = 0;
				sub_arr_ind++;
			}
			else {
				sub_arr[sub_arr_ind] = arr_2048[i][cur];
				arr_2048[i][cur] = 0;
				sub_arr_ind++;
			}
			cur++;
		}

		for (int k = 0; k < 4; k++) {
			if (sub_arr[k] == 0) break;
			if (prev_line[k] != sub_arr[k]) is_updated = true;
			arr_2048[i][k] = sub_arr[k];
		}
	}
}

void move_right() {

	for (int i = 0; i < 4; i++) {
		int sub_arr[4] = { 0 };
		int cur = 3;
		int sub_arr_ind = 3;

		int prev_line[4];
		for (int j = 0; j < 4; j++) {
			prev_line[j] = arr_2048[i][j];
		}

		while (true) {
			while (cur > -1 && arr_2048[i][cur] == 0) cur--;
			if (cur == -1) break;
			int ne = cur - 1;
			while (ne > -1 && arr_2048[i][ne] == 0) ne--;
			if (ne > -1 && arr_2048[i][cur] == arr_2048[i][ne]) {
				sub_arr[sub_arr_ind] = arr_2048[i][cur] * 2;
				score += arr_2048[i][cur];
				arr_2048[i][cur] = 0;
				arr_2048[i][ne] = 0;
				sub_arr_ind--;
			}
			else {
				sub_arr[sub_arr_ind] = arr_2048[i][cur];
				arr_2048[i][cur] = 0;
				sub_arr_ind--;
			}
			cur--;
		}

		for (int k = 3; k > -1; k--) {
			if (sub_arr[k] == 0) break;
			if (prev_line[k] != sub_arr[k]) is_updated = true;
			arr_2048[i][k] = sub_arr[k];
		}
	}
}

void move_up() {
	for (int i = 0; i < 4; i++) {
		int sub_arr[4] = { 0 };
		int cur = 0;
		int sub_arr_ind = 0;
		
		int prev_line[4];
		for (int j = 0; j < 4; j++) {
			prev_line[j] = arr_2048[j][i];
		}

		while (true) {
			while (cur < 4 && arr_2048[cur][i] == 0) cur++;
			if (cur == 4) break;
			int ne = cur + 1;
			while (ne < 4 && arr_2048[ne][i] == 0) ne++;
			if (ne < 4 && arr_2048[cur][i] == arr_2048[ne][i]) {
				sub_arr[sub_arr_ind] = arr_2048[cur][i] * 2;
				score += arr_2048[cur][i];
				arr_2048[cur][i] = 0;
				arr_2048[ne][i] = 0;
				sub_arr_ind++;
			}
			else {
				sub_arr[sub_arr_ind] = arr_2048[cur][i];
				arr_2048[cur][i] = 0;
				sub_arr_ind++;
			}
			cur++;
		}

		for (int k = 0; k < 4; k++) {
			if (sub_arr[k] == 0) break;
			if (prev_line[k] != sub_arr[k]) is_updated = true;
			arr_2048[k][i] = sub_arr[k];
		}
	}
}

void move_down() {

	for (int i = 0; i < 4; i++) {
		int sub_arr[4] = { 0 };
		int cur = 3;
		int sub_arr_ind = 3;


		int prev_line[4];
		for (int j = 0; j < 4; j++) {
			prev_line[j] = arr_2048[j][i];
		}


		while (true) {
			while (cur > -1 && arr_2048[cur][i] == 0) cur--;
			if (cur == -1) break;
			int ne = cur - 1;
			while (ne > -1 && arr_2048[ne][i] == 0) ne--;
			if (ne > -1 && arr_2048[cur][i] == arr_2048[ne][i]) {
				sub_arr[sub_arr_ind] = arr_2048[cur][i] * 2;
				score += arr_2048[cur][i];
				arr_2048[cur][i] = 0;
				arr_2048[ne][i] = 0;
				sub_arr_ind--;
			}
			else {
				sub_arr[sub_arr_ind] = arr_2048[cur][i];
				arr_2048[cur][i] = 0;
				sub_arr_ind--;
			}
			cur--;
		}

		for (int k = 3; k > -1; k--) {
			if (sub_arr[k] == 0) break;
			if (prev_line[k] != sub_arr[k]) is_updated = true;
			arr_2048[k][i] = sub_arr[k];
		}
	}
}

void get_2048_user_input() {
	int input;
	input = _getch();

	if (input == 224) {
		input = _getch();
		switch (input) {
		case (ARROW_DOWN):
			move_down();
			break;
		case (ARROW_RIGHT):
			move_right();
			break;
		case (ARROW_UP):
			move_up();
			break;
		case (ARROW_LEFT):
			move_left();
			break;
		}
	}
	else if (input == END) {
		set_cur_step(init_step);
		return;
	}
}



void print_2048_title() {
	print_str(1, 1, "< 2048 >");
	print_str_int_format(3, 1, "SCORE: %d", score);
}

void print_2048_shorten() {

	int start_y = WIDTH_2048 - 3;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%s", color_map[get_color_ind(arr_2048[i][j])]);
			print_str(INITIAL_X + i, start_y + j, " ");
		}
	}

}

void print_arr_2048() {

	print_2048_title();
	print_2048_shorten();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int cur = arr_2048[i][j];
			int color_ind = get_color_ind(cur);

			char cur_color[30];
			strcpy(cur_color, color_map[color_ind]);
			printf("%s", cur_color);
			int cur_x = INITIAL_X + HEADER_2048 + i * GAP;
			int cur_y = INITIAL_Y + j * GAP;
			for (int k = 0; k < GAP; k++) {
				print_str(cur_x, cur_y + k, " ");
				print_str(cur_x + GAP - 1, cur_y + k, " ");
			}

			for (int k = 1; k < GAP - 1; k++) {
				print_str(cur_x + k, cur_y, " ");
				print_str(cur_x + k, cur_y + GAP - 1, " ");
			}

			for (int k1 = 1; k1 < GAP - 1; k1++) {
				for (int k2 = 1; k2 < GAP - 1; k2++) {
					print_str(cur_x + k1, cur_y + k2, " ");
				}
			}

			char cur_str[6] = "";
			_itoa(cur, cur_str, 10);
			int cur_len = strlen(cur_str);
			int s_y = (GAP - cur_len) / 2;
			print_str(cur_x + (GAP / 2), cur_y + s_y, cur_str);

			printf("%s", COLOR_RESET);
		}
	}
}

void init_arr_2048() {
	srand(time(NULL));
	int num = rand() % 16;

	int i_x = num >> 2;
	int i_y = num % 4;

	arr_2048[i_x][i_y] = 1;

}
