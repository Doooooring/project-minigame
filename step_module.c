int cur_selected = 0;

void select_up() {
	if (cur_selected == 0) return;
	cur_selected--;
}

void select_down() {
	if (cur_selected == 2) return;
	cur_selected++;
}