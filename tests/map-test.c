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
#include "../src/map.h"

DUC_TEST(map, empty_exists_length) {
  duc_map_t *map = duc_map_new();

  DUC_ASSERT_TRUE(duc_map_empty(map));
  DUC_ASSERT_FALSE(duc_map_exists(map, "test1"));
  DUC_ASSERT_EQ(duc_map_length(map), 0);

  duc_map_set(map, "test1", NULL);

  DUC_ASSERT_FALSE(duc_map_empty(map));
  DUC_ASSERT_TRUE(duc_map_exists(map, "test1"));
  DUC_ASSERT_EQ(duc_map_length(map), 1);

  duc_map_set(map, "test2", NULL);

  DUC_ASSERT_FALSE(duc_map_empty(map));
  DUC_ASSERT_TRUE(duc_map_exists(map, "test2"));
  DUC_ASSERT_EQ(duc_map_length(map), 2);

  duc_map_free(map, duc_free_simple);
}

DUC_TEST(map, get_set_delete) {
  duc_map_t *map = duc_map_new();

  DUC_ASSERT_EQ(duc_map_length(map), 0);
  duc_map_set(map, "test1", NULL);
  DUC_ASSERT_EQ(duc_map_length(map), 1);
  duc_map_set(map, "test2", NULL);
  DUC_ASSERT_EQ(duc_map_length(map), 2);
  duc_map_set(map, "test2", NULL);
  DUC_ASSERT_EQ(duc_map_length(map), 2);

  DUC_ASSERT_EQ(duc_map_get(map, "test1"), NULL);
  DUC_ASSERT_EQ(duc_map_get(map, "test2"), NULL);
  DUC_ASSERT_EQ(duc_map_get(map, "test3"), NULL);

  duc_map_delete(map, "test0", duc_free_simple);
  DUC_ASSERT_EQ(duc_map_length(map), 2);
  duc_map_delete(map, "test1", duc_free_simple);
  DUC_ASSERT_EQ(duc_map_length(map), 1);
  duc_map_delete(map, "test2", duc_free_simple);
  DUC_ASSERT_EQ(duc_map_length(map), 0);
  duc_map_delete(map, "test3", duc_free_simple);
  DUC_ASSERT_EQ(duc_map_length(map), 0);

  duc_map_free(map, duc_free_simple);
}

DUC_TEST(map, new_and_free) {
  duc_map_t *map = duc_map_new();
  DUC_ASSERT_NE(map, NULL);

  duc_map_set(map, "test1", NULL);
  duc_map_set(map, "test2", NULL);
  duc_map_set(map, "test3", NULL);
  duc_map_free(map, duc_free_simple);
  duc_map_free(duc_map_new(), duc_free_simple);
}

int main () {
  DUC_TEST_RUN(map, empty_exists_length);
  DUC_TEST_RUN(map, get_set_delete);
  DUC_TEST_RUN(map, new_and_free);
}
