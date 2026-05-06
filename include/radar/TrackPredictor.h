#ifndef TRACKPREDICTOR_H
#define TRACKPREDICTOR_H

#include <vector>
#include <deque>
#include <unordered_map>
#include "Track.h"
#include "../core/Vector2D.h"

class TrackPredictor {
public:
    void update(const std::vector<Track>& tracks);
    std::vector<Vector2D> predict(int id, double lookaheadSeconds = 10.0, int steps = 5) const;

private:
    static constexpr size_t MAX_HISTORY = 20;
    static constexpr double TICK_DT     = 0.05;
    std::unordered_map<int, std::deque<Vector2D>> history_;
};

#endif
