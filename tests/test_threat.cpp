#include <gtest/gtest.h>
#include "radar/ThreatAnalyzer.h"
#include "radar/Track.h"
#include "radar/IFFSystem.h"
#include "core/Vector2D.h"

static Track makeTrack(int id, double x, double y, double vx, double vy, IFFStatus iff) {
    Track t;
    t.id = id;
    t.typeName = "Aircraft";
    t.lastKnownPosition = Vector2D(x, y);
    t.velocity = Vector2D(vx, vy);
    t.altitude = 8000;
    t.distanceKm = Vector2D(x, y).length();
    t.iff = iff;
    return t;
}

TEST(ThreatAnalyzerTest, FarFriendIsLow) {
    ThreatAnalyzer analyzer(250.0);
    Track t = makeTrack(1, 200, 0, 5, 0, IFFStatus::FRIEND);
    auto report = analyzer.analyze(t);
    EXPECT_EQ(report.level, ThreatLevel::LOW);
}

TEST(ThreatAnalyzerTest, CloseFoeIsCritical) {
    ThreatAnalyzer analyzer(250.0);
    Track t = makeTrack(1, 5, 0, -50, 0, IFFStatus::FOE);
    auto report = analyzer.analyze(t);
    EXPECT_TRUE(report.level == ThreatLevel::HIGH ||
                report.level == ThreatLevel::CRITICAL);
}

TEST(ThreatAnalyzerTest, ScoreInRange) {
    ThreatAnalyzer analyzer(250.0);
    Track t = makeTrack(1, 100, 0, 10, 0, IFFStatus::UNKNOWN);
    auto report = analyzer.analyze(t);
    EXPECT_GE(report.score, 0.0);
    EXPECT_LE(report.score, 100.0);
}

TEST(ThreatAnalyzerTest, AnalyzeAllReturnsCorrectCount) {
    ThreatAnalyzer analyzer(250.0);
    std::vector<Track> tracks = {
        makeTrack(1, 50,  0, 10, 0, IFFStatus::FOE),
        makeTrack(2, 150, 0, 5,  0, IFFStatus::FRIEND),
        makeTrack(3, 200, 0, 2,  0, IFFStatus::UNKNOWN)
    };
    auto reports = analyzer.analyzeAll(tracks);
    EXPECT_EQ(reports.size(), 3u);
}
