/**
 * Copyright (c) Aaron Delasy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <duc/common.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fs.h"

bool duc_file_eof (const duc_file_t *file) {
  return file->eof;
}

bool duc_file_exists (const char *filepath) {
  return access(filepath, F_OK) == 0;
}

void duc_file_free (duc_file_t *file) {
  fclose(file->fp);
  free(file);
}

duc_file_t *duc_file_new (const char *filepath, duc_file_mode mode) {
  duc_file_t *file = malloc(sizeof(duc_file_t));

  if (file == NULL) {
    return NULL;
  }

  char *open_mode = "w";

  if (mode == DUC_FILE_READ) {
    open_mode = "r";
  } else if (mode == DUC_FILE_APPEND) {
    open_mode = "a";
  }

  file->fp = fopen(filepath, open_mode);

  if (file->fp == NULL) {
    free(file);
    return NULL;
  }

  char *path = duc_path_real(filepath);

  if (path == NULL) {
    fclose(file->fp);
    free(file);
    return NULL;
  }

  file->eof = feof(file->fp);
  strcpy(file->path, path);
  free(path);

  if (!file->eof) {
    file->eof = fgetc(file->fp) == EOF;
    fseek(file->fp, -1, SEEK_CUR);
  }

  return file;
}

size_t duc_file_position (const duc_file_t *file) {
  return (size_t) ftell(file->fp);
}

unsigned char duc_file_readchar (duc_file_t *file) {
  int res = fgetc(file->fp);
  file->eof = res == EOF;

  if (!file->eof) {
    file->eof = fgetc(file->fp) == EOF;
    fseek(file->fp, -1, SEEK_CUR);
  }

  return res <= 0 ? '\0' : (unsigned char) res;
}

char *duc_file_readline (duc_file_t *file) {
  char *line = NULL;
  size_t len = 0;
  file->eof = getline(&line, &len, file->fp) == -1;

  if (!file->eof) {
    file->eof = fgetc(file->fp) == EOF;
    fseek(file->fp, -1, SEEK_CUR);
  }

  return line;
}

void duc_file_remove (const char *filepath) {
  remove(filepath);
}

void duc_file_seek (duc_file_t *file, size_t pos) {
  fseek(file->fp, (ssize_t) pos, SEEK_SET);
  file->eof = feof(file->fp);
}

void duc_file_writechar (duc_file_t *file, unsigned char ch) {
  fputc(ch, file->fp);
}

void duc_file_writeline (duc_file_t *file, const char *line) {
  fputs(line, file->fp);
}

char *duc_readfile (const char *filepath) {
  FILE *fp = fopen(filepath, "rb");
  fseek(fp, 0, SEEK_END);
  size_t size = (size_t) ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *result = malloc(size + 1);

  if (fread(result, 1, size, fp) != size) {
    duc_throw("Failed to read from file");
  }

  result[size] = '\0';
  fclose(fp);

  return result;
}

void duc_writefile (const char *filepath, const char *content) {
  FILE *fp = fopen(filepath, "wb");
  fwrite(content, strlen(content), 1, fp);
  fclose(fp);
}

char *duc_path_cwd () {
  char *cwd = malloc(PATH_MAX);

  if (cwd == NULL) {
    return NULL;
  } else if (getcwd(cwd, PATH_MAX) == NULL) {
    free(cwd);
    return NULL;
  }

  return cwd;
}

char *duc_path_real (const char *path) {
  char *real_path = malloc(PATH_MAX);

  if (real_path == NULL) {
    return NULL;
  } else if (realpath(path, real_path) == NULL) {
    free(real_path);
    return NULL;
  }

  return real_path;
}
