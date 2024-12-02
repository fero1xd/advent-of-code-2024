#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *contents = read_file("./input.txt");

  char *token = strtok(contents, "\n");

  int count = 0;
  int safe_reports = 0;

  while (token != NULL) {
    int chars = 0;
    for (int i = 0; token[i] != '\0'; i++) {
      chars++;
    }

    // char *copy = strdup(token);
    // char *l = strtok(copy, "   ");
    // char *r = strtok(0, "   ");
    //
    char *lvl = strtok(token, " ");
    int safe = 1;
    int last_num = 0;
    int first_run = 1;
    int decreasing = -1;

    while (lvl != NULL) {
      int int_lvl = atoi(lvl);

      if (first_run == 1) {
        last_num = int_lvl;
        first_run = 0;
      } else {
        if (decreasing == -1) {
          decreasing = (int_lvl - last_num) > 0 ? 0 : 1;
        } else {
          if (!decreasing && (int_lvl - last_num) < 0) {
            safe = 0;
            break;
          } else if (decreasing && (int_lvl - last_num) > 0) {
            safe = 0;
            break;
          }
        }

        int diff = abs(atoi(lvl) - last_num);
        if (diff > 3 || diff < 1) {
          safe = 0;
          break;
        }

        last_num = atoi(lvl);
      }

      lvl = strtok(0, " ");
    }

    if (safe == 1) {
      safe_reports++;
    }

    token = strtok((token + chars + 1), "\n");
    count++;
  }

  printf("safe reports: %d\n", safe_reports);
  free(contents);
  return 0;
}
