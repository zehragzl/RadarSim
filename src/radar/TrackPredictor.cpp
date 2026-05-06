#include "../../include/radar/TrackPredictor.h"

void TrackPredictor::update(const std::vector<Track>& tracks) {
    for (const auto& t : tracks) {
        auto& hist = history_[t.id];
        hist.push_back(t.lastKnownPosition);
        if (hist.size() > MAX_HISTORY)
            hist.pop_front();
    }
}

std::vector<Vector2D> TrackPredictor::predict(int id, double lookaheadSeconds, int steps) const {
    auto it = history_.find(id);
    if (it == history_.end() || it->second.size() < 2)
        return {};

    const auto& hist = it->second;
    Vector2D newest = hist.back();
    Vector2D oldest = hist.front();
    double dt = static_cast<double>(hist.size() - 1) * TICK_DT;
    Vector2D vel = (newest - oldest) * (1.0 / dt);

    std::vector<Vector2D> result;
    result.reserve(steps);
    for (int i = 1; i <= steps; ++i) {
        double t = lookaheadSeconds * i / steps;
        result.push_back(newest + vel * t);
    }
    return result;
}
