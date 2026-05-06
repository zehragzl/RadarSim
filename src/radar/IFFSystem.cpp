#include "../../include/radar/IFFSystem.h"

IFFSystem::IFFSystem() {
    // Varsayılan: ID'si kayıtlı olmayan her hedef UNKNOWN
}

void IFFSystem::setStatus(int id, IFFStatus status) {
    registry_[id] = status;
}

IFFStatus IFFSystem::classify(int id) const {
    auto it = registry_.find(id);
    if (it == registry_.end())
        return IFFStatus::UNKNOWN;
    return it->second;
}
