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

#ifndef DUC_BINARY_H
#define DUC_BINARY_H

/* See https://github.com/delasy/libduc for reference. */

#include <duc/helpers.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct duc_binary_s duc_binary_t;

/**
 * Append source binary to the destination binary
 * @param dest Destination binary
 * @param src Source binary
 */
void duc_binary_append_binary (duc_binary_t *dest, const duc_binary_t *src);

/**
 * Append data of specified size to the binary
 * @param binary Binary
 * @param data Data to be appended
 * @param size Data size
 */
void duc_binary_append_data (duc_binary_t *binary, const void *data, size_t size);

/**
 * Append up to 1024 int8 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_int8(binary, ...) \
  duc_binary_append_int8_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append up to 1024 int16 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_int16(binary, ...) \
  duc_binary_append_int16_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append up to 1024 int32 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_int32(binary, ...) \
  duc_binary_append_int32_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append up to 1024 int64 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_int64(binary, ...) \
  duc_binary_append_int64_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append string without trailing \0 to the binary
 * @param binary Binary
 * @param string String to be appended
 */
void duc_binary_append_string (duc_binary_t *binary, const char *string);

/**
 * Append specified character number of times to the binary
 * @param binary Binary
 * @param ch Character to be appended
 * @param times Number of times
 */
void duc_binary_append_times (duc_binary_t *binary, unsigned char ch, size_t times);

/**
 * Append up to 1024 uint8 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_uint8(binary, ...) \
  duc_binary_append_uint8_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append up to 1024 uint16 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_uint16(binary, ...) \
  duc_binary_append_uint16_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append up to 1024 uint32 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_uint32(binary, ...) \
  duc_binary_append_uint32_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Append up to 1024 uint64 arguments to the binary
 * @param binary Binary
 * @param ... arguments to be appended
 */
#define duc_binary_append_uint64(binary, ...) \
  duc_binary_append_uint64_(binary, DUC_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Access data at specified index
 * @param binary Binary
 * @param index Index to search for
 * @return unsigned char or 0 if the given index doesn't exists
 */
uint8_t duc_binary_at (const duc_binary_t *binary, size_t index);

/**
 * Access data of the binary
 * @param binary Binary
 * @return Data
 */
const uint8_t *duc_binary_data (const duc_binary_t *binary);

/**
 * Check weather binary is empty
 * @param binary Binary
 * @return `true` if binary has data or `false` otherwise
 */
bool duc_binary_empty (const duc_binary_t *binary);

/**
 * Binary destructor
 * @param binary Binary
 */
void duc_binary_free (duc_binary_t *binary);

/**
 * Binary constructor
 * @return Binary
 */
duc_binary_t *duc_binary_new ();

/**
 * Access data size of the binary
 * @param binary Binary
 * @return Data size
 */
size_t duc_binary_size (const duc_binary_t *binary);

/**
 * Write binary to the file
 * @param binary Binary
 * @param filepath File path
 */
void duc_binary_write (const duc_binary_t *binary, const char *filepath);

void duc_binary_append_int8_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_int16_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_int32_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_int64_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_uint8_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_uint16_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_uint32_ (duc_binary_t *binary, size_t n, ...);
void duc_binary_append_uint64_ (duc_binary_t *binary, size_t n, ...);

#endif
