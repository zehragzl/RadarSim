#include "../../include/radar/ThreatAnalyzer.h"
#include <algorithm>
#include <cmath>

ThreatAnalyzer::ThreatAnalyzer(double radarRangeKm)
    : radarRangeKm_(radarRangeKm) {}

ThreatReport ThreatAnalyzer::analyze(const Track& track) const {
    double score = calcScore(track);
    return { track.id, scoreToLevel(score), score };
}

std::vector<ThreatReport> ThreatAnalyzer::analyzeAll(const std::vector<Track>& tracks) const {
    std::vector<ThreatReport> reports;
    reports.reserve(tracks.size());
    for (const auto& t : tracks)
        reports.push_back(analyze(t));
    return reports;
}

double ThreatAnalyzer::calcScore(const Track& track) const {
    double score = 0.0;

    // 1. Yakınlık: 0-40 puan (ne kadar yakın, o kadar tehlikeli)
    double proximity = 1.0 - std::min(track.distanceKm / radarRangeKm_, 1.0);
    score += proximity * 40.0;

    // 2. Yaklaşma hızı: 0-30 puan (radara doğru geliyorsa tehlikeli)
    double posLen = track.lastKnownPosition.length();
    if (posLen > 0.001) {
        Vector2D posNorm(track.lastKnownPosition.getX() / posLen,
                         track.lastKnownPosition.getY() / posLen);
        double closingSpeed = -(posNorm.getX() * track.velocity.getX() +
                                posNorm.getY() * track.velocity.getY());
        if (closingSpeed > 0.0) {
            double maxSpeed = 50.0; // km/s referans hız
            score += std::min(closingSpeed / maxSpeed, 1.0) * 30.0;
        }
    }

    // 3. IFF durumu: FOE=30, UNKNOWN=15, FRIEND=0
    if (track.iff == IFFStatus::FOE)
        score += 30.0;
    else if (track.iff == IFFStatus::UNKNOWN)
        score += 15.0;

    return std::min(score, 100.0);
}

ThreatLevel ThreatAnalyzer::scoreToLevel(double score) const {
    if (score >= 70.0) return ThreatLevel::CRITICAL;
    if (score >= 50.0) return ThreatLevel::HIGH;
    if (score >= 25.0) return ThreatLevel::MEDIUM;
    return ThreatLevel::LOW;
}
