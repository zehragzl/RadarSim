#include <gtest/gtest.h>
#include "core/Vector2D.h"

TEST(Vector2DTest, Addition) {
    Vector2D a(1, 2), b(3, 4);
    Vector2D c = a + b;
    EXPECT_DOUBLE_EQ(c.getX(), 4);
    EXPECT_DOUBLE_EQ(c.getY(), 6);
}

TEST(Vector2DTest, Subtraction) {
    Vector2D a(5, 3), b(2, 1);
    Vector2D c = a - b;
    EXPECT_DOUBLE_EQ(c.getX(), 3);
    EXPECT_DOUBLE_EQ(c.getY(), 2);
}

TEST(Vector2DTest, ScalarMultiplication) {
    Vector2D a(2, 3);
    Vector2D c = a * 2.0;
    EXPECT_DOUBLE_EQ(c.getX(), 4);
    EXPECT_DOUBLE_EQ(c.getY(), 6);
}

TEST(Vector2DTest, Length) {
    Vector2D a(3, 4);
    EXPECT_DOUBLE_EQ(a.length(), 5.0);
}

TEST(Vector2DTest, Normalize) {
    Vector2D a(3, 4);
    Vector2D n = a.normalize();
    EXPECT_NEAR(n.length(), 1.0, 1e-9);
    EXPECT_NEAR(n.getX(), 0.6, 1e-9);
    EXPECT_NEAR(n.getY(), 0.8, 1e-9);
}

TEST(Vector2DTest, NormalizeZeroVector) {
    Vector2D a(0, 0);
    Vector2D n = a.normalize();
    EXPECT_DOUBLE_EQ(n.getX(), 0);
    EXPECT_DOUBLE_EQ(n.getY(), 0);
}

TEST(Vector2DTest, DotProduct) {
    Vector2D a(1, 2), b(3, 4);
    EXPECT_DOUBLE_EQ(a.dot(b), 11.0);
}

TEST(Vector2DTest, Distance) {
    Vector2D a(0, 0), b(3, 4);
    EXPECT_DOUBLE_EQ(a.distanceOf(b), 5.0);
}
