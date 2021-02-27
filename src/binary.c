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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary.h"

void duc_binary_append_binary (duc_binary_t *dest, const duc_binary_t *src) {
  size_t offset = dest->size;
  dest->size += src->size;

  if (dest->data == NULL) {
    dest->data = malloc(dest->size);
  } else {
    dest->data = realloc(dest->data, dest->size);
  }

  memcpy(dest->data + offset, src->data, src->size);
}

void duc_binary_append_data (duc_binary_t *binary, const void *data, size_t size) {
  size_t offset = binary->size;
  binary->size += size;

  if (binary->data == NULL) {
    binary->data = malloc(binary->size);
  } else {
    binary->data = realloc(binary->data, binary->size);
  }

  memcpy(binary->data + offset, data, size);
}

void duc_binary_append_string (duc_binary_t *binary, const char *string) {
  size_t offset = binary->size;
  size_t str_len = strlen(string) + 1;
  binary->size += str_len;

  if (binary->data == NULL) {
    binary->data = malloc(binary->size);
  } else {
    binary->data = realloc(binary->data, binary->size);
  }

  memcpy(binary->data + offset, string, str_len);
}

void duc_binary_append_times (duc_binary_t *binary, unsigned char ch, size_t times) {
  if (times == 0) {
    return;
  }

  size_t offset = binary->size;
  binary->size += times;

  if (binary->data == NULL) {
    binary->data = malloc(binary->size);
  } else {
    binary->data = realloc(binary->data, binary->size);
  }

  memset(binary->data + offset, ch, times);
}

uint8_t duc_binary_at (const duc_binary_t *binary, size_t index) {
  if (index >= binary->size) {
    return 0;
  }

  return binary->data[index];
}

const uint8_t *duc_binary_data (const duc_binary_t *binary) {
  return binary->data;
}

bool duc_binary_empty (const duc_binary_t *binary) {
  return binary->size == 0;
}

void duc_binary_free (duc_binary_t *binary) {
  if (binary->size > 0) {
    free(binary->data);
  }

  free(binary);
}

duc_binary_t *duc_binary_new () {
  duc_binary_t *binary = malloc(sizeof(duc_binary_t));

  binary->data = NULL;
  binary->size = 0;

  return binary;
}

size_t duc_binary_size (const duc_binary_t *binary) {
  return binary->size;
}

void duc_binary_write (const duc_binary_t *binary, const char *filepath) {
  FILE *fp = fopen(filepath, "wb");
  fwrite(binary->data, binary->size, 1, fp);
  fclose(fp);
}

#define DUC_BINARY_APPEND_(t, s, body) \
  do { size_t offset = binary->size; \
  size_t m = sizeof(t); \
  binary->size += n * m; \
  if (binary->data == NULL) binary->data = malloc(binary->size); \
  else binary->data = realloc(binary->data, binary->size); \
  va_list ap; \
  va_start(ap, n); \
  for (size_t i = 0; i < n * m; i += m) { \
    t ch = (t) va_arg(ap, s); \
    body \
  } \
  va_end(ap); } while (0)

void duc_binary_append_int8_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(int8_t, int, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
  });
}

void duc_binary_append_int16_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(int16_t, int, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
    binary->data[offset + i + 1] = (uint8_t) (ch >> 8 & 0xFF);
  });
}

void duc_binary_append_int32_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(int32_t, int, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
    binary->data[offset + i + 1] = (uint8_t) (ch >> 8 & 0xFF);
    binary->data[offset + i + 2] = (uint8_t) (ch >> 16 & 0xFF);
    binary->data[offset + i + 3] = (uint8_t) (ch >> 24 & 0xFF);
  });
}

void duc_binary_append_int64_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(int64_t, long long, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
    binary->data[offset + i + 1] = (uint8_t) (ch >> 8 & 0xFF);
    binary->data[offset + i + 2] = (uint8_t) (ch >> 16 & 0xFF);
    binary->data[offset + i + 3] = (uint8_t) (ch >> 24 & 0xFF);
    binary->data[offset + i + 4] = (uint8_t) (ch >> 32 & 0xFF);
    binary->data[offset + i + 5] = (uint8_t) (ch >> 40 & 0xFF);
    binary->data[offset + i + 6] = (uint8_t) (ch >> 48 & 0xFF);
    binary->data[offset + i + 7] = (uint8_t) (ch >> 56 & 0xFF);
  });
}

void duc_binary_append_uint8_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(uint8_t, unsigned int, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
  });
}

void duc_binary_append_uint16_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(uint16_t, unsigned int, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
    binary->data[offset + i + 1] = (uint8_t) (ch >> 8 & 0xFF);
  });
}

void duc_binary_append_uint32_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(uint32_t, unsigned int, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
    binary->data[offset + i + 1] = (uint8_t) (ch >> 8 & 0xFF);
    binary->data[offset + i + 2] = (uint8_t) (ch >> 16 & 0xFF);
    binary->data[offset + i + 3] = (uint8_t) (ch >> 24 & 0xFF);
  });
}

void duc_binary_append_uint64_ (duc_binary_t *binary, size_t n, ...) {
  DUC_BINARY_APPEND_(uint64_t, unsigned long long, {
    binary->data[offset + i] = (uint8_t) (ch & 0xFF);
    binary->data[offset + i + 1] = (uint8_t) (ch >> 8 & 0xFF);
    binary->data[offset + i + 2] = (uint8_t) (ch >> 16 & 0xFF);
    binary->data[offset + i + 3] = (uint8_t) (ch >> 24 & 0xFF);
    binary->data[offset + i + 4] = (uint8_t) (ch >> 32 & 0xFF);
    binary->data[offset + i + 5] = (uint8_t) (ch >> 40 & 0xFF);
    binary->data[offset + i + 6] = (uint8_t) (ch >> 48 & 0xFF);
    binary->data[offset + i + 7] = (uint8_t) (ch >> 56 & 0xFF);
  });
}
