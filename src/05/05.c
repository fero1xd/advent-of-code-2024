#include "../io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(char *str);
bool rule_exists(char *r, char *rules);
void reorder_pages(int *pages, int len, char *rules);

int main() {
  char *rules = read_file("./src/05/input.txt");

  char *updates = strstr(rules, "\n\n");
  updates[0] = '\0';
  updates += 2;
  updates[strlen(updates) - 1] = '\0';

  int count = 0;
  int middle_sum = 0;

  char *pages;
  while ((pages = strsep(&updates, "\n")) != NULL) {
    bool right_order = true;

    char *p = strdup(pages);
    char *page;

    int curr_page = 0;
    int *order = (int *)calloc(50, sizeof(int));
    bool failed = false;

    while ((page = strsep(&p, ",")) != NULL) {
      // Compare this page with every other page
      int i = 1;
      int page_i = atoi(page);
      order[curr_page] = page_i;

      // Starting page
      char *p_cp = strdup(pages);
      char *page_cp;

      // Loop till page_cp is null
      while (((page_cp = strsep(&p_cp, ",")) != NULL) && !failed) {
        int page_cp_i = atoi(page_cp);

        char rule[5 + 1];
        sprintf(rule, "%d|%d", page_cp_i, page_i);

        if (rule_exists(rule, rules) && (curr_page < (i - 1))) {
          right_order = false;
          failed = true;
          // goto out;
        }

        i++;
      }

      curr_page++;
    }

  out:

    if (right_order) {
      count++;
    } else {
      // PART 2
      reorder_pages(order, curr_page, rules);
      middle_sum += order[(int)((float)curr_page / 2.0f)];
    }

    free(order);

    // pages = strtok(pages + chars + 1, "\n");
    // pages = strsep(&updates, "\n");
  }

  printf("Right order count: %d\n", count);
  printf("Middle sum(wrong order): %d\n", middle_sum);

  free(rules);
  return 0;
}

int count_lines(char *str) {
  int lines = 0;
  char *p = strtok(str, "\n");

  while (p != NULL) {
    lines++;
    p = strtok(0, "\n");
  }

  return lines;
}

bool rule_exists(char *r, char *rules) {
  char *cp = strdup(rules);
  char *p;
  bool exists = false;

  while ((p = strsep(&cp, "\n")) != NULL) {
    if (strcmp(p, r) == 0) {
      exists = true;
      break;
    }
  }

  return exists;
}

void reorder_pages(int *pages, int len, char *rules) {
  for (int i = 0; i < len; i++) {

    for (int j = 0; j < len; j++) {
      if (i == j)
        continue;

      char rule[5 + 1];
      sprintf(rule, "%d|%d", pages[j], pages[i]);

      if (rule_exists(rule, rules) && (i < j)) {
        // Swap
        int tmp = pages[i];
        pages[i] = pages[j];
        pages[j] = tmp;
      }
    }
  }
}
