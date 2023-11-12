void check_menu() {
  if (gv_inc_menu) {
    inc_menu();
    gv_inc_menu = false;
  }
}

void inc_menu() {
  gv_act_menu += 1;
  if (gv_act_menu >= gc_max_menu) {
    gv_act_menu = 0;
  }
}