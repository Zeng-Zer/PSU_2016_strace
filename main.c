#include <unistd.h>
int main() {
  int i = 0;
  for (i = 0; i < 50 ; i++)
    write(1, "z\n", 2);
  return (0);
}
