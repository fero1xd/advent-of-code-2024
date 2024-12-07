#include "../io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10
#define ROWS 10

int move_player(char **map);

int main() {
  char *map_raw = read_file("./src/06/sample.txt");

  char *map[ROWS];
  int cur_row = 0;

  for (int i = 0; map_raw[i] != '\0'; i++) {
    if (map_raw[i] == '\n') {
      map_raw[i] = '\0';
      map[cur_row++] = (&map_raw[i]) - WIDTH;
    }
  }

  int steps = 1;
  while (1) {
    int code = move_player(map);

    if (code == -1) {
      break;
    }

    if (code == 1) {
      steps++;
    }
  }

  printf("Steps taken: %d\n", steps);

  free(map_raw);
  return 0;
}

typedef struct {
  int x, y;
} Position;

/*
 * Returns -1 when player reaches out of bounds
 * Returns 0 when there is a dir change
 * Returns 1 when there is a step taken
 */
int move_player(char **map) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < WIDTH; j++) {
      // Check if player is going outside the map
      char dir = map[i][j];
      if (dir == '^' && i == 0) {
        return -1;
      } else if (dir == '>' && j == (WIDTH - 1)) {
        return -1;
      } else if (dir == '<' && j == 0) {
        return -1;
      } else if (dir == 'v' && i == (ROWS - 1)) {
        return -1;
      }

      if (dir == '^') {
        if (map[i - 1][j] == '#') {
          // Obstacle
          map[i][j] = '>';
          return false;
        }

        // Update current
        map[i][j] = 'X';
        // Move
        if (map[i - 1][j] == 'X') {
          // Visited
          map[i - 1][j] = '^';
          return false;
        }

        map[i - 1][j] = '^';
        return true;
      } else if (dir == '>') {
        if (map[i][j + 1] == '#') {
          // Obstacle
          map[i][j] = 'v';
          return false;
        }

        // Update current
        map[i][j] = 'X';
        // Move
        if (map[i][j + 1] == 'X') {
          // Visited
          map[i][j + 1] = '>';
          return false;
        }

        map[i][j + 1] = '>';
        return true;
      } else if (dir == 'v') {
        if (map[i + 1][j] == '#') {
          // Obstacle
          map[i][j] = '<';
          return false;
        }

        // Update current
        map[i][j] = 'X';
        // Move
        if (map[i + 1][j] == 'X') {
          // Visited
          map[i + 1][j] = 'v';
          return false;
        }

        map[i + 1][j] = 'v';

        return true;
      } else if (dir == '<') {
        if (map[i][j - 1] == '#') {
          // Obstacle
          map[i][j] = '^';

          return false;
        }

        // Update current
        map[i][j] = 'X';
        // Move
        if (map[i][j - 1] == 'X') {
          // Visited
          map[i][j - 1] = '<';
          return false;
        }

        map[i][j - 1] = '<';
        return true;
      }
    }
  }

  return 0;
}
