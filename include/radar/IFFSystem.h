#ifndef IFFSYSTEM_H
#define IFFSYSTEM_H

#include <unordered_map>

enum class IFFStatus {
    FRIEND,
    FOE,
    UNKNOWN
};

class IFFSystem {
public:
    IFFSystem();

    void setStatus(int id, IFFStatus status);
    IFFStatus classify(int id) const;

private:
    std::unordered_map<int, IFFStatus> registry_;
};

#endif
