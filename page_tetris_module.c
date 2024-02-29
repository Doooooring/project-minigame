#include "main.h"
#include "page_tetris.h"

//ȸ�� ���ɼ� üũ �� �̵��� ���
int test_block[4][2];

//Step3

//���� ����
void init_setting(int(*blocks)[4][2]) {
	set_diff();
	reset();
	init_score(); //source.c
	init_tetris_level();
	init_tetris_level_erased();
	init_seed();
	choose_next_block(blocks);
	print_outline();
	print_tetris(100);
	print_next_block(0);
	print_difficulty();
	print_str_int_format(MAPHEIGHT - TETRISHEIGHT - 2, 5, "%2d/10", tetris_level_erased);
	print_str_int_format(MAPHEIGHT - TETRISHEIGHT, 1, "SCORE: %d", score);
	print_str_int_format(MAPHEIGHT - TETRISHEIGHT - 2, 1, "LV%2d", tetris_level);
}
//���ο� ��� ���
void start_new_block(int(*blocks)[4][2]) {
	print_next_block(-1);
	change_block();
	choose_next_block(blocks);
	print_next_block(1);
	modify(blockNum);
	print_tetris(0);
}

//���� ���
void move_block() {
	if (check(down)) {
		move(down);
		print_tetris(speed);
		start_time = clock();
		while (control_enabe_time()) {
			if (_kbhit()) {
				button = get_input(_getch());
				if (button == FALSE) {
					continue;
				}
				if (check(button)) {
					move(button);
					print_tetris(0);
				}
			}
		}
		move_block();
	}
}

//���� ��� ��� ����
void set_for_next_block() {
	modify(1);
	num_erased = erase();
	control_tetris_level(num_erased);
	control_score(num_erased);
	if (num_erased > 0) {
		printf("%s", COLOR_RESET);
		print_str_int_format(MAPHEIGHT - TETRISHEIGHT - 2, 5, "%2d/10", tetris_level_erased);
		print_str_int_format(MAPHEIGHT - TETRISHEIGHT, 1, "SCORE: %d", score);
		if (num_erased > tetris_level_erased) {
			printf("%s", COLOR_RESET);
			print_str_int_format(MAPHEIGHT - TETRISHEIGHT - 2, 1, "LV%2d", tetris_level);
		}
	}
	init_num_erased();
}


//�ʱ�ȭ

// ��Ʈ���� �� �ʱ�ȭ
void reset() {
	//�Ʒ���
	i = TETRISHEIGHT + 1;
	for (j = 1; j < WIDTH + 2; j++)
		tetris_map[i][j] = 1;
	//����
	i = 0;
	for (j = 0; j < WIDTH + 2; j++)
		tetris_map[i][j] = 1;
	//����
	j = 0;
	for (i = 0; i < TETRISHEIGHT + 2; i++)
		tetris_map[i][j] = 1;
	//������
	j = WIDTH + 1;
	for (i = 0; i < TETRISHEIGHT + 2; i++)
		tetris_map[i][j] = 1;
	//����
	for (i = 1; i <= TETRISHEIGHT; i++)
		for (j = 1; j <= WIDTH; j++)
			tetris_map[i][j] = 0;
}

// ��Ʈ���� �� ĳ�� �ʱ�ȭ
void init_mem() {
	for (int i = 0; i < TETRISHEIGHT + 2; i++) {
		for (int j = 0; j < WIDTH + 2; j++) {
			mem[i][j] = -2;
		}
	}
}
//�ܰ� �ʱ�ȭ
void init_tetris_level() {
	tetris_level = 1;
}
//�ܰ� �� ���� ���� �ʱ�ȭ
void init_tetris_level_erased() {
	tetris_level_erased = 0;
}
//�� ������ ���� ���� �ʱ�ȭ
void init_num_erased() {
	num_erased = 0;
}

//���� �ʱ�ȭ
void init_seed() {
	srand(time(NULL));
	seed = rand() % 2024;
}

//�Է�

//����Ű +�����̽���
int get_input(int button) {
	switch (button) {
	case(ARROW_DOWN):
		return down;
	case(ARROW_LEFT):
		return left;
	case(ARROW_RIGHT):
		return right;
	case(ARROW_UP):
		return up;
	case(SPACEBAR):
		return spacebar;
	default:
		return false;
	}
}

//���

//�׵θ� �׸���
void print_outline() {
	printf("%s", COLOR_RESET);
	i = MAPHEIGHT + 1;
	for (j = 1; j < WIDTH + 2; j++)
		print_str(i, j, white);
	//����
	i = 0;
	for (j = 0; j < WIDTH + 2; j++)
		print_str(i, j, white);
	//����
	j = 0;
	for (i = 0; i < MAPHEIGHT + 2; i++)
		print_str(i, j, white);
	//������
	j = WIDTH + 1;
	for (i = 0; i < MAPHEIGHT + 2; i++)
		print_str(i, j, white);
}


// ��Ʈ���� �� ���
void print_tetris(int speed) {
	for (int i = 1; i < TETRISHEIGHT + 1; i++) {
		for (int j = 1; j < WIDTH + 1; j++)
		{
			if (mem[i][j] == tetris_map[i][j]) continue;
			gotoxy(j, MAPHEIGHT - TETRISHEIGHT + i);
			coloring_block(tetris_map[i][j]);
			mem[i][j] = tetris_map[i][j];
		}
	}
	Sleep(speed);
}

// ���̵� ���
void print_difficulty() {
	switch (difficulty) {
	case(advanced):
		print_str_row(1, "<ADVANCED>");
		break;
	case(challenge):
		print_str_row(1, "<CHANLLENGE>");
		break;
	case(impossible):
		print_str_row(1, "<IMPOSSIBLE>");
		break;
	}
}

//���� ��� ���
void print_next_block(int type) {
	if (type == 1)
		for (i = 0; i < 4; i++) {
			gotoxy(next_block[i][1] - start_w + WIDTH - 1, next_block[i][0]);
			coloring_block(randNum);
		}
	else if (type == -1)
		for (i = 0; i < 4; i++) {
			gotoxy(next_block[i][1] - start_w + WIDTH - 1, next_block[i][0]);
			printf("%s", COLOR_RESET);
			printf(black);
		}
	else
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++) {
				gotoxy(WIDTH - 3 + i, start_h - 1 + j);
				printf("%s", COLOR_RESET);
				printf(black);
			}
}

//��� ����
void coloring_block(int color) {
	switch (color) {
	case(1):
		printf("%s", COLOR_CYAN);
		printf(white);
		break;
	case(2):
		printf("%s", COLOR_YELLOW);
		printf(white);
		break;
	case(3):
		printf("%s", COLOR_GREEN);
		printf(white);
		break;
	case(4):
		printf("%s", COLOR_GREEN);
		printf(white);
		break;
	case(5):
		printf("%s", COLOR_BLUE);
		printf(white);
		break;
	case(6):
		printf("%s", COLOR_BLUE);
		printf(white);
		break;
	case(7):
		printf("%s", COLOR_RED);
		printf(white);
		break;
	case(8):
		printf("%s", COLOR_PURPLE);
		printf(white);
		break;
	default:
		printf("%s", COLOR_RESET);
		printf(black);
		break;
	}
}

//����

//���� ��ϰ� ������ �ҷ� ��ü
void change_block() {
	for (i = 0; i < 4; i++)
		for (j = 0; j < 2; j++)
			block[i][j] = next_block[i][j];
	blockNum = randNum;
}

//��� ����
void choose_next_block(int(*blocks)[4][2]) {
	srand(seed);
	seed += 1;
	randNum = rand() % 7;
	for (i = 0; i < 4; i++)
	{
		next_block[i][0] = blocks[(randNum)][i][0];
		next_block[i][1] = blocks[(randNum)][i][1];
	}
	randNum += 2;
}

//���� ���� �ð�
int control_enabe_time() {
	end_time = clock();
	if ((int)(end_time - start_time) <= speed / 10)
		return true;
	else
		return false;
}

//�ܰ� ����
void control_tetris_level(int num_erased) {
	tetris_level_erased += num_erased;
	if (tetris_level_erased >= goal) {
		tetris_level_erased -= goal;
		tetris_level += 1;
		speed -= 10;
		if (speed == 0)
			speed = 1;
	}
}

//���� ����
void control_score(int num_erased) {
	if (num_erased > tetris_level_erased)
		score += num_erased * (tetris_level - 1) * 1000;
	else
		score += num_erased * tetris_level * 1000;
}

//���̵� ����
void set_diff() {
	switch (difficulty) {
	case(advanced):
		speed = 150;
		break;
	case(challenge):
		speed = 100;
		break;
	case(impossible):
		speed = 50;
		break;
	}
}

//�˰���
// 
//��� üũ
int check(int type) {
	switch (type) {
		//�� ����
	case(down):
		for (i = 0; i < 4; i++)
			if (tetris_map[(block[i][0] + 1)][(block[i][1])] == 1)
				return false;
		break;
		//�� ����
	case(left):
		for (i = 0; i < 4; i++)
			if (tetris_map[(block[i][0])][(block[i][1] - 1)] == 1)
				return false;
		break;
		//������ ����
	case(right):
		for (i = 0; i < 4; i++)
			if (tetris_map[(block[i][0])][(block[i][1] + 1)] == 1)
				return false;
		break;
		//ȸ�� ����
	case(up):
		for (int i = 0; i < 4; i++) {
			test_block[i][0] = block[0][0] + (block[i][1] - block[0][1]);
			test_block[i][1] = block[0][1] - (block[i][0] - block[0][0]);
		}
		for (i = 0; i < 4; i++)
			if (tetris_map[(test_block[i][0])][(test_block[i][1])] == 1)
				return false;
		break;
	case(spacebar):
		break;
		//���� ����
	default:
		for (i = 0; i < 4; i++)
			if (block[i][0] == 1)
				return false;
	}
	return true;
}

//BLOCK �̵�
void move(int type) {
	modify(0);
	//������ �̵�
	switch (type) {
	case(down):
		for (i = 0; i < 4; i++)
			block[i][0]++;
		modify(blockNum);
		break;
		//�������� �̵�
	case(left):
		for (i = 0; i < 4; i++)
			block[i][1]--;
		modify(blockNum);
		break;
		//���������� �̵�
	case(right):
		for (i = 0; i < 4; i++)
			block[i][1]++;
		modify(blockNum);
		break;
		//ȸ�� ����
	case(up):
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 2; j++)
				block[i][j] = test_block[i][j];
		}
		modify(blockNum);
		break;
		//
	case(spacebar):
		if (check(down)) {
			move(down);
			move(spacebar);
		}
		break;
	}
}

//BlOCK �� ����
void modify(int change) {
	int h, w;
	for (i = 0; i < 4; i++) {
		h = block[i][0], w = block[i][1];
		tetris_map[h][w] = change;
	}
}

//��� ����
int erase() {
	int num = 0;
	int type;
	for (i = TETRISHEIGHT; i > 0; i--) {
		type = line_check_for_erase(i, 1);
		if (type) {
			i++;
			num++;
		}
	}
	return num;
}

int line_check_for_erase(int h, int w) {
	if (w > WIDTH) {
		line_drop_for_erase(h);
		return true;
	}
	else {
		if (tetris_map[h][w]) {
			line_check_for_erase(h, (w + 1));
		}
		else
			return false;
	}
}

void line_drop_for_erase(int line) {
	if (line > 1) {
		for (k = 1; k <= WIDTH; k++) {
			tetris_map[line][k] = tetris_map[(line - 1)][k];
		}
		line_drop_for_erase(line - 1);
	}
	else
		for (k = 1; k <= WIDTH; k++)
			tetris_map[line][k] = 0;
}














