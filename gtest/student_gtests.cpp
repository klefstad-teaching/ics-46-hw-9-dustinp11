#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(EditDistance, Test) {
  EXPECT_TRUE(edit_distance_within("abc", "bbc", 1));
  EXPECT_TRUE(edit_distance_within("adc", "abc", 1));
  EXPECT_TRUE(edit_distance_within("kitten", "sitting", 3));
  EXPECT_FALSE(edit_distance_within("kitten", "sitting", 2));
}
