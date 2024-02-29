#include "main.h"
#include "page_tetris.h"

int blocks[7][4][2] =
{
	{
		{start_h, start_w},
		{start_h - 1, start_w},
		{start_h + 1, start_w},
		{start_h + 2, start_w}
	},
	{
		{start_h , start_w},
		{start_h - 1,start_w},
		{start_h + 1,start_w + 1},
		{start_h , start_w + 1}
	},
	{
		{start_h , start_w},
		{start_h - 1,start_w},
		{start_h ,start_w - 1},
		{start_h + 1,start_w - 1}
	},
	{
		{start_h, start_w},
		{start_h,start_w - 1},
		{start_h,start_w + 1},
		{start_h - 1,start_w + 1}
	},
	{
		{start_h , start_w},
		{start_h,start_w - 1},
		{start_h,start_w + 1},
		{start_h - 1,start_w - 1}
	},
	{
		{start_h, start_w},
		{start_h - 1,start_w},
		{start_h - 1,start_w + 1},
		{start_h,start_w + 1}
	},
	{
		{start_h,start_w},
	{start_h,start_w - 1},
	{start_h,start_w + 1},
	{start_h - 1,start_w}
	}
}
;

int page_tetris() {
	//���� ����
	init_setting(blocks);
	//��Ʈ���� ����
	while (true) {
		//���ο� ��� ���
		start_new_block(blocks);
		//��� �̵�
		move_block();
		//������ ��� Ȯ��
		if (check(0) == false) {
			cur_step = ranking_step;
			return;
		}
		//���� ��� ����� ���� ����
		set_for_next_block();
	}
}

