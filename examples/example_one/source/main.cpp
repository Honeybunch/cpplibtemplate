#include "examplecore.h"
#include "mylib.h"

#include <assert.h>

int main() {
  example_core_init();

  int mylib_val = get_my_lib_val();
  assert(mylib_val == 10);

  example_core_shutdown();

  mylib_val = get_my_lib_val();
  assert(mylib_val == 0);

  return 0;
}