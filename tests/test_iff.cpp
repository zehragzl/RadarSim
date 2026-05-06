#include <gtest/gtest.h>
#include "radar/IFFSystem.h"

TEST(IFFSystemTest, DefaultIsUnknown) {
    IFFSystem iff;
    EXPECT_EQ(iff.classify(99), IFFStatus::UNKNOWN);
}

TEST(IFFSystemTest, SetFriend) {
    IFFSystem iff;
    iff.setStatus(1, IFFStatus::FRIEND);
    EXPECT_EQ(iff.classify(1), IFFStatus::FRIEND);
}

TEST(IFFSystemTest, SetFoe) {
    IFFSystem iff;
    iff.setStatus(2, IFFStatus::FOE);
    EXPECT_EQ(iff.classify(2), IFFStatus::FOE);
}

TEST(IFFSystemTest, MultipleIds) {
    IFFSystem iff;
    iff.setStatus(1, IFFStatus::FRIEND);
    iff.setStatus(2, IFFStatus::FOE);
    iff.setStatus(3, IFFStatus::UNKNOWN);
    EXPECT_EQ(iff.classify(1), IFFStatus::FRIEND);
    EXPECT_EQ(iff.classify(2), IFFStatus::FOE);
    EXPECT_EQ(iff.classify(3), IFFStatus::UNKNOWN);
}

TEST(IFFSystemTest, OverwriteStatus) {
    IFFSystem iff;
    iff.setStatus(1, IFFStatus::FRIEND);
    iff.setStatus(1, IFFStatus::FOE);
    EXPECT_EQ(iff.classify(1), IFFStatus::FOE);
}
