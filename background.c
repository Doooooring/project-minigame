#include "main.h"

bool is_background_on = false;
int x, y = 0;
int block_shape;
int blockchange;
int iv1;
int tmp[4][4];

int block[8][4][4][4] = {
	{//��Ÿ ��
		{
			{1,0,0,1},
			{0,1,1,0},
			{0,1,1,0},
			{1,0,0,1}
		},
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{0,0,1,0},
			{0,1,1,0},
			{1,1,1,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,1,0,0}
		}
	},

	{    //�������
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,1,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,1,0}
		}
	},
	{   // ������� �¿��Ī
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,1,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},

	{ // T��
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},

	{   // 1��
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,1,1,1},
			{0,1,1,1}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L��
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L�� �¿��Ī
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // �簢��
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,1},
			{0,1,1,0},
			{0,1,1,0},
			{1,0,0,1}
		},
		{
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,0,1},
			{1,1,1,1}
		}
	}
};

void random_shape() //�� ������ ���� ��������
{
	block_shape = rand() % 8;
	blockchange = rand() % 4;
	x = (rand() % 15) + 1;
}

int check_first_line()//������ �Ʒ��� �ٸ� ���� ������ Ȯ���ϴ� �Լ�
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j < 19; j++)
		{
			if (background[i][j] != 0)
				return 0;
		}
	}
	return 1;


}

void draw_block()//�迭�� �׸��� �Լ�
{
	if (check_first_line() == 0)
		return;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)

		{
			tmp[i][j] = block[block_shape][blockchange][i][j];
			if (tmp[i][j] == 1)

				background[y + i][x + j] = 1;
		}
	}
}

void drop_block()//��ü �迭�� ��ĭ�� ������ �Լ�
{
	for (int i = MAPHEIGHT - 1; i > 0; i--)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			background[i][j] = background[i - 1][j];
		}
	}

	for (int j = 0; j < WIDTH; j++) {
		background[0][j] = 0;
	}

}

void update_background() {
	random_shape();
	draw_block();
	drop_block();
}

bool print_background() {

	if (is_cursor_using) return false;
	is_cursor_using = true;

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (map[i + 1][j + 1] != 0) continue;
			if (background[i][j] == 0) {
				print_str(1 + i, 1 + j, " ");
			}
			else {
				print_str(1 + i, 1 + j, white);
			}

		}
	}
	is_cursor_using = false;
	return true;
}

void start_background() {
	is_background_on = true;
}

void stop_background() {
	is_background_on = false;
}

void WINAPI background_api() {
	Sleep(50);
	while (is_background_on) {
		update_background();
		while (!print_background()) {
			Sleep(10);
		}
		Sleep(100);
	}
}

void execute_background() {
	start_background();
	int backgroundThreadId;
	HANDLE backgroundThreadHandle;
	backgroundThreadHandle = CreateThread(NULL, 0, background_api, NULL, 0, &backgroundThreadId);
}