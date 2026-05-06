#include <gtest/gtest.h>
#include "core/FlyingObjectFactory.h"
#include "core/Vector2D.h"

TEST(FactoryTest, CreatesAircraft) {
    auto obj = FlyingObjectFactory::create("Aircraft", 1, Vector2D(0,0), Vector2D(10,0), 8000);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->typeName(), "Aircraft");
}

TEST(FactoryTest, CreatesHelicopter) {
    auto obj = FlyingObjectFactory::create("Helicopter", 2, Vector2D(0,0), Vector2D(5,0), 300);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->typeName(), "Helicopter");
}

TEST(FactoryTest, CreatesUAV) {
    auto obj = FlyingObjectFactory::create("UAV", 3, Vector2D(0,0), Vector2D(15,0), 1000);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->typeName(), "UAV");
}

TEST(FactoryTest, UnknownTypeReturnsNull) {
    auto obj = FlyingObjectFactory::create("Tank", 4, Vector2D(0,0), Vector2D(0,0), 0);
    EXPECT_EQ(obj, nullptr);
}

TEST(FactoryTest, CreatedObjectHasCorrectId) {
    auto obj = FlyingObjectFactory::create("Aircraft", 42, Vector2D(0,0), Vector2D(0,0), 5000);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->id(), 42);
}
