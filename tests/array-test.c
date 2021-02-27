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
#include "../src/array.h"

DUC_TEST(array, at) {
  int *a = malloc(sizeof(int));
  int *b = malloc(sizeof(int));

  *a = 1;
  *b = 2;

  duc_array_t *arr = duc_array_new();

  duc_array_push(arr, a);
  duc_array_push(arr, b);
  duc_array_push(arr, NULL);

  DUC_ASSERT_EQ(*((int *) duc_array_at(arr, 0)), 1);
  DUC_ASSERT_EQ(*((int *) duc_array_at(arr, 1)), 2);
  DUC_ASSERT_EQ(duc_array_at(arr, 2), NULL);
  DUC_ASSERT_EQ(duc_array_at(arr, 3), NULL);
  DUC_ASSERT_EQ(duc_array_at(arr, 4), NULL);

  duc_array_free(arr, duc_free_simple);
}

DUC_TEST(array, empty_and_length) {
  duc_array_t *arr = duc_array_new();

  DUC_ASSERT_TRUE(duc_array_empty(arr));
  DUC_ASSERT_EQ(duc_array_length(arr), 0);
  duc_array_push(arr, NULL);

  DUC_ASSERT_FALSE(duc_array_empty(arr));
  DUC_ASSERT_EQ(duc_array_length(arr), 1);
  duc_array_push(arr, NULL);

  DUC_ASSERT_FALSE(duc_array_empty(arr));
  DUC_ASSERT_EQ(duc_array_length(arr), 2);

  duc_array_free(arr, duc_free_simple);
}

DUC_TEST(array, new_and_free) {
  duc_array_t *arr = duc_array_new();
  DUC_ASSERT_NE(arr, NULL);

  duc_array_push(arr, NULL);
  duc_array_push(arr, NULL);
  duc_array_push(arr, NULL);
  duc_array_free(arr, duc_free_simple);
  duc_array_free(duc_array_new(), duc_free_simple);
}

DUC_TEST(array, push_and_shift) {
  duc_array_t *arr = duc_array_new();

  DUC_ASSERT_EQ(duc_array_length(arr), 0);
  duc_array_push(arr, NULL);
  DUC_ASSERT_EQ(duc_array_length(arr), 1);
  duc_array_push(arr, NULL);
  DUC_ASSERT_EQ(duc_array_length(arr), 2);

  DUC_ASSERT_EQ(duc_array_shift(arr), NULL);
  DUC_ASSERT_EQ(duc_array_length(arr), 1);
  DUC_ASSERT_EQ(duc_array_shift(arr), NULL);
  DUC_ASSERT_EQ(duc_array_length(arr), 0);
  DUC_ASSERT_EQ(duc_array_shift(arr), NULL);
  DUC_ASSERT_EQ(duc_array_length(arr), 0);

  duc_array_free(arr, duc_free_simple);
}

int main () {
  DUC_TEST_RUN(array, at);
  DUC_TEST_RUN(array, empty_and_length);
  DUC_TEST_RUN(array, new_and_free);
  DUC_TEST_RUN(array, push_and_shift);
}
