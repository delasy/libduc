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
#include <duc/testing.h>
#include <stdlib.h>
#include "../src/binary.h"

DUC_TEST(binary, append_at_size) {
  duc_binary_t *binary0 = duc_binary_new();
  DUC_ASSERT_EQ(duc_binary_at(binary0, 0), 0x00);
  DUC_ASSERT_EQ(duc_binary_size(binary0), 0);

  uint8_t data[] = { 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA };

  duc_binary_append_data(binary0, data, sizeof(data));
  DUC_ASSERT_EQ(duc_binary_size(binary0), 6);
  DUC_ASSERT_EQ(duc_binary_at(binary0, 0), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary0, 1), 0xFE);
  DUC_ASSERT_EQ(duc_binary_at(binary0, 2), 0xFD);
  DUC_ASSERT_EQ(duc_binary_at(binary0, 3), 0xFC);
  DUC_ASSERT_EQ(duc_binary_at(binary0, 4), 0xFB);
  DUC_ASSERT_EQ(duc_binary_at(binary0, 5), 0xFA);

  duc_binary_t *binary = duc_binary_new();

  duc_binary_append_binary(binary, binary0);
  DUC_ASSERT_EQ(duc_binary_size(binary), 6);
  DUC_ASSERT_EQ(duc_binary_at(binary, 0), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, 1), 0xFE);
  DUC_ASSERT_EQ(duc_binary_at(binary, 2), 0xFD);
  DUC_ASSERT_EQ(duc_binary_at(binary, 3), 0xFC);
  DUC_ASSERT_EQ(duc_binary_at(binary, 4), 0xFB);
  DUC_ASSERT_EQ(duc_binary_at(binary, 5), 0xFA);
  duc_binary_free(binary0);

  size_t offset = duc_binary_size(binary);

  duc_binary_append_times(binary, '_', 0);
  duc_binary_append_times(binary, '$', 2);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 2);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), '$');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), '$');
  offset = duc_binary_size(binary);

  duc_binary_append_int8(binary, 0x01);
  duc_binary_append_int8(binary, -0x02, 0x03);
  duc_binary_append_int8(binary, -0x04, 0x05, -0x06);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0x01);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0xFE);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0x03);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0xFC);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0x05);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0xFA);
  offset = duc_binary_size(binary);

  duc_binary_append_uint8(binary, 0x01);
  duc_binary_append_uint8(binary, 0x02, 0x03);
  duc_binary_append_uint8(binary, 0x04, 0x05, 0x06);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0x01);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0x02);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0x03);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0x04);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0x05);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0x06);
  offset = duc_binary_size(binary);

  duc_binary_append_int16(binary, 0x0FF1);
  duc_binary_append_int16(binary, -0x0FF2, 0x0FF3);
  duc_binary_append_int16(binary, -0x0FF4, 0x0FF5, -0x0FF6);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6 * sizeof(int16_t));
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0xF1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0x0E);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0xF0);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0xF3);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 6), 0x0C);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 7), 0xF0);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 8), 0xF5);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 9), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 10), 0x0A);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 11), 0xF0);
  offset = duc_binary_size(binary);

  duc_binary_append_uint16(binary, 0x0FF1);
  duc_binary_append_uint16(binary, 0x0FF2, 0x0FF3);
  duc_binary_append_uint16(binary, 0x0FF4, 0x0FF5, 0x0FF6);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6 * sizeof(uint16_t));
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0xF1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0xF2);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0xF3);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 6), 0xF4);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 7), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 8), 0xF5);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 9), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 10), 0xF6);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 11), 0x0F);
  offset = duc_binary_size(binary);

  duc_binary_append_int32(binary, 0x0FFFFFF1);
  duc_binary_append_int32(binary, -0x0FFFFFF2, 0x0FFFFFF3);
  duc_binary_append_int32(binary, -0x0FFFFFF4, 0x0FFFFFF5, -0x0FFFFFF6);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6 * sizeof(int32_t));
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0xF1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0x0E);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 6), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 7), 0xF0);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 8), 0xF3);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 9), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 10), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 11), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 12), 0x0C);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 13), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 14), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 15), 0xF0);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 16), 0xF5);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 17), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 18), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 19), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 20), 0x0A);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 21), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 22), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 23), 0xF0);
  offset = duc_binary_size(binary);

  duc_binary_append_uint32(binary, 0x0FFFFFF1);
  duc_binary_append_uint32(binary, 0x0FFFFFF2, 0x0FFFFFF3);
  duc_binary_append_uint32(binary, 0x0FFFFFF4, 0x0FFFFFF5, 0x0FFFFFF6);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6 * sizeof(uint32_t));
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0xF1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0xF2);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 6), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 7), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 8), 0xF3);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 9), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 10), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 11), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 12), 0xF4);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 13), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 14), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 15), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 16), 0xF5);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 17), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 18), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 19), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 20), 0xF6);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 21), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 22), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 23), 0x0F);
  offset = duc_binary_size(binary);

  duc_binary_append_int64(binary, 0x0FFFFFFFFFFFFFF1);
  duc_binary_append_int64(binary, -0x0FFFFFFFFFFFFFF2, 0x0FFFFFFFFFFFFFF3);
  duc_binary_append_int64(binary, -0x0FFFFFFFFFFFFFF4, 0x0FFFFFFFFFFFFFF5, -0x0FFFFFFFFFFFFFF6);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6 * sizeof(int64_t));
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0xF1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 6), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 7), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 8), 0x0E);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 9), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 10), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 11), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 12), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 13), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 14), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 15), 0xF0);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 16), 0xF3);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 17), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 18), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 19), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 20), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 21), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 22), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 23), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 24), 0x0C);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 25), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 26), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 27), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 28), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 29), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 30), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 31), 0xF0);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 32), 0xF5);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 33), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 34), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 35), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 36), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 37), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 38), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 39), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 40), 0x0A);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 41), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 42), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 43), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 44), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 45), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 46), 0x00);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 47), 0xF0);
  offset = duc_binary_size(binary);

  duc_binary_append_uint64(binary, 0x0FFFFFFFFFFFFFF1);
  duc_binary_append_uint64(binary, 0x0FFFFFFFFFFFFFF2, 0x0FFFFFFFFFFFFFF3);
  duc_binary_append_uint64(binary, 0x0FFFFFFFFFFFFFF4, 0x0FFFFFFFFFFFFFF5, 0x0FFFFFFFFFFFFFF6);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6 * sizeof(uint64_t));
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 0xF1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 6), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 7), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 8), 0xF2);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 9), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 10), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 11), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 12), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 13), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 14), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 15), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 16), 0xF3);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 17), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 18), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 19), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 20), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 21), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 22), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 23), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 24), 0xF4);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 25), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 26), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 27), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 28), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 29), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 30), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 31), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 32), 0xF5);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 33), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 34), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 35), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 36), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 37), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 38), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 39), 0x0F);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 40), 0xF6);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 41), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 42), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 43), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 44), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 45), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 46), 0xFF);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 47), 0x0F);
  offset = duc_binary_size(binary);

  const char *string = "Test";
  duc_binary_append_string(binary, string);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + strlen(string) + 1);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 'T');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 'e');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), 's');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), 't');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), '\0');
  offset = duc_binary_size(binary);

  duc_binary_append_times(binary, 'A', 2);
  duc_binary_append_times(binary, '0', 4);
  DUC_ASSERT_EQ(duc_binary_size(binary), offset + 6);
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 0), 'A');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 1), 'A');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 2), '0');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 3), '0');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 4), '0');
  DUC_ASSERT_EQ(duc_binary_at(binary, offset + 5), '0');

  duc_binary_free(binary);
}

DUC_TEST(binary, data_and_empty) {
  duc_binary_t *binary = duc_binary_new();

  DUC_ASSERT_TRUE(duc_binary_empty(binary));
  duc_binary_append_string(binary, "Hello, World!");
  DUC_ASSERT_FALSE(duc_binary_empty(binary));
  DUC_ASSERT_MEMEQ(duc_binary_data(binary), "Hello, World!", 14);

  duc_binary_free(binary);
}

DUC_TEST(binary, write) {
  duc_binary_t *binary = duc_binary_new();
  char string[] = "Hello, World!";

  duc_binary_append_string(binary, string);
  duc_binary_write(binary, "../test.txt");
  duc_binary_free(binary);

  DUC_ASSERT_TRUE(duc_file_exists("../test.txt"));
  char *content = duc_readfile("../test.txt");

  DUC_ASSERT_STREQ(content, string);
  free(content);
  duc_file_remove("../test.txt");
}

int main () {
  DUC_TEST_RUN(binary, append_at_size);
  DUC_TEST_RUN(binary, data_and_empty);
  DUC_TEST_RUN(binary, write);
}
