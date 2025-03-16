#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(EditDistance, Test) {
  EXPECT_TRUE(is_adjacent("apple", "appl"));
  EXPECT_TRUE(is_adjacent("mouse", "mous"));
  EXPECT_TRUE(is_adjacent("apple", "appe"));
  EXPECT_TRUE(is_adjacent("mouse", "moue"));
  EXPECT_TRUE(is_adjacent("apple", "aple"));
  EXPECT_TRUE(is_adjacent("mouse", "ouse"));
  EXPECT_TRUE(is_adjacent("apple", "applep"));
  EXPECT_TRUE(is_adjacent("mouse", "mousee"));
}


TEST(WordLadder, Test) {
  set<string> word_list = {"apple", "apply", "applyi", "applyin", "applying", "blah", "boo", "some", "random", "words"};
  string begin = "apple";
  string end = "applying";
  vector<string> expect = {"apple", "apply", "applyi", "applyin", "applying"};
  EXPECT_EQ(generate_word_ladder(begin, end, word_list), expect);
}