#include "mylib.h"

int my_val = 0;

void init_my_lib() { my_val = 10; }

int get_my_lib_val() { return my_val; }

void shutdown_my_lib() { my_val = 0; }