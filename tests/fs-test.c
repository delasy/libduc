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

#include <duc/testing.h>
#include <stdlib.h>
#include "../src/fs.h"

#define FILE_F(text, body) \
  do { duc_writefile("../test.txt", text); \
  duc_file_t *file = duc_file_new("../test.txt", DUC_FILE_READ); \
  body \
  duc_file_free(file); \
  duc_file_remove("../test.txt"); } while (0)

DUC_TEST(file, eof_and_read) {
  FILE_F("", {
    DUC_ASSERT_TRUE(duc_file_eof(file));
  });

  FILE_F("\n", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    char *line = duc_file_readline(file);

    DUC_ASSERT_STREQ(line, "\n");
    DUC_ASSERT_TRUE(duc_file_eof(file));
    free(line);
  });

  FILE_F("Test", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    char *line = duc_file_readline(file);

    DUC_ASSERT_STREQ(line, "Test");
    DUC_ASSERT_TRUE(duc_file_eof(file));
    free(line);
  });

  FILE_F("Test\n", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    char *line = duc_file_readline(file);

    DUC_ASSERT_STREQ(line, "Test\n");
    DUC_ASSERT_TRUE(duc_file_eof(file));
    free(line);
  });

  FILE_F("Test1\nTest2", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    char *line1 = duc_file_readline(file);
    DUC_ASSERT_STREQ(line1, "Test1\n");
    DUC_ASSERT_FALSE(duc_file_eof(file));
    free(line1);

    char *line2 = duc_file_readline(file);
    DUC_ASSERT_STREQ(line2, "Test2");
    DUC_ASSERT_TRUE(duc_file_eof(file));
    free(line2);
  });

  FILE_F("Test1\nTest2\n", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    char *line1 = duc_file_readline(file);
    DUC_ASSERT_STREQ(line1, "Test1\n");
    DUC_ASSERT_FALSE(duc_file_eof(file));
    free(line1);

    size_t pos = duc_file_position(file);
    char *line2 = duc_file_readline(file);
    DUC_ASSERT_STREQ(line2, "Test2\n");
    DUC_ASSERT_TRUE(duc_file_eof(file));
    free(line2);
    duc_file_seek(file, pos);
    DUC_ASSERT_FALSE(duc_file_eof(file));

    char *line3 = duc_file_readline(file);
    DUC_ASSERT_STREQ(line3, "Test2\n");
    DUC_ASSERT_TRUE(duc_file_eof(file));
    free(line3);
  });

  FILE_F("\n", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), '\n');
    DUC_ASSERT_TRUE(duc_file_eof(file));
  });

  FILE_F("Test", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 'T');
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 'e');
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 's');
    DUC_ASSERT_FALSE(duc_file_eof(file));

    size_t pos = duc_file_position(file);
    DUC_ASSERT_EQ(duc_file_readchar(file), 't');
    DUC_ASSERT_TRUE(duc_file_eof(file));
    duc_file_seek(file, pos);

    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 't');
    DUC_ASSERT_TRUE(duc_file_eof(file));
  });

  FILE_F("Test\n", {
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 'T');
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 'e');
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 's');
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), 't');
    DUC_ASSERT_FALSE(duc_file_eof(file));
    DUC_ASSERT_EQ(duc_file_readchar(file), '\n');
    DUC_ASSERT_TRUE(duc_file_eof(file));
  });
}

DUC_TEST(file, exists_remove_write) {
  char *filepath = "../test.txt";
  DUC_ASSERT_FALSE(duc_file_exists(filepath));

  duc_file_t *file = duc_file_new(filepath, DUC_FILE_WRITE);

  duc_file_writeline(file, "Hello, World!");
  duc_file_writechar(file, '\n');
  duc_file_free(file);
  DUC_ASSERT_TRUE(duc_file_exists(filepath));

  file = duc_file_new(filepath, DUC_FILE_READ);
  char *line = duc_file_readline(file);

  DUC_ASSERT_STREQ(line, "Hello, World!\n");
  duc_file_free(file);
  free(line);

  duc_file_remove(filepath);
  DUC_ASSERT_FALSE(duc_file_exists(filepath));
}

DUC_TEST(file, new_and_free) {
  duc_file_t *file = duc_file_new("../fake.txt", DUC_FILE_READ);
  DUC_ASSERT_EQ(file, NULL);

  char *filepath = "../test.txt";

  file = duc_file_new(filepath, DUC_FILE_WRITE);
  DUC_ASSERT_NE(file, NULL);
  duc_file_free(file);

  file = duc_file_new(filepath, DUC_FILE_READ);
  DUC_ASSERT_NE(file, NULL);
  duc_file_free(file);

  file = duc_file_new(filepath, DUC_FILE_APPEND);
  DUC_ASSERT_NE(file, NULL);
  duc_file_free(file);

  duc_file_remove(filepath);
}

DUC_TEST(file, position_and_seek) {
  duc_file_t *file = duc_file_new("../LICENSE", DUC_FILE_READ);

  DUC_ASSERT_EQ(duc_file_position(file), 0);
  duc_file_seek(file, 1);
  DUC_ASSERT_EQ(duc_file_position(file), 1);
  duc_file_seek(file, 2);
  DUC_ASSERT_EQ(duc_file_position(file), 2);

  duc_file_free(file);
}

DUC_TEST(file, simple_read_write) {
  char *filepath = "../test.txt";

  DUC_ASSERT_FALSE(duc_file_exists(filepath));
  duc_writefile(filepath, "Hello, World!\n");
  DUC_ASSERT_TRUE(duc_file_exists(filepath));

  char *content = duc_readfile(filepath);
  DUC_ASSERT_STREQ(content, "Hello, World!\n");
  free(content);

  duc_file_remove(filepath);
}

DUC_TEST(path, cwd_and_real) {
  char *cwd = duc_path_cwd();
  char *path = duc_path_real("../LICENSE");
  char *non_path = duc_path_real("../fake");

  DUC_ASSERT_NE(cwd, NULL);
  DUC_ASSERT_STRNE(cwd, "");
  DUC_ASSERT_NE(path, NULL);
  DUC_ASSERT_STRNE(path, "");
  DUC_ASSERT_EQ(non_path, NULL);

  free(cwd);
  free(path);
}

int main () {
  DUC_TEST_RUN(file, eof_and_read);
  DUC_TEST_RUN(file, exists_remove_write);
  DUC_TEST_RUN(file, new_and_free);
  DUC_TEST_RUN(file, position_and_seek);
  DUC_TEST_RUN(file, simple_read_write);
  DUC_TEST_RUN(path, cwd_and_real);
}
