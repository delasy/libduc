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

#include <duc/fs.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
  duc_file_t *file = duc_file_new("LICENSE", DUC_FILE_READ);
  size_t pos = duc_file_position(file);

  while (!duc_file_eof(file)) {
    char *line = duc_file_readline(file);

    printf("%s", line);
    free(line);
  }

  duc_file_seek(file, pos);
  duc_file_free(file);

  file = duc_file_new("test.txt", DUC_FILE_WRITE);
  duc_file_writeline(file, "Hello, World!");
  duc_file_free(file);

  if (duc_file_exists("test.txt")) {
    duc_file_remove("test.txt");
  }

  duc_writefile("test.txt", "Hello, World!");
  char *content = duc_readfile("test.txt");

  printf("%s", content);
  free(content);
  duc_file_remove("test.txt");

  return 0;
}
