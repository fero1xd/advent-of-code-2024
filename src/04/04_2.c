#include "../io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *contents = read_file("./src/04/input.txt");

  // TMp
  int width = 139;
  int height = 139;

  char *line = strtok(contents, "\n");
  int row = 0;
  int count = 0;

  while (line != NULL) {

    for (int i = 0; (line[i] != '\0'); i++) {

      if (line[i] != 'A')
        continue;

      int space_r = width - i;
      int space_b = height - row;

      if (space_r >= 1 && space_b >= 1 && i >= 1 && row >= 1) {
        char *nxt = strtok((line + width + 2), "\n");
        char *up = strtok((line - width - 2), "\n");

        bool pos = (nxt[i + 1] == 'S' && up[i - 1] == 'M') ||
                   (nxt[i + 1] == 'M' && up[i - 1] == 'S');

        bool neg = (nxt[i - 1] == 'S' && up[i + 1] == 'M') ||
                   (nxt[i - 1] == 'M' && up[i + 1] == 'S');
        if (pos && neg) {
          count++;
        }
      }
    }

    line = strtok((line + width + 2), "\n");
    row++;
  }

  printf("X-MAS are: %d\n", count);

  free(contents);
  return 0;
}
