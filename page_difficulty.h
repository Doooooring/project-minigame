#pragma once
#include "menu_module.h"
#define DIFFICULTY_PAGE_TITLE "Difficulty"

extern char* difficulty_menus[];

void difficulty_page_menu_select(int cur_menu_selected);
void initialize_difficulty_page_map();

menu* page_difficulty_menu;
