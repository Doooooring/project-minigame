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
	//게임 시작
	init_setting(blocks);
	//테트리스 게임
	while (true) {
		//새로운 블록 출발
		start_new_block(blocks);
		//블록 이동
		move_block();
		//끝나는 경우 확인
		if (check(0) == false) {
			cur_step = ranking_step;
			return;
		}
		//다음 블록 출발을 위한 세팅
		set_for_next_block();
	}
}

