#ifndef THREATANALYZER_H
#define THREATANALYZER_H

#include <vector>
#include "Track.h"

enum class ThreatLevel {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

struct ThreatReport {
    int id;
    ThreatLevel level;
    double score; // 0-100
};

class ThreatAnalyzer {
public:
    explicit ThreatAnalyzer(double radarRangeKm = 250.0);

    ThreatReport analyze(const Track& track) const;
    std::vector<ThreatReport> analyzeAll(const std::vector<Track>& tracks) const;

private:
    double radarRangeKm_;

    double calcScore(const Track& track) const;
    ThreatLevel scoreToLevel(double score) const;
};

#endif
