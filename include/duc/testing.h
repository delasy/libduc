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

#ifndef DUC_TESTING_H
#define DUC_TESTING_H

/* See https://github.com/delasy/libduc for reference. */

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Assert if left-hand side expression not equal right-hand side expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_EQ(lhs_expr, rhs_expr) \
  assert((lhs_expr) == (rhs_expr))

/**
 * Assert if expression is true
 * @param expr Expression
 */
#define DUC_ASSERT_FALSE(expr) \
  assert((expr) == false)

/**
 * Assert if left-hand side expression less than right-hand side expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_GE(lhs_expr, rhs_expr) \
  assert((lhs_expr) >= (rhs_expr))

/**
 * Assert if left-hand side expression less than equal right-hand side
 *  expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_GT(lhs_expr, rhs_expr) \
  assert((lhs_expr) > (rhs_expr))

/**
 * Assert if left-hand side expression greater than right-hand side expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_LE(lhs_expr, rhs_expr) \
  assert((lhs_expr) <= (rhs_expr))

/**
 * Assert if left-hand side expression greater than equal right-hand side
 *  expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_LT(lhs_expr, rhs_expr) \
  assert((lhs_expr) < (rhs_expr))

/**
 * Assert if left-hand side expression memory not equal right-hand side
 *  expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 * @param len
 */
#define DUC_ASSERT_MEMEQ(lhs_expr, rhs_expr, len) \
  assert(memcmp(lhs_expr, rhs_expr, len) == 0)

/**
 * Assert if left-hand side expression memory equal right-hand side expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 * @param len
 */
#define DUC_ASSERT_MEMNE(lhs_expr, rhs_expr, len) \
  assert(memcmp(lhs_expr, rhs_expr, len) != 0)

/**
 * Assert if left-hand side expression equal right-hand side expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_NE(lhs_expr, rhs_expr) \
  assert((lhs_expr) != (rhs_expr))

/**
 * Assert if left-hand side expression string not equal right-hand side
 *  expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_STREQ(lhs_expr, rhs_expr) \
  assert(strcmp(lhs_expr, rhs_expr) == 0)

/**
 * Assert if left-hand side expression string equal right-hand side expression
 * @param lhs_expr Left-hand side expression
 * @param rhs_expr Right-hand side expression
 */
#define DUC_ASSERT_STRNE(lhs_expr, rhs_expr) \
  assert(strcmp(lhs_expr, rhs_expr) != 0)

/**
 * Assert if expression is false
 * @param expr Expression
 */
#define DUC_ASSERT_TRUE(expr) \
  assert((expr) == true)

/**
 * Generate definition of the test
 * @param test_suite_name Test suite name
 * @param test_name Test name
 */
#define DUC_TEST(test_suite_name, test_name) \
  void test_suite_name##_##test_name##_test () \

/**
 * Run previously defined test
 * @param test_suite_name Test suite name
 * @param test_name Test name
 */
#define DUC_TEST_RUN(test_suite_name, test_name) \
  test_suite_name##_##test_name##_test()

#endif
