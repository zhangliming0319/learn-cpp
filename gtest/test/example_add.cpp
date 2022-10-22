// Copyright 2021 Tencent Inc.  All rights reserved.
//
// Author: leolmzhang@tencent.com (leolmzhang)
//
// test instance
#include <gtest/gtest.h>

#include "example.h"

TEST(example, add) {
  double res;
  res = add_numbers(1.0, 2.0);
  ASSERT_NEAR(res, 3.0, 1.0e-11);
}
