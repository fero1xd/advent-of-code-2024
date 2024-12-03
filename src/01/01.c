#include "../io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom comparator
int comp(const void *a, const void *b) {

  // If a is smaller, positive value will be returned
  return (*(int *)a - *(int *)b);
}

int main() {
  char *contents = read_file("./src/01/input.txt");

  char *token = strtok(contents, "\n");

  int count = 0;

  int left[1000] = {0};
  int right[1000] = {0};

  while (token != NULL) {

    char *copy = strdup(token);
    char *l = strtok(copy, "   ");
    char *r = strtok(0, "   ");

    left[count] = atoi(l);
    right[count] = atoi(r);

    token = strtok((token + 13 + 1), "\n");
    count++;
  }

  qsort(left, sizeof(left) / sizeof(left[0]), sizeof(int), comp);
  qsort(right, sizeof(right) / sizeof(right[0]), sizeof(int), comp);

  int total_distance = 0;
  int sim_score = 0;

  for (int i = 0; i < count; i++) {
    total_distance += abs(left[i] - right[i]);

    int curr = left[i];
    int freq = 0;
    for (int j = 0; j < count; j++) {
      if (right[j] == curr) {
        freq++;
      }
    }

    sim_score += (curr * freq);
  }

  printf("total distance: %d\n", total_distance);
  printf("similarity score: %d\n", sim_score);

  free(contents);
  return 0;
}
