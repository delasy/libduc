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

#include <stdlib.h>
#include "array.h"

void *duc_array_at (const duc_array_t *arr, size_t index) {
  if (index >= arr->size) {
    return NULL;
  }

  duc_array_item_t *it = arr->items;

  for (size_t i = 0; i < index; i++) {
    it = it->next;
  }

  return it->value;
}

bool duc_array_empty (const duc_array_t *arr) {
  return arr->size == 0;
}

void duc_array_free (duc_array_t *arr, duc_free_cb free_cb) {
  while (arr->items != NULL) {
    duc_array_item_t *next = arr->items->next;

    free_cb(arr->items->value);
    free(arr->items);
    arr->items = next;
  }

  free(arr);
}

size_t duc_array_length (const duc_array_t *arr) {
  return arr->size;
}

duc_array_t *duc_array_new () {
  duc_array_t *arr = malloc(sizeof(duc_array_t));

  if (arr == NULL) {
    return NULL;
  }

  arr->items = NULL;
  arr->size = 0;

  return arr;
}

void duc_array_push (duc_array_t *arr, void *value) {
  duc_array_item_t *it = arr->items;

  while (it != NULL && it->next != NULL) {
    it = it->next;
  }

  duc_array_item_t *in = malloc(sizeof(duc_array_item_t));

  if (in == NULL) {
    return;
  }

  in->next = NULL;
  in->value = value;

  if (it == NULL) {
    arr->items = in;
  } else {
    it->next = in;
  }

  arr->size += 1;
}

void *duc_array_shift (duc_array_t *arr) {
  if (duc_array_empty(arr)) {
    return NULL;
  }

  duc_array_item_t *next = arr->items->next;
  void *value = arr->items->value;

  free(arr->items);
  arr->items = next;
  arr->size -= 1;

  return value;
}
