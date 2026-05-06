#include <gtest/gtest.h>
#include "core/Vector2D.h"
#include "domain/Aircraft.h"

TEST(AircraftTest, MovesCorrectly) {
    Aircraft a(1, Vector2D(0, 0), Vector2D(10, 5), 8000);
    a.update(1.0);
    EXPECT_DOUBLE_EQ(a.position().getX(), 10.0);
    EXPECT_DOUBLE_EQ(a.position().getY(), 5.0);
}

TEST(AircraftTest, HalfSecondUpdate) {
    Aircraft a(1, Vector2D(0, 0), Vector2D(20, 0), 8000);
    a.update(0.5);
    EXPECT_DOUBLE_EQ(a.position().getX(), 10.0);
}

TEST(AircraftTest, ReflectsAtBoundary) {
    // Starts just inside boundary, moving outward fast
    Aircraft a(1, Vector2D(240, 0), Vector2D(50, 0), 8000);
    a.update(1.0);
    // After update it would be at x=290 > 250, so it should reflect
    EXPECT_LE(a.position().length(), 250.0 + 1e-6);
}

TEST(AircraftTest, RCSValue) {
    Aircraft a(1, Vector2D(0, 0), Vector2D(0, 0), 8000);
    EXPECT_DOUBLE_EQ(a.radarCrossSection(), 1.0);
}

TEST(AircraftTest, TypeName) {
    Aircraft a(1, Vector2D(0, 0), Vector2D(0, 0), 8000);
    EXPECT_EQ(a.typeName(), "Aircraft");
}
