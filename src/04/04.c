#include "../io.h"
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

      int space_r = width - i;
      if (space_r >= 3) {
        // Check right
        if (strncmp(&line[i], "XMAS", 4) == 0) {
          count++;
        } else if (strncmp(&line[i], "SAMX", 4) == 0) {
          count++;
        }
        //        char *p = strstr(&line[i], "XMAS");
        // if (p == &line[i]) {
        // }
      }

      int space_b = height - row;
      if (space_b >= 3) {
        char *nxt = strtok((line + width + 2), "\n");
        char *nxt2 = strtok((nxt + width + 2), "\n");
        char *nxt3 = strtok((nxt2 + width + 2), "\n");

        // veritcal
        if (line[i] == 'X' && nxt[i] == 'M' && nxt2[i] == 'A' &&
            nxt3[i] == 'S') {
          count++;
        }
        if (line[i] == 'S' && nxt[i] == 'A' && nxt2[i] == 'M' &&
            nxt3[i] == 'X') {
          count++;
        }

        // Diagonal right/pos
        if (space_r >= 3) {
          if (line[i] == 'X' && nxt[i + 1] == 'M' && nxt2[i + 2] == 'A' &&
              nxt3[i + 3] == 'S') {
            count++;
          }

          if (line[i] == 'S' && nxt[i + 1] == 'A' && nxt2[i + 2] == 'M' &&
              nxt3[i + 3] == 'X') {
            count++;
          }
        }

        // Diagonal left/neg
        if (i >= 3) {
          if (line[i] == 'X' && nxt[i - 1] == 'M' && nxt2[i - 2] == 'A' &&
              nxt3[i - 3] == 'S') {
            count++;
          }

          if (line[i] == 'S' && nxt[i - 1] == 'A' && nxt2[i - 2] == 'M' &&
              nxt3[i - 3] == 'X') {
            count++;
          }
        }
      }
    }

    line = strtok((line + width + 2), "\n");
    row++;
  }

  printf("XMAS are: %d\n", count);

  free(contents);
  return 0;
}
