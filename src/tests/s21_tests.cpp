#include <gtest/gtest.h>

#include <QString>

#include "model.h"

using namespace s21;

TEST(ParseFile, Test1) {
  int expected_points = 8;
  int expected_lines = 24;

  QString path("../cube.txt");
  Model::Instance()->parseFile(path);

  ASSERT_EQ(Model::Instance()->getCountVertices(), expected_points);
  ASSERT_EQ(Model::Instance()->getCountIndices(), expected_lines);
}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}