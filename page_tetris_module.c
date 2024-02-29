#include "main.h"
#include "page_tetris.h"

//회전 가능성 체크 및 이동용 블록
int test_block[4][2];

//Step3

//게임 시작
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
//새로운 블록 출발
void start_new_block(int(*blocks)[4][2]) {
	print_next_block(-1);
	change_block();
	choose_next_block(blocks);
	print_next_block(1);
	modify(blockNum);
	print_tetris(0);
}

//무브 블록
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

//다음 블록 출발 세팅
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


//초기화

// 테트리스 맵 초기화
void reset() {
	//아래쪽
	i = TETRISHEIGHT + 1;
	for (j = 1; j < WIDTH + 2; j++)
		tetris_map[i][j] = 1;
	//위쪽
	i = 0;
	for (j = 0; j < WIDTH + 2; j++)
		tetris_map[i][j] = 1;
	//왼쪽
	j = 0;
	for (i = 0; i < TETRISHEIGHT + 2; i++)
		tetris_map[i][j] = 1;
	//오른쪽
	j = WIDTH + 1;
	for (i = 0; i < TETRISHEIGHT + 2; i++)
		tetris_map[i][j] = 1;
	//내부
	for (i = 1; i <= TETRISHEIGHT; i++)
		for (j = 1; j <= WIDTH; j++)
			tetris_map[i][j] = 0;
}

// 테트리스 맵 캐시 초기화
void init_mem() {
	for (int i = 0; i < TETRISHEIGHT + 2; i++) {
		for (int j = 0; j < WIDTH + 2; j++) {
			mem[i][j] = -2;
		}
	}
}
//단계 초기화
void init_tetris_level() {
	tetris_level = 1;
}
//단계 내 지운 개수 초기화
void init_tetris_level_erased() {
	tetris_level_erased = 0;
}
//한 프레임 지운 개수 초기화
void init_num_erased() {
	num_erased = 0;
}

//씨드 초기화
void init_seed() {
	srand(time(NULL));
	seed = rand() % 2024;
}

//입력

//방향키 +스페이스바
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

//출력

//테두리 그리기
void print_outline() {
	printf("%s", COLOR_RESET);
	i = MAPHEIGHT + 1;
	for (j = 1; j < WIDTH + 2; j++)
		print_str(i, j, white);
	//위쪽
	i = 0;
	for (j = 0; j < WIDTH + 2; j++)
		print_str(i, j, white);
	//왼쪽
	j = 0;
	for (i = 0; i < MAPHEIGHT + 2; i++)
		print_str(i, j, white);
	//오른쪽
	j = WIDTH + 1;
	for (i = 0; i < MAPHEIGHT + 2; i++)
		print_str(i, j, white);
}


// 테트리스 맵 출력
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

// 난이도 출력
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

//다음 블록 출력
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

//블록 색깔
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

//세팅

//다음 블록과 움직일 불럭 교체
void change_block() {
	for (i = 0; i < 4; i++)
		for (j = 0; j < 2; j++)
			block[i][j] = next_block[i][j];
	blockNum = randNum;
}

//블록 선택
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

//조종 가능 시간
int control_enabe_time() {
	end_time = clock();
	if ((int)(end_time - start_time) <= speed / 10)
		return true;
	else
		return false;
}

//단계 조정
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

//점수 조정
void control_score(int num_erased) {
	if (num_erased > tetris_level_erased)
		score += num_erased * (tetris_level - 1) * 1000;
	else
		score += num_erased * tetris_level * 1000;
}

//난이도 조정
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

//알고리즘
// 
//블록 체크
int check(int type) {
	switch (type) {
		//밑 점검
	case(down):
		for (i = 0; i < 4; i++)
			if (tetris_map[(block[i][0] + 1)][(block[i][1])] == 1)
				return false;
		break;
		//왼 점검
	case(left):
		for (i = 0; i < 4; i++)
			if (tetris_map[(block[i][0])][(block[i][1] - 1)] == 1)
				return false;
		break;
		//오른쪽 점검
	case(right):
		for (i = 0; i < 4; i++)
			if (tetris_map[(block[i][0])][(block[i][1] + 1)] == 1)
				return false;
		break;
		//회전 점검
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
		//종료 점검
	default:
		for (i = 0; i < 4; i++)
			if (block[i][0] == 1)
				return false;
	}
	return true;
}

//BLOCK 이동
void move(int type) {
	modify(0);
	//밑으로 이동
	switch (type) {
	case(down):
		for (i = 0; i < 4; i++)
			block[i][0]++;
		modify(blockNum);
		break;
		//왼쪽으로 이동
	case(left):
		for (i = 0; i < 4; i++)
			block[i][1]--;
		modify(blockNum);
		break;
		//오른쪽으로 이동
	case(right):
		for (i = 0; i < 4; i++)
			block[i][1]++;
		modify(blockNum);
		break;
		//회전 적용
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

//BlOCK 값 조정
void modify(int change) {
	int h, w;
	for (i = 0; i < 4; i++) {
		h = block[i][0], w = block[i][1];
		tetris_map[h][w] = change;
	}
}

//블록 제거
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














