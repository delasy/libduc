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

#ifndef DUC_ARRAY_H
#define DUC_ARRAY_H

/* See https://github.com/delasy/libduc for reference. */

#include <duc/common.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct duc_array_s duc_array_t;

/**
 * Access array element at specified index
 * @param arr Array
 * @param index Index to search for
 * @return Array element or NULL if the given index doesn't exists
 */
void *duc_array_at (const duc_array_t *arr, size_t index);

/**
 * Check weather array is empty
 * @param arr Array
 * @return `true` if array has elements or `false` otherwise
 */
bool duc_array_empty (const duc_array_t *arr);

/**
 * Array destructor
 * @param arr Array
 * @param free_cb Array element free callback
 */
void duc_array_free (duc_array_t *arr, duc_free_cb free_cb);

/**
 * Access number of elements in the array
 * @param arr Array
 * @return Number of elements
 */
size_t duc_array_length (const duc_array_t *arr);

/**
 * Array constructor
 * @return Array
 */
duc_array_t *duc_array_new ();

/**
 * Append element value to the end of the array
 * @param arr Array
 * @param value Array element value
 */
void duc_array_push (duc_array_t *arr, void *value);

/**
 * Remove the first element from the array
 * @param arr Array
 * @return Array element that was removed or NULL if nothing was removed
 */
void *duc_array_shift (duc_array_t *arr);

#endif
