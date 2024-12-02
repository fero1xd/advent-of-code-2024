#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(char *path) {
  FILE *fp;

  if ((fp = fopen(path, "r")) == NULL) {
    printf("[-] Couldnt open file\n");
    return NULL;
  }

  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  char *contents = malloc(size + 1);
  memset(contents, 0, size);
  fread(contents, sizeof(char), size, fp);

  // printf("Contents: %s", contents);
  // printf("Length: %d", strlen(contents));
  // printf("Size: %ld\n", size);

  fclose(fp);
  return contents;
}
