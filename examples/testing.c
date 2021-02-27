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

#define TEST_F(body) \
  do { \
    /* Fixture setup */ \
    body \
    /* Fixture teardown */ \
  } while (0)

DUC_TEST(test_suite, test) {
  DUC_ASSERT_EQ(1, 1);
  DUC_ASSERT_NE(2, 1);
  DUC_ASSERT_FALSE(1 != 1);
  DUC_ASSERT_TRUE(1 == 1);
  DUC_ASSERT_GE(1, 1);
  DUC_ASSERT_GT(2, 1);
  DUC_ASSERT_LE(1, 1);
  DUC_ASSERT_LT(1, 2);
  DUC_ASSERT_STREQ("test", "test");
  DUC_ASSERT_STRNE("test1", "test2");

  uint8_t data[5] = { 't', 'e', 's', 't', '\0' };
  DUC_ASSERT_MEMEQ(data, "test", 4 + 1);
  DUC_ASSERT_MEMNE("test1", "test2", 5 + 1);

  TEST_F({
    // Fixture test body 1
  });

  TEST_F({
    // Fixture test body 2
  });
}

int main () {
  DUC_TEST_RUN(test_suite, test);
}
