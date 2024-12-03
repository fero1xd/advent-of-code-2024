#include "../io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_safe_report(char *starting, int ignore_idx);
int get_num_levels(char *report);

int main() {
  char *contents = read_file("./src/02/input.txt");

  char *token = strtok(contents, "\n");

  int count = 0;
  int safe_reports = 0;

  while (token != NULL) {
    int chars = 0;
    for (int i = 0; token[i] != '\0'; i++) {
      chars++;
    }

    // TODO: dont make a copy
    char *report_cpy = strdup(token);
    char *lvl = strtok(token, " ");

    // TODO: make this dynamic
    int num_lvls = 5;
    bool safe = is_safe_report(lvl, -1);

    if (safe) {
      safe_reports++;
    } else {
      char *lvl = strdup(report_cpy);
      int i = 0;
      while (i < num_lvls) {
        printf("Testing %s, level by removing %d\n", lvl, i);
        bool is_safe_after_rm = is_safe_report(strdup(lvl), i++);
        printf("| SAFE=%d |\n", is_safe_after_rm);
        if (is_safe_after_rm) {
          // printf("Safe after removing %dth level, %s", i, lvl);
        }
      }
    }

    printf("\n");

    token = strtok((token + chars + 1), "\n");
    count++;
  }

  printf("safe reports: %d\n", safe_reports);
  free(contents);
  return 0;
}

int get_num_levels(char *report) {
  int i = 0;
  while (report != NULL) {
    i++;
    report = strtok(0, " ");
  }
  return i;
}

bool is_safe_report(char *lvl, int ignore_idx) {
  int safe = 1;
  int last_num = 0;
  int first_run = 1;
  int decreasing = -1;
  int i = 0;

  // 1 2 3 4 5

  while (lvl != NULL) {
    int int_lvl = atoi(lvl);

    if (i == ignore_idx) {
      // 1\02\03 4 5
      lvl = strtok((lvl + ((i++) * 2) + 2), " ");

      // lvl = strtok(0, " ");
      continue;
    }

    if (ignore_idx > -1) {
      printf("%s ", lvl);
    }

    if (first_run == 1) {
      last_num = int_lvl;
      first_run = 0;
    } else {
      if (decreasing == -1) {
        decreasing = (int_lvl - last_num) > 0 ? 0 : 1;
      } else {
        if (!decreasing && (int_lvl - last_num) < 0) {
          if (ignore_idx > -1) {
            printf("_dec_");
          }
          safe = 0;
          break;
        } else if (decreasing && (int_lvl - last_num) > 0) {
          if (ignore_idx > -1) {
            printf("_inc_");
          }
          safe = 0;
          break;
        }
      }

      int diff = abs(atoi(lvl) - last_num);
      if (diff > 3 || diff < 1) {
        if (ignore_idx > -1) {
          printf("_far_");
        }
        safe = 0;
        break;
      }

      last_num = atoi(lvl);
    }

    lvl = strtok(0, " ");
    i++;
  }

  return safe;
}
