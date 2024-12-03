#include "io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_x(char *p, char ch);

bool is_enabled(char *contents, char *p);

int main() {

  char *contents = read_file("./input.txt");
  const char *prefix = "mul(";

  char *p = strstr(contents, prefix);
  int total = 0;

  while (p != NULL) {
    if (p[4] == ',') {
      p = strstr(p + 3, prefix);
      continue;
    }

    if (p[5] == ',' || p[6] == ',' || p[7] == ',') {
      int x = get_x(&p[4], ',');
      int y;

      if (p[5] == ',') {
        y = get_x(&p[6], ')');
      } else if (p[6] == ',') {
        y = get_x(&p[7], ')');
      } else if (p[7] == ',') {
        y = get_x(&p[8], ')');
      }

      if (p[7] != ')' && p[8] != ')' && p[9] != ')' && p[10] != ')' &&
          p[11] != ')') {
        p = strstr(p + 3, prefix);
        continue;
      }

      bool enabled = is_enabled(contents, p);

      if (enabled) {
        total += (x * y);
      }
      p = strstr(p + 3, prefix);
    } else {
      p = strstr(p + 3, prefix);
      continue;
    }
  }

  printf("Total sum: %d\n", total);

  free(contents);
  return 0;
}

int get_x(char *p, char ch) {
  if (p[1] == ch) {
    return p[0] - '0';
  } else if (p[2] == ch) {
    char aa[3] = {p[0], p[1], '\0'};
    return atoi(aa);
  } else if (p[3] == ch) {
    char aa[4] = {p[0], p[1], p[2], '\0'};
    return atoi(aa);
  }

  return -1;
}

bool is_enabled(char *contents, char *p) {
  const char *enabled_prefix = "do()";
  const char *disabled_prefix = "don't()";

  char cp = p[0];

  p[0] = '\0';

  char *e = strstr(contents, enabled_prefix);
  while (e != NULL) {
    char *current_idx = strstr(e + 1, enabled_prefix);
    if (current_idx == NULL) {
      break;
    }
    e = current_idx;
  }

  char *d = strstr(contents, disabled_prefix);
  while (d != NULL) {
    char *current_idx = strstr(d + 1, disabled_prefix);
    if (current_idx == NULL) {
      break;
    }
    d = current_idx;
  }

  p[0] = cp;

  if (e == NULL && d == NULL) {
    return true;
  }

  if (e == NULL) {
    return false;
  }

  if (d == NULL) {
    return true;
  }

  return e > d;
}
