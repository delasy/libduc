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

#include <duc/binary.h>

int main () {
  duc_binary_t *bin = duc_binary_new();

  duc_binary_append_int8(bin, 0x01);
  duc_binary_append_uint8(bin, 0xAA, 0xBB);
  duc_binary_append_int16(bin, 0x1111, -0x2222, 0x4444);
  duc_binary_append_uint16(bin, 0xAAAA, 0xBBBB, 0xCCCC, 0xDDDD);
  duc_binary_append_int32(bin, 0x11111111, -0x22222222, 0x44444444);
  duc_binary_append_uint32(bin, 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC);
  duc_binary_append_int64(bin, 0x1111111111111111, -0x2222222222222222);
  duc_binary_append_uint64(bin, 0xAAAAAAAAAAAAAAAA, 0xBBBBBBBBBBBBBBBB);
  duc_binary_append_string(bin, "test");
  duc_binary_append_times(bin, 0x00, 10);

  if (!duc_binary_empty(bin)) {
    for (size_t i = 0, size = duc_binary_size(bin); i < size; i++) {
      uint8_t ch = duc_binary_at(bin, i);
      duc_binary_append_uint8(bin, ch);
    }
  }

  duc_binary_free(bin);
  return 0;
}
