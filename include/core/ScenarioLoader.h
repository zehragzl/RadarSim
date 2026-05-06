#ifndef SCENARIOLOADER_H
#define SCENARIOLOADER_H

#include <string>
#include "ObjectManager.h"
#include "../radar/IFFSystem.h"

class ScenarioLoader {
public:
    static void load(const std::string& path, ObjectManager& manager, IFFSystem& iff);
};

#endif
